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


GHashTable * getHashT_reviews(SGR sgr){
    return sgr->hashT_reviews;
}

//free de um elemento da hash_table
void free_a_hash_table_entry (gpointer key, gpointer value, gpointer user_data)
{
    g_free (key);
    g_free (value);
}


//free de uma hash_table
void free_all_key_value_entries (GHashTable* table)
{
    g_hash_table_foreach (table, free_a_hash_table_entry, NULL);
    g_hash_table_destroy (table);
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
        data->result[col] = malloc(strlen(name) * sizeof(char));
        data->result[col] = name;
        data->column++;
        data->total++;
    }
}


/* query 2 */
//list of businesses whose name starts with char "letter"
TABLE businesses_started_by_letter(SGR sgr, char letter){
    int max_lines = g_hash_table_size(sgr->hashT_businesses) + 1;
    Query2 process = malloc(sizeof(struct query2));
    char* firstLine = "business_name";
    process->letter = letter;
    process->result = (char ** ) malloc(max_lines * sizeof(*process->result));
    process->result[0] = strdup(firstLine);
    process->column = 1;
    process->total = 0;
    //search every key in the hash for a business name starting with letter
    //if one is found, then result and total are updated 
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)query2_iterator,process);
    
    //turning the results from process into TABLE
    TABLE result = initTable();
    setTab(result,process->result);
    setEntries(result,process->total);
    //free();
    return result;
}

/* query 3 
Dado um id de negócio, determinar a sua informação: nome,
cidade,estado,stars,e número total reviews
query 3*/
typedef struct query3{
        char* b_id;
        int total;
}*Query3;

void q3_iterator (gpointer key, gpointer value, gpointer user_data){
    char* b_id = r_getBusinessId((Reviews) value);
    Query3 data = (Query3) user_data;
    char* l = strdup(data->b_id);
    if(strcmp(b_id,l) == 0)
        data->total+=1;
}

TABLE business_info (SGR sgr, char* business_id){
    TABLE r = init_Sized_Table(2);
    char indicador [50] = "total;b_id;b_nome;b_city;b_state;b_categories";
    setNewLine(r,indicador);
    Business b = (Business) g_hash_table_lookup(sgr->hashT_businesses,
                                            GINT_TO_POINTER(business_id));
    char* b_name = get_name(b);
    char* b_c = get_city(b);
    char* b_s = get_state(b);
    char* b_cat = get_categ(b);
    
    Query3 pro = malloc(sizeof(struct query3));
    pro->b_id = strdup (business_id);
    pro->total = 0;
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)q3_iterator,pro);
    char* res = malloc( sizeof(char) * (strlen(business_id) + strlen(b_name) + 
                        strlen(b_cat)+strlen(b_c)+ strlen(b_s)+10));
    sprintf(res,"%d;%s;%s;%s;%s;%s",pro->total,business_id, b_name,b_c,b_s,b_cat);
    setNewLine(r,res);
    free(pro->b_id);   

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
        snprintf(result,strlen(b_name) + strlen(b_id) + 1,"%s;%s",b_id,b_name);
        data->result[col] = result;
        data->column++;
        
    }
}


/* query 4 */
//searches for the business_id and name of every business a certain user has reviewed
TABLE businesses_reviewed(SGR sgr, char *user_id){
    int max_lines = g_hash_table_size(sgr->hashT_businesses) + 1;
    Query4 process = malloc(sizeof(struct query4));
    char* firstLine = "b_id;b_name";
    process->result = (char ** ) malloc(max_lines * sizeof(*process->result));
    process->result[0] = strdup(firstLine);
    process->user_id = strdup(user_id);
    process->hashT_businesses = sgr->hashT_businesses;
    process->column = 1;
    
    //procura o user_id nas reviews
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)query4_iterator, process);
    TABLE result = initTable();
    setTab(result,process->result);
    setEntries(result,process->column);
    free(process->user_id);
    return result;
}


