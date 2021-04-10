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
        B_STARS business = malloc(sizeof(B_STARS));
        business->b_name= b_name;
        business->n_reviews = 0;
        business->total = 0;
        addToHashT(data->b_same_name,GINT_TO_POINTER(b_name),business);
    }

    //verifica se ja foi adicionada a cidade na table
    char* city = get_city(b);
    if(g_hash_table_lookup(data->cities,GINT_TO_POINTER(city)) == NULL){
        CITY c = malloc(sizeof(CITY));
        c->entries = 0;
        c->low_score = 0;
        c->name = city;
        c->top = malloc(sizeof(char*) * data->top);
        addToHashT(data->b_same_name,GINT_TO_POINTER(city),c);
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
    int i = 0;

    //se a cidade ainda nao top negocios guardados, adiciona imediatamente numa posicao livre
    if(c->entries < data->top){
        char stars[20];
        sprintf(stars,"%.2f",average);
        char * result = malloc(sizeof(char) * (strlen(stars) + strlen(b_name) + strlen(b_id) + 2));
        snprintf(result,strlen(stars) + strlen(b_name) + strlen(b_id)+ 2,"%s,%s,%s",stars,b_name,b_id);
        while(c->top[i]) i++; //procura uma posicao vazia
        c->top[i] = result;
        c->low_score = average;
        c->entries++;
    }
    //se o min score da cidade for maior do que o do business nao adiciona
    else if(c->low_score > average);
         else{
             char *buffer = malloc(sizeof(char) * 1000);
             char*b_compare;
             int found = 0;
             int i_lowest = 0;
             float lowest;
             //primeiro verificar se o negocio ja foi adicionado
             while(c->top[i] && found !=1){
                strcpy(buffer,c->top[i]);
                sprintf(strsep(&buffer,","),"%2.f",lowest);
                if (lowest == c->low_score) i_lowest = i; //guarda a posicao do menor score
                if (strcmp(b_name,strsep(&buffer,",")) == 0) found++;
                i++;
             } 
             //se n foi adicionado trocar pelo negocio com o score mais baixo
             if(found == 0){
                char stars[20];
                sprintf(stars,"%.2f",average);
                char * result = malloc(sizeof(char) * (strlen(stars) + strlen(b_name) + strlen(b_id) + 2));
                snprintf(result,strlen(stars) + strlen(b_name) + strlen(b_id)+ 2,"%s,%s,%s",stars,b_name,b_id);
                c->top[i_lowest] = result;
                //atualizar score mais baixo
                float min = 20;
                float s;
                while(c->top[i]){
                    strcpy(buffer,c->top[i]);
                    sprintf(strsep(&buffer,","),"%.2f",s);
                    if(s< min) min = s;
                    i++;
                }
                c->low_score = min;
             }
         }
}

//torna os dados de uma cidade em formato de uma linha de TABLE
void city_to_table(gpointer key, gpointer value, gpointer user_data){
    TABLE result = (TABLE) user_data;
    CITY c = (CITY) value;
    int i = result->entries;
    int j = 0 ,k = 0, length = 0 ;
    //calcula o tamanho necessario para concatenar os dados dos negocios todos da cidade
    for(; c->top[j];j++) length += strlen(c->top[j]) ;

    result->tab[i] = malloc(sizeof(char) * (length + j));
    result->tab[i][0] = '\0';
    //concatena os dados dos negocios e coloca-os na table
    for(k=0 ; k<j;k++){
        strcat(result->tab[i],c->top[k]);
        strcat(result->tab[i],";");
    }
    result->entries++;
}


/* query 6 */
//searches for the top n businesses from each city
TABLE top_businesses_by_city(SGR sgr, int top){
    GHashTable * b_same_name = initHashT(); //hash para guardar o numero medio de estrelas de cada negocio
    GHashTable * cities = initHashT(); //hash para descobrir o numero total de cidades diferentes 
    B_AVERAGE_STARS process = malloc(sizeof(B_AVERAGE_STARS));
    process->b_same_name = b_same_name;
    process->sgr = sgr;
    process->cities = cities;
    process->top = top;

    //cria table q une negocios com o mesmo nome em elementos singulares
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)b_name_hash, process);
    int total_cities = g_hash_table_size(process->cities);


    //percorrer todas as reviews e vai adicionando estrelas ao negocio correspondente
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)b_add_stars, process);

    //para cada business verifica a cidade a que pertence e verifica se pertence ao top dessa cidade
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)top_city, process);

    

    TABLE result = malloc(sizeof(struct table));
    result->entries = 0;
    
    g_hash_table_foreach(process->cities, (GHFunc)city_to_table, result);
    

    //To do
    //Para cada cidade encontrar os top business
    //Criar estrutura para q facilmente se possa modificar os top business numa cidade enquanto se analisa os dados
    //  por exemplo uma matriz para cada cidade
    //Utilizar matriz na table, cada linha sera um cidade e as colunas serao os business
    //free das hashes criadas
    
    return result;
}





typedef struct query9{
       TABLE result; 
        char *word;
        
}*Query9;

void query9_iterator(gpointer key, gpointer value, gpointer user_data){
    
    Reviews rev = (Reviews) value;
    Query9 query_data = (Query9) user_data;
    char buffer[100];
    int j=0,entries_count=0;
    char * txt = strdup(r_getText(rev));

    for(int i=0;txt[i]!='\0';i++){
        if(!isspace(txt[i]) && !ispunct(txt[i])){
            buffer[j++] = txt[i];
        }else{
            if(strcmp(buffer,query_data->word)){
                query_data->result->tab[entries_count] = strdup(r_getReviewId(value));
            }
            j = 0;
        }
    }

    query_data->result->entries = entries_count;
    
}



/**
\brief QUERY-9:Dada uma palavra,determinar a lista de ids de reviews que a referem no campo text
@param sgr struct sgr
@param top int
@param word string
@returns TABLE apontador para struct table
*/
TABLE reviews_with_word(SGR sgr,char * word){
    Query9 data_q9 = malloc(sizeof(struct query9));
    TABLE results_table;
    data_q9->result = results_table;
    data_q9->word = word;

    g_hash_table_foreach(sgr->hashT_reviews,(GHFunc) query9_iterator,data_q9);


    return results_table;
}
