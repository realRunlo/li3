#include "../includes/sgr.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct sgr{

    GHashTable * hashT_users;
    GHashTable * hashT_businesses;
    GHashTable * hashT_reviews;

};


struct table{

   char ** tab;
   int entries;

};


int getEntries(TABLE t){
    return t->entries;
}


char* get_string_table(TABLE t,int n){
    char* r;
    if(t->tab[n]) r = strdup(t->tab[n]);
    else r = NULL;
    return r;
}
/**
\brief Inicializador de dados SGR
@returns new_sgr stuct sgr
*/
SGR init_sgr(){

    SGR new_sgr = malloc(sizeof(struct sgr));

    new_sgr->hashT_users = initHashT();
    new_sgr->hashT_reviews= initHashT();
    new_sgr->hashT_businesses = initHashT();

    return new_sgr;
}

/*
void free_sgr(SGR sgr){
    free(sgr);    //not working
 
}
*/
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file){
    
    SGR sgr_load = init_sgr();

    printf("Loading...\n");

    mapToHash_ReviewsFile(reviews_file,sgr_load->hashT_reviews);
    
    readUser(sgr_load->hashT_users,users_file);

    readBusiness(sgr_load->hashT_businesses,buinesses_file);


    return sgr_load;
}



//struct used to store results found by query2_iterator
typedef struct query2{
        char** result; //[business1],[business2],[...]
        char letter;
        int column;
        int total;
}*Query2;

// Iterator for query2
void query2_iterator(gpointer key, gpointer value, gpointer user_data){
    char* name = get_name((Business) value);
    Query2 data = (Query2) user_data;
    char letter = data->letter;
    if(name[0] == letter){ 
        int col = data->column;
        data->result[col] =(char *) malloc(strlen(name) * sizeof(char));
        data->result[col] = name;
        data->column++;
        data->total++;
    }
}


/* query 2 */
//list of businesses whose name starts with char "letter"
TABLE businesses_started_by_letter(SGR sgr, char letter){
    int max_lines = g_hash_table_size(sgr->hashT_businesses);
    Query2 process = malloc(sizeof(struct query2));
    process->letter = letter;
    process->result = (char ** ) malloc(max_lines * sizeof(*process->result));
    process->column = 0;
    process->total = 0;
    //search every key in the hash for a business name starting with letter
    //if one is found, then result and total are updated 
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)query2_iterator,process);
    
    //turning the results from process into TABLE
    TABLE result = malloc(sizeof(struct table));
    result->tab = process->result;
    result->entries =  process->total;
    //free();
    return result;
}

/* query 3 
Dado um id de negócio, determinar a sua informação: nome,
cidade,estado,stars,e número total reviews*/
/*query 3*/
typedef struct query3{
        char* b_id;
        int total;
}*Query3;
// Iterator for query3
void query3_iterator(gpointer key, gpointer value, gpointer user_data){
    char* b_id = r_getBusinessId((Reviews) value);
    if(strcmp(b_id,user_data->b_id) == 0)
        user_data->total++;
}

TABLE business_info (SGR sgr, char* business_id){
    TABLE r; 
    Business c = malloc(sizeof(struct business));
    char* id = NULL;
    char** key_ptr = &id;
    struct business** value_ptr = &c;
    gboolean result = g_hash_table_lookup_extended(hash,business_id, 
                    (gpointer*)key_ptr, (gpointer*) value_ptr);
    if (result){ 
        //printf("%s\n%s\n%s\n%s\n%s\n",id, c->name,c->city,c->state,c->categories);
        Query3 pro = malloc(sizeof(struct query3));
        pro->b_id = strdup (business_id);
        pro->total = 0;
        g_hash_table_foreach(sgr.hashT_reviews, (GHFunc)query3_iterator,pro);
        //printf("%d\n",pro->total);
        free(pro);
    }
    return r;
}

typedef struct query4{
        char** result; //[business_id1,business1],[business_id2,business2][...]
        char* user_id;
        GHashTable * hashT_businesses; // used to look for the name of the business in case there is a review on it by the user
        int column;
}*Query4;


