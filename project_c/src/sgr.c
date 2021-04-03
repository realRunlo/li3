#include "../includes/sgr.h"
#include <string.h>

SGR init_sgr(){
    SGR  new_sgr;

    new_sgr.hashT_users = initHashT();
    new_sgr.hashT_reviews= initHashT();
    new_sgr.hashT_businesses = initHashT();

    return new_sgr;
}
/*
void free_sgr(SGR sgr){
    free(&sgr);    //not working
 
}
*/
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file){
    SGR sgr_load = init_sgr();

    mapToHash_ReviewsFile(reviews_file,sgr_load.hashT_reviews);

    //read users

    //read business

    return sgr_load;
}


// Iterator for query2
void query2_iterator(gpointer key, gpointer value, gpointer user_data){
    char* name = get_name((Business) value);
    Query2 data = (Query2) user_data;
    char letter = data->letter;
    if(name[1] == letter){
        data->result = (char*) realloc(data->result,strlen(data->result) + strlen(name));
        strcat(data->result,name);
    }
}


/* query 2 */
//list of businesses whose name starts with char "letter"
TABLE businesses_started_by_letter(SGR sgr, char letter){
    Query2 result = malloc(sizeof(struct query2));
    result->letter = letter;
    result->result = "";
    g_hash_table_foreach(sgr.hashT_users, (GHFunc)query2_iterator,result);
}


