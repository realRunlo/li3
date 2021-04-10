#include "../includes/sgr.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

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



// Iterator for query4
void query4_iterator(gpointer key, gpointer value, gpointer user_data){
    Reviews r = (Reviews) value;
    char* user_id = r_getUserId(r);
    Query4 data = (Query4) user_data;

    if(strcmp(user_id,data->user_id) == 0){
        //Encontra o business correspondente ao business_id na review
        int col = data->column;
        char* b_id = r_getBusinessId(r);
        Business b = (Business) g_hash_table_lookup(data->hashT_businesses,b_id);
        char* b_name = get_name(b);
        
        char* result = (char*) malloc( sizeof(char) * (1 + strlen(b_name) + strlen(b_id)));
        strcat(result,b_id);
        strcat(result,",");
        strcat(result,b_name);
        data->result[col] = (char*) malloc(strlen(result) * sizeof(char));
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



void query6_iterator(gpointer key, gpointer value, gpointer user_data){
    
}


/* query 6 */
//searches for the top n businesses from each city
TABLE top_businesses_by_city(SGR sgr, int top){
    Query6 process = malloc(sizeof(struct query6));
    process->result = NULL;
    process->hashT_reviews = sgr->hashT_reviews;

    //percorre todos os businesses
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)query6_iterator, process);

    free(process);
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