// Iterator for query4
void query4_iterator(gpointer key, gpointer value, gpointer user_data){
    Reviews r = (Reviews) value;
    char* user_id = r_getUserId(r);
    Query4 data = (Query4) user_data;

    if(strcmp(user_id,data->user_id) == 0){
        //Encontra o business correspondente ao business_id na review
        int col = data->column;
        char* b_id = r_getBusinessId(r);
        Business b = (Business) g_hash_table_lookup(data->hashT_businesses,GINT_TO_POINTER(b_id));
        char* b_name = get_name(b);
        char* result = malloc( sizeof(char) * (strlen(b_name) + strlen(b_id) + 1));
        //result = b_id,b_name
        snprintf(result,strlen(b_name) + strlen(b_id) + 1,"%s,%s",b_id,b_name);
        data->result[col] = result;
        data->column++;
        
    }
}


/* query 4 */
//searches for the business_id and name of every business a certain user has reviewed
TABLE businesses_reviewed(SGR sgr, char *user_id){
    int max_lines = g_hash_table_size(sgr->hashT_businesses);
    Query4 process = malloc(sizeof(struct query4));

    process->result = (char ** ) malloc(max_lines * sizeof(*process->result));
    process->user_id = strdup(user_id);
    process->hashT_businesses = sgr->hashT_businesses;
    process->column = 0;
    
    //procura o user_id nas reviews
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)query4_iterator, process);
    TABLE result = malloc(sizeof(struct table));
    result->tab = process->result;
    free(process->user_id);
    return result;
}
/* query 5 
Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais
stars na cidade.A informação associada a cada negócio deve ser o seu id e nome.*/
typedef struct query5{
        char* list; //[id_business1,name_business1,id_business2,...]
        char* city;
        float stars;
}*Query5;

void query5_iterator(gpointer key, gpointer value, gpointer user_data){
    Reviews r = ((Reviews)value);
    char* city = get_city((Business) value);
    float b_stars = get_stars(Business) value);

    if(b_stars >= user_data->stars){
        Business b = (Business) g_hash_table_lookup(data->hashT_business, r->business_id);
         if(strcmp(city,user_data_city)==0){
             user_data->list = (char*) realloc(user_data->list, strlen(user_data->list) 
                                        + strlen(b->business_id) + strlen(b->name) + 2);
            strcat(user_data->list,b->business_id);
            strcat(user_data->list,",");
            strcat(user_data->list,b->name);
            strcat(user_data->list,",");
        }
    }
}

TABLE businesses_with_stars_and_city (SGR sgr, float stars,char* city){
    TABLE r = malloc(sizeof(struct table));
    Query5 pro = malloc(sizeof(struct query5));
    pro->city = strdup (city);
    pro->stars = stars;
    g_hash_table_foreach(sgr.hashT_reviews, (GHFunc)query5_iterator,pro);
    r->tab[5] = strdup(pro->list);
    free(pro);   
    return r;
}

//struct para guardar informacoes sobre os top negocios de cada cidade 
typedef struct city{
    char* name;
    char** top; //[score1,business1][score2,business2][...]
    int entries;
    float low_score;
}*CITY;

//elemento da tabela que guarda a media de estrelas de cada negocio
typedef struct b_stars{
    char* b_name;
    int n_reviews;
    float total;
}*B_STARS;

//user_data para business_average_stars
typedef struct b_average_stars{
    SGR sgr;
    GHashTable * b_same_name;
    GHashTable * cities;
    int top;
}*B_AVERAGE_STARS;



// Cria uma hash em que cada elemento sao todos os negocios com o mesmo nome
// Alem disso verifica se a cidade do business ja foi adicionada na table das cidades
void b_name_hash(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Business b = (Business) value;
    char* b_name = get_name(b);
    //verifica se ja existe um negocio na table com o mesmo nome
    if(g_hash_table_lookup(data->b_same_name,GINT_TO_POINTER(b_name)) == NULL)
    {
        B_STARS business = malloc(sizeof(struct b_stars));
        business->b_name= b_name;
        business->n_reviews = 0;
        business->total = 0;
        addToHashT(data->b_same_name,GINT_TO_POINTER(b_name),business);
    }

    //verifica se ja foi adicionada a cidade na table
    char* city = get_city(b);
    if(g_hash_table_lookup(data->cities,GINT_TO_POINTER(city)) == NULL){
        CITY c = malloc(sizeof(struct city));
        c->entries = 0;
        c->low_score = 0;
        c->name = city;
        c->top = malloc(sizeof(char*) * data->top);
        addToHashT(data->cities,GINT_TO_POINTER(city),c);
    }
}

