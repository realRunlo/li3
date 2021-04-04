#include "../includes/reading.h"
#include "../includes/user.h"
#include "../includes/reviews.h"
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 10000

/**
\brief Lê informação de um ficheiro de reviews e guarda numa hashtable
@param filename string
@param htable apontador para uma tabela de hash
@returns hTable apontador para uma tabela de hash
*/
GHashTable *  mapToHash_ReviewsFile(char *filename,GHashTable * hTable){

    FILE *  fp = fopen(filename,"r");

    if(fp!=NULL){
        char * buffer = malloc(BUFFER_SIZE);
        Reviews rev;
        printf("Loading...\n");
        while(fgets(buffer,BUFFER_SIZE,fp)!=NULL){
            rev = addReview(rev,buffer);
            addToHashT(hTable,r_getReviewId(rev),rev);
        }
        printf("file loaded.\n");

        free(buffer);
        fclose(fp);
        return hTable;
    }else{
        perror("ERROR: ");
    }

    
}

User createUser(char * buffer){
    User u = malloc(sizeof(struct user));
    setUserId(u,strsep(&buffer,";"));
    setName(u,strsep(&buffer,";"));
    setFriends(u,strsep(&buffer,"\n"));
    return u;
}

void readUser(GHashTable * table, char * filename){

    FILE* f;
    f = fopen(filename,"r");
    if (f==NULL){
        printf("ERROR_FILE_readUser\n");
        exit(1);
    }

    char buffer[400000]; // enough space for 3 excel cells
    User u;
    int i = 0;

    while(fgets(buffer,400000,f)){
        //printf("%d : %s",i,buffer);
        //printf("%d\n",i);
        u = createUser(buffer);
        addToHashT(table,GINT_TO_POINTER((getUserId(u))),u);
        i++;
    }
    fclose(f);
}