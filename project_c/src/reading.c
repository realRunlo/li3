#include "../includes/reading.h"
#include "../includes/user.h"
#include "../includes/reviews.h"
#include "../includes/business.h"
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
        
        while(fgets(buffer,BUFFER_SIZE,fp)!=NULL){
            rev = addReview(rev,buffer);
            addToHashT(hTable,r_getReviewId(rev),rev);
        }

        free(buffer);
        fclose(fp);
        printf("Reviews loaded.\n");
        return hTable;
    }else{
        perror("ERROR: ");
    }

    
}

User createUser(char * buffer){
    User u = malloc(sizeof(User));
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
    }
    else{
    
        char buffer[400000]; // espaco suficiente para os exemplos do input file
        User u;
        int i = 0;

        while(fgets(buffer,400000,f)){
            //printf("%d : %s",i,buffer);
            //printf("%d\n",i);
            u = createUser(buffer);
            addToHashT(table,GINT_TO_POINTER((getUserId(u))),u);
            i++;
        }
        printf("users file loaded.\n");
    }
    fclose(f);
    printf("Users loaded.\n");
}


void readBusiness (GHashTable * hash, char fic [] ){
    char buffer [5000];
    Business b;
    FILE *f = fopen(fic,"r");

    if(f!=NULL){
        int i=0;
        while(fgets(buffer,1024,f)){
            char dest [5000];
            strcpy(dest,buffer);
            int r = check_line(dest);
            if(r == 1){
                b = create_b(buffer);
                addToHashT(hash,GINT_TO_POINTER(get_id(b)),b);
                i++;
            }
        }
        //int t = g_hash_table_size(hash);
        //printf("%d\n",t);
        //g_hash_table_foreach(hash, (GHFunc)iterator, "%s;%s;%s;%s;%s");
        printf("Business loaded.\n");
    }
    else printf("ERROR opening file\n");
}
