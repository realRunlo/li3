#include "../includes/reading.h"
#include "../includes/user.h"
#include "../includes/reviews.h"
#include "../includes/business.h"
#include <stdio.h>
#include <string.h>


/**
 * @brief Lê informação de um ficheiro de reviews e guarda numa hashtable
 * 
 * @param hTable Apontador para uma tabela de hash
 * @param filename Nome do ficheiro
 */
void readReviews(GHashTable * hTable,char * filename){

    FILE *  fp = fopen(filename,"r");
    if (fp==NULL){
        perror("ERROR: ");
        return;
    } else{
        Reviews r;
        ssize_t linelen = 0; size_t line_buf_len = 0;
        char * line = NULL;
        linelen = getline(&line,&line_buf_len,fp); // ignora primeira linha 
        linelen = getline(&line,&line_buf_len,fp);
        while(linelen >=0)
        {
            if(r_checkNewLine(line)){
                r = addReview(r,line);
                addToHashT(hTable,r_getReviewId(r),r);
            }
            linelen = getline(&line,&linelen,fp);
        }
        free(line);
        fclose(fp);
    }
}


/**
 * @brief Lê informação de um ficheiro de users e guarda numa hashtable
 * 
 * @param table Apontador para uma tabela de hash
 * @param filename Nome do ficheiro
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
 * @brief Lê informação de um ficheiro de businesses e guarda numa hashtable
 * 
 * @param hash apontador para uma tabela de hash
 * @param filename nome do ficheiro
 */
void readBusiness (GHashTable * hash, char * filename ){
    FILE *f = fopen(filename,"r");
    if(f!=NULL){
        Business b;
        ssize_t linelen = 0; size_t line_buf_len = 0;
        char * line = NULL;
        linelen = getline(&line,&line_buf_len,f); // ignora primeira linha 
        linelen = getline(&line,&line_buf_len,f);
        while(linelen >=0)
        {
            if(check_line(line)){
                b = create_b(line);
                addToHashT(hash,GINT_TO_POINTER(get_id(b)),b);
            }
            linelen = getline(&line,&linelen,f);
        }
        free(line);
        fclose(f);
    }
    else  perror("ERROR: ");
}
