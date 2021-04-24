#include "../includes/reading.h"
#include "../includes/user.h"
#include "../includes/reviews.h"
#include "../includes/business.h"
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 10000
#define USERS_BUFFER_SIZE 100000

/**
\brief Lê informação de um ficheiro de reviews e guarda numa hashtable
@param filename - nome do ficheiro
@param htable apontador para uma tabela de hash
*/
void readReviews(GHashTable * hTable,char * filename){

    FILE *  fp = fopen(filename,"r");
    if(fp!=NULL){
        char * buffer = malloc(BUFFER_SIZE);
        fgets(buffer,BUFFER_SIZE,fp);
        Reviews rev;
        while(fgets(buffer,BUFFER_SIZE,fp)!=NULL ){
            rev = addReview(rev,buffer);
            addToHashT(hTable,r_getReviewId(rev),rev);
        }

        free(buffer);
        fclose(fp);
        printf("Reviews loaded.\n");
    }else{
        perror("ERROR: ");
    }

    
}

/**
\brief Lê informação de um ficheiro de users e guarda numa hashtable
@param filename - nome do ficheiro
@param htable apontador para uma tabela de hash
*/
void readUser(GHashTable * table, char * filename){
    FILE* f;
    f = fopen(filename,"r");
    if (f==NULL){
        printf("ERROR_FILE_readUser\n");
    }
    else{
    
        User u;
        char buff[USERS_BUFFER_SIZE]; // espaco suficiente para os exemplos do input file
        buff[0] = '\0';
        size_t linelen = USERS_BUFFER_SIZE, bufflen = 0 , maxlen = 0;
        char * line = malloc(sizeof(char) * USERS_BUFFER_SIZE);
        if(fgets(buff,USERS_BUFFER_SIZE,f)){ // ignora primeira linha 
        int read = 0;
        while(fgets(buff,USERS_BUFFER_SIZE,f))
        {
            line[0] = '\0';
            bufflen = strlen(buff);
            maxlen = bufflen;
            if (linelen <= bufflen){
                linelen += maxlen + linelen;
                line = realloc(line, linelen);
            }
            strcat(line, buff);
            while(bufflen == USERS_BUFFER_SIZE - 1 && buff[USERS_BUFFER_SIZE-2] != '\n'){
                if(fgets(buff, USERS_BUFFER_SIZE, f)){
                bufflen = strlen(buff);
                maxlen += bufflen;
                if (linelen <= maxlen){
                linelen += maxlen + linelen;
                line = realloc(line, linelen);
                }
                strcat(line, buff);
                }
            }
            u = createUser(line);
            addToHashT(table,GINT_TO_POINTER((getUserId(u))),u);
            
        }
        }
        free(line);
    fclose(f);
    printf("Users loaded.\n");
    }
}

/**
\brief Lê informação de um ficheiro de businesses e guarda numa hashtable
@param filename - nome do ficheiro
@param htable apontador para uma tabela de hash
*/
void readBusiness (GHashTable * hash, char * filename ){
    char buffer [5000];
    Business b;
    FILE *f = fopen(filename,"r");

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
        printf("Business loaded.\n");
    }
    else  perror("ERROR: ");
}