//para cada review vai a table "b_same_name" e adiciona no negocio correspondente o numero de estrelas
void b_add_stars(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Reviews r = (Reviews) value;
    char *b_id = r_getBusinessId(r);
    
    //encontra o negocio da review
    Business b = g_hash_table_lookup(data->sgr->hashT_businesses,GINT_TO_POINTER(b_id));
    char* b_name = get_name(b);

    //encontra o negocio (na table com os negocios de mesmo nome juntos)
    B_STARS b_average = g_hash_table_lookup(data->b_same_name,GINT_TO_POINTER(b_name));

    b_average->n_reviews++;
    b_average->total += r_getStars(r);
}


//verifica a cidade de cada business, e dependendo do seu average score, atualiza o top dessa cidade    
void top_city(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Business b = (Business) value;
    GHashTable * b_same_name = data->b_same_name;
    GHashTable * cities = data->cities;
    char* b_name    = get_name(b);
    char* b_id      = get_id(b);
    char* city_name = get_city(b);
    B_STARS bStar   = g_hash_table_lookup(b_same_name,GINT_TO_POINTER(b_name));
    CITY c          = g_hash_table_lookup(cities,GINT_TO_POINTER(city_name));
    float average   = bStar->total / bStar->n_reviews;
    int i = 0; int top = data->top;
    //verifica se o negocio tem reviews e caso tenha o top cheio, se o score do negocio e menor do que o minimo do top
    if(bStar->n_reviews > 0){
    //caso a cidade ja n tenha espaco no top e o score do negocio e menor do que o minimo do top
    if(c->entries == top && average < c->low_score);
    else{
        char stars[20]; //string para colocar as estrelas medias
        sprintf(stars,"%.2f",average); //float to string
        char * result = malloc(sizeof(char) * (strlen(stars) + strlen(b_name) + strlen(b_id) + 2)); //declaracao da string q sera colocada
        snprintf(result,strlen(stars) + strlen(b_name) + strlen(b_id)+ 2,"%s %s,%s",stars,b_name,b_id);
        //caso em que ainda nao foram adicionados nenhuns negocios
        if(c->entries == 0){
            c->top[0] = result;
            c->low_score = average;
            c->entries++;
        }
        else{
            //verificar se o negocio ja foi adicionado
            i = 0;
            char*buffer = malloc(sizeof(char) * 1000);
            int found = 0;
            int i_lowest = 0;
            float lowest;
            while(i < c->entries && found !=1){
                strcpy(buffer,c->top[i]);
                lowest = atof(strsep(&buffer," "));  //torna a string da media de estrelas em um float 
                if (lowest == c->low_score) i_lowest = i; //guarda a posicao do menor score
                if (strcmp(b_name,strsep(&buffer,",")) == 0) found++;
                i++;
            }
            //se o negocio ainda n foi adicionado mas o top ja esteja cheio, necessario trocar pelo de menor score
            if(found == 0 && c->entries == data->top){
                i = 0;
                c->top[i_lowest] = result;
                //atualizar score mais baixo
                float min = 20;
                float s;
                while(i < top){
                    strcpy(buffer,c->top[i]);
                    sprintf(strsep(&buffer," "),"%.2f",s);
                    if(s< min) min = s;
                    i++;
                }
                c->low_score = min;
            }
            //se a cidade ainda nao tem top negocios guardados, adiciona imediatamente numa posicao livre
            if(found == 0 && c->entries < data->top){
                c->top[c->entries] = result;
                c->low_score = average;
                c->entries++;
                //printf("cidade %s\n",c->top[i]);
            }
        }
        }   
    }
}

//torna os dados de uma cidade em formato de uma linha de TABLE
void city_to_table(gpointer key, gpointer value, gpointer user_data){
    TABLE result = (TABLE) user_data;
    CITY c = (CITY) value;
    int top = 5;
    int i = result->entries;
    int j = 0 ,k = 0, length = 0 ;
    
    //printf("city: %s -> entries :%d\n",c->name,c->entries);
    
    if(c->entries > 0){
    //calcula o tamanho necessario para concatenar os dados dos negocios todos da cidade
    for(; j< c->entries;j++){ 
        //printf("%s\n",c->top[0]);
        length += strlen(c->top[j]);
        }
    result->tab[i] = malloc(sizeof(char) * (length + j + strlen(c->name) + j + 1));
    //concatena os dados dos negocios e coloca-os na table
    snprintf(result->tab[i],strlen(c->name)+2,"%s;",c->name);
    for(k=0 ; k<j;k++){
        strcat(result->tab[i],c->top[k]);
        strcat(result->tab[i],";");
    }
    printf("%d -> %s\n",result->entries,result->tab[i]);
    result->entries++;
    }
}