// query 5 
//Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais
//stars na cidade.A informação associada a cada negócio deve ser o seu id e nome.
typedef struct query5{
        TABLE t;
        char* city;
        float stars;
        GHashTable * hashT_business;
        GHashTable * h_business_visitado;
}*Query5;

void query5_iterator(gpointer key, gpointer value, gpointer user_data){
    Reviews r = ((Reviews)value);
    float b_stars = r_getStars((Reviews) value);
    Query5 data = (Query5) user_data;
    char* city_data = strdup(data->city);
    if(b_stars >= (data->stars)){
        char* b_id = strdup(r_getBusinessId(r));
        gboolean r = g_hash_table_insert(data->h_business_visitado,b_id,"a");
        if(r){
            Business b = (Business) g_hash_table_lookup(data->hashT_business,
                                            GINT_TO_POINTER(b_id));
            char* b_city = get_city(b);
            if(strcmp(b_city,city_data) == 0){
                char* b_name = get_name(b);
                char* a = malloc( sizeof(char) * (strlen(b_id) + strlen(b_name) + 5));
                sprintf(a,"%s;%s",b_id, b_name);
                setNewLine(data->t,a);
            }
        }
    }
}

TABLE businesses_with_stars_and_city (SGR sgr, float stars,char* city){
    Query5 pro = malloc(sizeof(struct query5));
    int max_lines = g_hash_table_size(sgr->hashT_businesses);
    pro->t = init_Sized_Table(max_lines);
    char ind [16] = "b_id;b_name";
    setNewLine(pro->t,ind);
    pro->city = strdup (city);
    pro->stars = stars;
    pro->hashT_business = sgr->hashT_businesses;
    pro->h_business_visitado = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)query5_iterator,pro);  
    free(pro->city);
    g_hash_table_destroy(pro->hashT_business);   
    g_hash_table_destroy(pro->h_business_visitado);   
    return pro->t;
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
    char* b_id;
    char* b_name;
    int n_reviews;
    float total;
}*B_STARS;

//user_data para business_average_stars
typedef struct b_average_stars{
    SGR sgr;
    GHashTable * b_same;
    GHashTable * cities;
    int top;
    char* condition; //pode ser utilizado pelo query 8 para guardar a categoria procurada
    char** results;
    int entries; //numero de linhas preenchidas de results
    float lowScore;
}*B_AVERAGE_STARS;




//Cria uma hash com todas as diferentes cidades 
void city_hash(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Business b = (Business) value;

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

//para cada review vai a table "b_same" e adiciona no negocio correspondente o numero de estrelas
void b_add_stars(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Reviews r = (Reviews) value;
    char *b_id = r_getBusinessId(r);
    
    //encontra o id do negocio da review
    Business b = g_hash_table_lookup(data->sgr->hashT_businesses,GINT_TO_POINTER(b_id));
    char* b_name = get_name(b);

    //verifica se ja existe um negocio na table de media de estrelas com o mesmo id
    if(g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id)) == NULL)
    {
        B_STARS business = malloc(sizeof(struct b_stars));
        business->b_id = b_id;
        business->b_name= b_name;
        business->n_reviews = 1;
        business->total = r_getStars(r);
        addToHashT(data->b_same,GINT_TO_POINTER(b_id),business);
    }
    //se ja existir da update no numero de reviews e no total de estrelas
    else{
        B_STARS update = g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id));
        update->n_reviews++;
        update->total += r_getStars(r);
    }
}


