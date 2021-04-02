#include "../includes/reviews.h"
#include "../includes/structs.h"
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 10000

GHashTable *  mapToHash_ReviewsFile(char *filename,GHashTable * hTable){

    FILE *  fp = fopen(filename,"r");

    if(fp!=NULL){
        char * buffer = malloc(BUFFER_SIZE);
        Reviews rev;
        printf("Loading...\n");
        while(fgets(buffer,BUFFER_SIZE,fp)!=NULL){
            rev = addReview(rev,buffer);
            addToHashT(hTable,getReviewId(rev),rev);
        }
        printf("file loaded.\n");

        free(buffer);
        fclose(fp);
        return hTable;
    }else{
        perror("ERROR: ");
    }

    
}

