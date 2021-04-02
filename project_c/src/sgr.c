#include "../includes/sgr.h"
#include "../includes/structs.h"
#include "../includes/reading.h"
#include <stdlib.h>

SGR init_sgr(){
    SGR  new_sgr = malloc(sizeof(struct sgr));

    new_sgr.hashT_users = initHashT();
    new_sgr.hashT_reviews= initHashT();
    new_sgr.hashT_businesses = initHashT();

    return new_sgr;
}

void free_sgr(SGR sgr){
    free(sgr);    //not working
 
}

SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file){
    SGR sgr_load = init_sgr();

    mapToHash_ReviewsFile(reviews_file,sgr_load.hashT_reviews);

    //read users

    //read business

    return sgr_load;
}