//verifica a cidade de cada business, e dependendo do seu average score, atualiza o top dessa cidade    
void top_city(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Business b = (Business) value;
    GHashTable * b_same_name = data->b_same;
    GHashTable * cities = data->cities;
    char* b_name    = get_name(b);
    char* b_id      = get_id(b);
    char* city_name = get_city(b);
    B_STARS bStar   = g_hash_table_lookup(b_same_name,GINT_TO_POINTER(b_id));
    CITY c          = g_hash_table_lookup(cities,GINT_TO_POINTER(city_name));
    
    //verifica se houve reviews para o negocio em questao
    if(bStar != NULL){
    float average   = bStar->total / bStar->n_reviews;
    int i = 0; int top = data->top;
    
    //verifica se o negocio tem reviews e caso tenha o top cheio, se o score do negocio e menor do que o minimo do top
    //caso a cidade ja n tenha espaco no top e o score do negocio e menor do que o minimo do top
    if(c->entries == top && average < c->low_score);
    else{
        char stars[20]; //string para colocar as estrelas medias
        sprintf(stars,"%.2f",average); //float to string
        char * result = malloc(sizeof(char) * (strlen(stars) + strlen(b_name) + strlen(b_id) + 3)); //declaracao da string q sera colocada
        snprintf(result,strlen(stars) + strlen(b_id) + strlen(b_name)+ 3,"%s;%s;%s",stars,b_id,b_name);
        //caso em que ainda nao foram adicionados nenhuns negocios
        if(c->entries == 0){
            c->top[0] = result;
            c->low_score = average;
            c->entries++;
        }
        else{
            //verificar se o negocio ja foi adicionado
            i = 0;
            size_t maxLen = strlen(result);
            while(i < c->entries){
                if(strlen(c->top[i]) > maxLen) maxLen = strlen(c->top[i]);
                i++;
            }
            char*buffer = malloc(sizeof(char) * (maxLen + 1));    
            char *pointer = buffer;
            int found = 0;
            int i_lowest = 0;
            float lowest;
            i=0;
            while(i < c->entries && found !=1){
                buffer = pointer;
                buffer[0] = '\0';
                strcpy(buffer,c->top[i]);
                lowest = atof(strsep(&buffer,";"));  //torna a string da media de estrelas em um float  
                if (lowest == c->low_score) i_lowest = i; //guarda a posicao do menor score
                if (strcmp(b_id,strsep(&buffer,";")) == 0) found++;
                i++;
            }
            free(pointer);
            //se o negocio ainda n foi adicionado(e o seu score e superior ao minimo da cidade) mas o top ja esteja cheio, necessario trocar pelo de menor score
            if(found == 0 && c->entries == data->top && average > c->low_score){
                i = 0;
                maxLen = strlen(result);
                while(i < c->entries){
                    if(strlen(c->top[i]) > maxLen) maxLen = strlen(c->top[i]);
                    i++;
                }
                c->top[i_lowest] = result;
                //atualizar score mais baixo
                float min = 20;
                float s = 20;
                char*buffer2 = malloc(sizeof(char) * (maxLen + 1));
                char *pointer2 = buffer2;
                i=0;
                while(i < top){
                    buffer2 = pointer2;
                    buffer2[0] = '\0';
                    strcpy(buffer2,c->top[i]);
                    s = (float) atof(strsep(&buffer2,";"));
                    if(s< min) min = s;
                    i++;
                }
                c->low_score = min;
                free(pointer2);
            }
            //se a cidade ainda nao tem top negocios guardados, adiciona imediatamente numa posicao livre
            if(found == 0 && c->entries < data->top){
                c->top[c->entries] = result;
                if(average < c->low_score) c->low_score = average;
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
    int j = 0 ,k = 0, length = 0 ;
    
    //printf("city: %s -> entries :%d\n",c->name,c->entries);
    
    if(c->entries > 0){
    //calcula o tamanho necessario para concatenar os dados dos negocios todos da cidade
    for(; j< c->entries;j++){ 
        //printf("%s\n",c->top[0]);
        length += strlen(c->top[j]) + 2;
        }
    char  buff[length + j + strlen(c->name) + j + 1];
    buff[0] = '\0';
    //concatena os dados dos negocios e coloca-os na table
    snprintf(buff,strlen(c->name)+2,"%s-",c->name);
    for(k=0 ; k<j;k++){
        strcat(buff,c->top[k]);
        strcat(buff,"-");
    }
    setNewLine(result,buff);
    }
}


/* query 6 */
//searches for the top n businesses from each city
TABLE top_businesses_by_city(SGR sgr, int top){
    B_AVERAGE_STARS process = malloc(sizeof(struct b_average_stars));
    process->b_same = initHashT(); //hash para guardar o numero medio de estrelas de cada negocio
    process->sgr = sgr;
    process->cities = initHashT(); //hash para descobrir o numero total de cidades diferentes 
    process->top = top;

    printf("Making city hashTable...");
    //cria table em q cada elemento e uma cidade distinta
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)city_hash, process);
    printf("Done!\n");
    int total_cities = g_hash_table_size(process->cities);

    printf("Calculating average stars of each business...");
    //percorrer todas as reviews e vai criando uma hash de negocios para guardar o numero total de reviews dele e a soma das estrelas
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)b_add_stars, process);
    printf("Done!\n");
    
    printf("Calculating top of each city...");
    //para cada business verifica a cidade a que pertence e verifica se pertence ao top dessa cidade
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)top_city, process);
    printf("Done!\n");
    

    TABLE result = initTable();
    setEntries(result,0);
    setTab(result,malloc(sizeof(char*) * (total_cities + 1)));
    setNewLine(result,"city-stars;b_id;b_name-");
    
    printf("Turning data into TABLE structure...\n");
    g_hash_table_foreach(process->cities, (GHFunc)city_to_table, result);
     printf("Done!\n"); 

    free_all_key_value_entries(process->b_same);   
    free_all_key_value_entries(process->cities);     
    return result;
}

