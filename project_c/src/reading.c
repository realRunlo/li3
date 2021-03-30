#include "../includes/reviews.h"
#include "../includes/structs.h"
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 10000


GHashTable *  mapToHash_ReviewsFile(char *filename){

    FILE *  fp = fopen(filename,"r");

    char * buffer = malloc(BUFFER_SIZE);
    Reviews rev;
    GHashTable * table = initHashT();

    while(fgets(buffer,BUFFER_SIZE,fp)!=NULL){
        rev = addReview(rev,buffer);
        addToHashT(table,getReviewId(rev),rev);
    }

    free(buffer);
    fclose(fp);
    return table;
}

