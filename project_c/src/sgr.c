#include "../includes/sgr.h"
#include <string.h>

typedef struct sgr{

    GHashTable * hashT_users;
    GHashTable * hashT_businesses;
    GHashTable * hashT_reviews;

};

typedef struct table{

   char ** tab;
   int entries;

};

/**
\brief Inicializador de dados SGR
@returns new_sgr stuct sgr
*/
SGR init_sgr(){
    SGR  new_sgr;

    new_sgr.hashT_users = initHashT();
    new_sgr.hashT_reviews= initHashT();
    new_sgr.hashT_businesses = initHashT();

    return new_sgr;
}

/*
void free_sgr(SGR sgr){
    free(sgr);    //not working
 
}
*/
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file){
    SGR sgr_load = init_sgr();

    mapToHash_ReviewsFile(reviews_file,sgr_load.hashT_reviews);

    readUser(sgr_load.hashT_users,users_file);

    readBusiness (sgr_load.hashT_businesses,business_file);

    return sgr_load;
}


// Iterator for query2
void query2_iterator(gpointer key, gpointer value, gpointer user_data){
    char* name = get_name((Business) value);
    Query2 data = (Query2) user_data;
    char letter = data->letter;
    if(name[1] == letter){
        data->result = (char*) realloc(data->result,strlen(data->result) + strlen(name) + 1);
        strcat(data->result,name);
        strcat(data->result,",");
        data->total++;
    }
}


/* query 2 */
//list of businesses whose name starts with char "letter"
TABLE businesses_started_by_letter(SGR sgr, char letter){
    Query2 process = malloc(sizeof(struct query2));
    process->letter = letter;
    process->result = "";
    process->total = 0;
    //search every key in the hash for a business name starting with letter
    //if one is found, then result and total are updated 
    g_hash_table_foreach(sgr.hashT_users, (GHFunc)query2_iterator,process);

    //turning the results from process into TABLE
    TABLE result = malloc(sizeof(struct table));
    result->tab[2] = strdup(process->result);
    result->entries = process->total;
    free(process);
    return result;
}


// Iterator for query4
void query4_iterator(gpointer key, gpointer value, gpointer user_data){
    Reviews r = (Reviews) value;
    Query4 data = (Query4) user_data;

    if(strcmp(r->user_id,data->user_id)){
        //Encontra o business correspondente ao business_id na review
        Business b = (Business) g_hash_table_lookup(data->hashT_businesses, r->business_id);
        data->result = (char*) realloc(data->result,strlen(data->result) + strlen(r->business_id) + strlen(b->name) + 2);
        strcat(data->result,r->business_id);
        strcat(data->result,",");
        strcat(data->result,b->name);
        strcat(data->result,",");
    }
}


/* query 4 */
//searches for the business_id and name of every business a certain user has reviewed
TABLE businesses_reviewed(SGR sgr, char *user_id){
    Query4 process = malloc(sizeof(struct query4));
    process->result = "";
    process->user_id = strdup(user_id);
    process->hashT_businesses = sgr.hashT_businesses;

    //procura o user_id nas reviews
    g_hash_table_foreach(sgr.hashT_reviews, (GHFunc)query4_iterator, process);
    TABLE result = malloc(sizeof(struct table));
    result->tab[4] = strdup(process->result);
    free(process);
    return result;
}



void query6_iterator(gpointer key, gpointer value, gpointer user_data){
    
}


/* query 6 */
//searches for the top n businesses from each city
TABLE top_businesses_by_city(SGR sgr, int top){
    Query6 process = malloc(sizeof(struct query6));
    process->result = NULL;
    process->hashT_reviews = sgr.hashT_reviews;

    //percorre todos os businesses
    g_hash_table_foreach(sgr.hashT_businesses, (GHFunc)query6_iterator, process);

    free(process);
}



typedef struct query9{
       TABLE result; 
        char *word;
        
}*Query9;

void query9_iterator(gpointer key, gpointer value, gpointer user_data){
    Query9 process = malloc(sizeof(struct query9));
    Reviews rev = (Reviews) value;

    for(int i=0;rev->text!='\0'){
        for(int j=;rev->text!='\0';j++){

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

}