//query 7
//Lista ids de utilizadores e o número total de utilizadores que tenham visitado mais 
//de um estado,i.e. que tenham feito reviews em negócios de diferentes estados.

typedef struct query7{
    TABLE t;
    GHashTable * h_user_visitado;
    GHashTable * hashT_businesses;
    char * state_atual;
    int total;
    GHashTable * h_state;
}*Query7;

void check_state_iterator(gpointer key, gpointer value, gpointer user_data){
    Query7 data = (Query7) user_data;
    data->h_state = g_hash_table_new(g_str_hash, g_str_equal);
    int t = g_slist_length((GSList*)value);
    GSList* iterator = NULL;
    if(t>1){
        for (iterator = (GSList*)value; iterator; iterator = iterator->next) {
            char* b_id = strdup(iterator->data);
            Business b = (Business) g_hash_table_lookup(data->hashT_businesses,
                                            GINT_TO_POINTER(b_id));
            char* b_state = get_state(b);
            g_hash_table_insert(data->h_state, b_state,"a");
        }
        if((g_hash_table_size(data->h_state))>=2){
            setNewLine(data->t,key);
            data->total++;
        }
    } 
}



void query7_iterator(gpointer key, gpointer value, gpointer user_data){
    char* user_id = strdup(r_getUserId((Reviews) value));
    char* b_id =  strdup(r_getBusinessId((Reviews) value));
    Query7 data = (Query7) user_data;
    g_hash_table_insert(data->h_user_visitado, user_id,
        g_slist_append(g_hash_table_lookup(data->h_user_visitado, user_id),b_id));
}
void destroy(gpointer key, gpointer value, gpointer data) {
 g_slist_free(value);
}

TABLE international_users (SGR sgr){
    Query7 pro = malloc(sizeof(struct query7));
    int max_lines = g_hash_table_size(sgr->hashT_reviews);
    pro->t = init_Sized_Table(max_lines);
    char ind [15] = "user_id;total";
    setNewLine(pro->t,ind);
    pro->hashT_businesses=sgr->hashT_businesses;
    pro->h_user_visitado = g_hash_table_new(g_str_hash, g_str_equal);
    pro->h_state = g_hash_table_new(g_str_hash, g_str_equal);
    pro->total = 0;
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)query7_iterator,pro);
    g_hash_table_foreach(pro->h_user_visitado, (GHFunc)check_state_iterator,pro);
    g_hash_table_destroy(pro->h_state);
    g_hash_table_destroy(pro->hashT_businesses);
    g_hash_table_foreach(pro->h_user_visitado, destroy, NULL);
    g_hash_table_destroy(pro->h_user_visitado);
    free(pro->state_atual);
    char total [2];
    sprintf(total,"%d",pro->total);
    setNewLine(pro->t,total);
    return pro->t;
}



