#include "../includes/reading.h"
#include "../includes/user.h"
#include "../includes/reviews.h"
#include "../includes/business.h"
#include <stdio.h>
#include <string.h>
#define BUS_BUFFER_SIZE 10000
#define REV_BUFFER_SIZE 10000
#define USERS_BUFFER_SIZE 100000

/**
\brief Lê informação de um ficheiro de reviews e guarda numa hashtable
@param filename - nome do ficheiro
@param htable apontador para uma tabela de hash
*/
void readReviews(GHashTable * hTable,char * filename){

    FILE *  fp = fopen(filename,"r");
    if (fp==NULL){
        perror("ERROR: ");
        return;
    } else{
        Reviews rev = NULL;
        char buff[REV_BUFFER_SIZE]; 
        buff[0] = '\0';
        size_t linelen = USERS_BUFFER_SIZE, bufflen = 0 , maxlen = 0;
        char * line = malloc(sizeof(char) * REV_BUFFER_SIZE);
        fgets(buff,REV_BUFFER_SIZE,fp); // ignora primeira linha 
        int read = 0;
        while(fgets(buff,REV_BUFFER_SIZE,fp)){
            line[0] = '\0';
            bufflen = strlen(buff);
            maxlen = bufflen;
            if (linelen <= bufflen){
                linelen += maxlen + linelen;
                line = realloc(line, linelen);
            }
            strcat(line, buff);
            while(bufflen == REV_BUFFER_SIZE - 1 && buff[REV_BUFFER_SIZE-2] != '\n'){
                if(fgets(buff, REV_BUFFER_SIZE,fp)){
                bufflen = strlen(buff);
                maxlen += bufflen;
                if (linelen <= maxlen){
                linelen += maxlen + linelen;
                line = realloc(line, linelen);
                }
                strcat(line, buff);
                }
            }
           if(r_checkNewLine(line)){
                rev = addReview(rev,line);
                addToHashT(hTable,r_getReviewId(rev),rev);
            }
           
        }
        free(line);
    }
    fclose(fp);
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
        ssize_t linelen = 0; size_t line_buf_len = 0;
        char * line = NULL;
        linelen = getline(&line,&line_buf_len,f); // ignora primeira linha 
        linelen = getline(&line,&line_buf_len,f);
        while(linelen >=0)
        {
            if(u_checkNewLine(line) == 0){
                u = createUser(line);
                addToHashT(table,GINT_TO_POINTER((getUserId(u))),u);
            }
            linelen = getline(&line,&linelen,f);
        }
        free(line);
        fclose(f);
    }
}

/**
\brief Lê informação de um ficheiro de businesses e guarda numa hashtable
@param filename - nome do ficheiro
@param htable apontador para uma tabela de hash
*/
void readBusiness (GHashTable * hash, char * filename ){
    char buffer [BUS_BUFFER_SIZE];
    Business b;
    FILE *f = fopen(filename,"r");

    if(f!=NULL){
        int r =0;
        fgets(buffer,BUS_BUFFER_SIZE,f);
        while(fgets(buffer,BUS_BUFFER_SIZE,f)){
            char cpy [BUS_BUFFER_SIZE];
            strcpy(cpy,buffer);
            r = check_line(cpy);
            if(r == 1){
                b = create_b(buffer);
                addToHashT(hash,GINT_TO_POINTER(get_id(b)),b);
            }
        }
    }
    else  perror("ERROR: ");
}