/* query 6 */
//searches for the top n businesses from each city
TABLE top_businesses_by_city(SGR sgr, int top){
    B_AVERAGE_STARS process = malloc(sizeof(struct b_average_stars));
    process->b_same_name = initHashT(); //hash para guardar o numero medio de estrelas de cada negocio
    process->sgr = sgr;
    process->cities = initHashT(); //hash para descobrir o numero total de cidades diferentes 
    process->top = top;

    printf("Making city and average_stars hashTables...\n");
    //cria table q une negocios com o mesmo nome em elementos singulares
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)b_name_hash, process);
    printf("HashTables created!\n");
    int total_cities = g_hash_table_size(process->cities);

    printf("Calculating average stars of each business...\n");
    //percorrer todas as reviews e vai adicionando estrelas ao negocio correspondente
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)b_add_stars, process);
    printf("Done!\n");
    
    printf("Calculating top of each city...\n");
    //para cada business verifica a cidade a que pertence e verifica se pertence ao top dessa cidade
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)top_city, process);
    printf("Done!\n");
    

    TABLE result = malloc(sizeof(struct table));
    result->entries = 0;
    result->tab = malloc(sizeof(char*) * top);

    
    printf("Turning data into TABLE structure...\n");
    g_hash_table_foreach(process->cities, (GHFunc)city_to_table, result);
    printf("Done!\n");    
    return result;
}
/*query 7
Lista ids de utilizadores e o número total de utilizadores que tenham visitado mais 
de um estado,i.e. que tenham feito reviews em negócios de diferentes estados.*/
typedef struct query7{
    char** list_b;
    GHashTable * hashT_businesses; 
    char * state_atual;
    int total;
}Query7;

void query7_iterator(gpointer key, gpointer value, gpointer user_data){
    char* user_id = r_getUserId(r);
    TABLE t = businesses_reviewed(user_data->sgr, user_id);
    char* b_id_atual = strdup(strsep(&(t[4][0]),","));
    Business b_atual = (Business) g_hash_table_lookup(user_data->hashT_businesses,GINT_TO_POINTER(b_id_atual));
    user_data->state_atual = get_state(b);
    
    int r = 1,i=1;
    while(r!= 0 && t[4]!NULL){
        char* b_id = strdup(strsep(&(t[4][i]),","));
        Business b = (Business)g_hash_table_lookup(user_data->hashT_businesses,GINT_TO_POINTER(b_id));
        if (strcmp (user_data->state_atual,get_state(b))==0) i++;
        else{
            user_data->list[user_data->total] = user_id;
            user_data->total++;
            r=0;
        }
    }
}
TABLE international_users (SGR sgr){
    TABLE r = malloc(sizeof(struct table));
    Query7 pro = malloc(sizeof(struct query7));
    pro->sgr = sgr;
    pro->total = 0;
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)query5_iterator,pro);
    r->tab[5] = strdup(pro->list);
    r->entries[5] = pro->total;
    free(pro);   
    return r;
}


void query9_iterator(gpointer key, gpointer value, gpointer user_data){
 
    TABLE results_table = (TABLE) user_data;
    char * buffer = malloc(100);
    int j=0;
     
    char * word = strdup(results_table->tab[0]);
    char * txt = strdup(r_getText((Reviews) value));
    
    for(int i=0;txt[i]!='\0';i++){
        if(!isspace(txt[i]) && !ispunct(txt[i])){
            buffer[j++] = txt[i];
        }else{
            
            buffer[j++] = '\0';
            if(strcmp(buffer,word)==0){
                int entries = results_table->entries;
                results_table->tab[entries] = strdup(r_getReviewId((Reviews) value));
                results_table->entries++;
                
            }
            j = 0;
        }
        
    }
    
}
/**
\brief QUERY-9:Dada uma palavra,determinar a lista de ids de reviews que a referem no campo text
@param sgr struct sgr
@param top int
@param word string
@returns TABLE apontador para struct table
*/
TABLE reviews_with_word(SGR sgr,char * word){
    int max_lines = g_hash_table_size(sgr->hashT_reviews);
    TABLE results_table = malloc(sizeof(struct table));
    results_table->tab = (char **) malloc(max_lines);
    results_table->entries = 0;

    results_table->tab[0] = strdup(word);
   
    
    g_hash_table_foreach(sgr->hashT_reviews,(GHFunc) query9_iterator,results_table);

    return results_table;
}