int cmp_category(char* c_condition,char* c_comparing){
    int i = 0, j = 0;
    if(c_condition[0] == '\0' && c_comparing[0] == '\0') return 0;
    for(;c_comparing[j] != '\0' ;j++){
        if(c_condition[i] == '\0' && (c_comparing[j] == ',' || c_comparing[j] == ';')) return 0;
        else if(c_condition[i] == c_comparing[j]) i++;
            else if(c_condition[i] != c_comparing[j]) i = 0;
    }
    return 1;
}


//para cada review vai a table "b_same" e adiciona no negocio correspondente o numero de estrelas
void b_category(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Reviews r = (Reviews) value;
    char *b_id = r_getBusinessId(r);
    
    //encontra o id do negocio da review
    Business b = g_hash_table_lookup(data->sgr->hashT_businesses,GINT_TO_POINTER(b_id));
    char* b_category = get_categ(b);

    //verifica se o negocio reviewed pertence a categoria procurada
    if(cmp_category(data->condition,b_category) == 0){
        //verifica se ja existe um negocio na table de media de estrelas com o mesmo id
        if(g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id)) == NULL)
        {
            char* b_name = get_name(b);
            B_STARS business = malloc(sizeof(struct b_stars));
            business->b_id = b_id;
            business->b_name= b_name;
            business->n_reviews = 1;
            business->total = r_getStars(r);
            addToHashT(data->b_same,GINT_TO_POINTER(b_id),business);
        }
        //se ja existir da update no numero de reviews e no total de estrelas
        else{
            B_STARS update = g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id));
            update->n_reviews++;
            update->total += r_getStars(r);
        }
    }

}





//procura dentro da hash, os business com top score 
void top_category(gpointer key, gpointer value, gpointer user_data){
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    B_STARS b = (B_STARS) value;
    GHashTable * b_same_name = data->b_same;
    char** results  = data->results; 
    char* b_name    = b->b_name;
    char* b_id      = b->b_id;    
    float average   = b->total / b->n_reviews;
    int i = 0; int top = data->top;
    //verifica se o negocio tem reviews e caso tenha o top cheio, se o score do negocio e menor do que o minimo do top
    //caso a cidade ja n tenha espaco no top e o score do negocio e menor do que o minimo do top
    if(data->entries == top && average < data->lowScore);
    else{
        char stars[20]; //string para colocar as estrelas medias
        sprintf(stars,"%.2f",average); //float to string
        char * result = malloc(sizeof(char) * (strlen(stars) + strlen(b_name) + strlen(b_id) + 3)); //declaracao da string q sera colocada
        snprintf(result,strlen(stars) + strlen(b_id) + strlen(b_name)+ 3,"%s;%s;%s",stars,b_id,b_name);
        //caso em que ainda nao foram adicionados nenhuns negocios
        if(data->entries == 0){
            results[1] = result;
            data->lowScore = average;
            data->entries++;
        }
        else{
            //verificar se o negocio ja foi adicionado
            i = 1;
            size_t maxLen = strlen(result);
            while(i < data->entries+1){
                if(strlen(results[i]) > maxLen) maxLen = strlen(results[i]);
                i++;
            }
            i = 1;
            char*buffer = malloc(sizeof(char) * (maxLen +1));
            buffer[0] = '\0';
            char *pointer = buffer;

            int found = 0;
            int i_lowest = 0;
            float lowest;
            while(i < data->entries+1 && found !=1){
                buffer = pointer;
                strcpy(buffer,results[i]);
                lowest = atof(strsep(&buffer,";"));  //torna a string da media de estrelas em um float 
                if (lowest == data->lowScore) i_lowest = i; //guarda a posicao do menor score
                if (strcmp(b_id,strsep(&buffer,";")) == 0) found++;
                i++;
            }
            free(pointer);
            //se o negocio ainda n foi adicionado(mas tem score superior ao minimo da categoria) mas o top ja esteja cheio, necessario trocar pelo de menor score
            if(found == 0 && data->entries == top && average > data->lowScore){
                i = 1;
                maxLen = strlen(result);
                while(i < data->entries+1){
                    if(strlen(results[i]) > maxLen) maxLen = strlen(results[i]);
                    i++;
                }
                i=1;
                results[i_lowest] = result;
                //atualizar score mais baixo
                float min = 20;
                float s = 20;
                char*buffer2 = malloc(sizeof(char) * (maxLen + 1));
                buffer2[0] = '\0';
                char *pointer2 = buffer2;
                while(i < data->entries+1){
                    buffer2 = pointer2;
                    strcpy(buffer2,results[i]);
                    s = (float) atof(strsep(&buffer2,";"));
                    if(s< min) min = s;
                    i++;
                }
                data->lowScore = min;
                free(pointer2);
                
            }
            //se a cidade ainda nao tem top negocios guardados, adiciona imediatamente numa posicao livre
            if(found == 0 && data->entries < data->top){
                results[data->entries+1] = result;
                //atualizar min score se necessario
                if (average < data->lowScore) data->lowScore = average;
                data->entries++;
                //printf("cidade %s\n",c->top[i]);
            }
        }
    }   
}


/* query 8 */
//calcula os top n negocios de uma dada categoria
TABLE top_businesses_with_category(SGR sgr, int top, char *category){
    B_AVERAGE_STARS process = malloc(sizeof(struct b_average_stars));
    process->b_same = initHashT(); //hash para guardar o numero medio de estrelas de cada negocio
    process->sgr = sgr;
    process->top = top;
    process->condition = strdup(category);
    process->results = malloc(sizeof(char*) * (top + 1));
    process->results[0] = strdup("stars;b_id;b_name");
    process->entries = 0;

    //percorrer todas as reviews e vai criando uma hash de negocios para guardar o numero total de reviews dele e a soma das estrelas
    printf("Calculating average stars of each business...");
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)b_category, process);
    printf("Done!\n");

    //calcular os top negocios e guardar numa matriz de top linhas
    printf("Calculating top businesses...");
    g_hash_table_foreach(process->b_same, (GHFunc)top_category, process);
    printf("Done!\n");
    
    //tornar a matriz em forma TABLE
    printf("entries = %d\n",process->entries);
    printf("Turning data into TABLE structure...\n");
    TABLE result = initTable();
    setEntries(result,process->entries+1);
    setTab(result,process->results);
    printf("Done!\n");

    return result;
}

int wordInString(char *str,char * word){
    char * buffer = malloc(strlen(str) + 1);
    int j=0;
    for(int i=0;str[i]!='\0';i++){
        if((!isspace(str[i]) && !ispunct(str[i])) || str[i] == '\''){
            buffer[j++] = str[i];
        }else{
            
            buffer[j] = '\0';
            if(strcmp(buffer,word)==0){
                free(buffer);
                return 1;
            }
            j = 0;
            
        }
        
    }
     buffer[j] = '\0';
        if(strcmp(buffer,word)==0){
            free(buffer);
            return 1;
        }
    free(buffer);
    return 0;
}

typedef struct query9{
        TABLE t;
        char * word;
}*Query9;

 
void query9_iterator(gpointer key, gpointer value, gpointer user_data){ 
    Query9 data = (Query9) user_data;
    char * word = strdup(data->word);
    char * txt = r_getText((Reviews) value);
    
    if(wordInString(txt,word))
        setNewLine(data->t,r_getReviewId((Reviews) value));
    
        
    
   
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
    Query9 query_data = malloc(sizeof(struct query9));
    query_data->t = init_Sized_Table(max_lines);
    query_data->word = strdup(word);
 
    setNewLine(query_data->t,"review_id");
    
    
    g_hash_table_foreach(sgr->hashT_reviews,(GHFunc) query9_iterator,query_data);
    
    return query_data->t;
}
