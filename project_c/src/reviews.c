#include "../includes/reviews.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*  ----------private----------  */
struct reviews{
    char * review_id;
    char * user_id;
    char * business_id;
    float stars;
    int useful;
    int funny;
    int cool;
    char * date;
    char * text;
};

/**
 * @brief Valida se é um inteiro
 * 
 * @param arg Recebe uma string
 * @return int 
 */
static int isInt(char* arg){ 
   for(int i = 0;i<arg[i]!='\0';i++){
      if(!isdigit(arg[i]))
          return 0;
   }

 return 1;
}

/*  ----------public----------  */

/**
 * @brief Devolve campo review_id
 * 
 * @param rev apontador para struct reviews 
 * @return char* 
 */
char * r_getReviewId(Reviews  rev){
    return strdup(rev->review_id);
}

/**
 * @brief Devolve campo user_id
 * 
 * @param rev Apontador para struct reviews
 * @return char* 
 */
char * r_getUserId(Reviews  rev){
    return strdup(rev->user_id);
}

/**
 * @brief Devolve campo business_id
 * 
 * @param rev Apontador para struct reviews
 * @return char* 
 */
char * r_getBusinessId(Reviews  rev){
    return strdup(rev->business_id);
}

/**
 * @brief Devolve campo stars
 * 
 * @param rev Apontador para struct reviews
 * @return float 
 */
float r_getStars(Reviews  rev){
    return rev->stars;
}

/**
 * @brief Devolve campo useful
 * 
 * @param rev Apontador para struct reviews
 * @return int 
 */
int r_getUseful(Reviews  rev){
    return rev->useful;
}

/**
 * @brief Devolve campo funny
 * 
 * @param rev Apontador para struct reviews
 * @return int 
 */
int r_getFunny(Reviews  rev){
    return rev->funny;
}

/**
 * @brief Devolve campo cool
 * 
 * @param rev Apontador para struct reviews
 * @return int 
 */
int r_getCool(Reviews  rev){
    return rev->cool;
}

/**
 * @brief Devolve campo date
 * 
 * @param rev Apontador para struct reviews
 * @return char* 
 */
char *  r_getDate(Reviews  rev){
    return strdup(rev->date);
}

/**
 * @brief Devolve campo text
 * 
 * @param rev Apontador para struct reviews 
 * @return char ** 
 */
char * r_getText(Reviews rev){
    return strdup(rev->text);
}

/**
 * @brief Valida linha do ficheiro
 * 
 * @param str linha do ficheiro
 * @return int 1 valida | 0 invalida
 */
int r_checkNewLine(char * str){
    char * test = strdup(str);
    char * seped;
    seped = strsep(&test,";");
    if(strcmp(seped,"")==0) return 0;
    seped = strsep(&test,";");
    if(strcmp(seped,"")==0) return 0;
    seped = strsep(&test,";");
    if(strcmp(seped,"")==0) return 0;
    seped = strsep(&test,";");
    if(atoi(seped)>5) return 0;
    seped = strsep(&test,";");
    if(!isInt(seped)) return 0;
    seped = strsep(&test,";");
    if(!isInt(seped)) return 0;
    seped = strsep(&test,";");
    if(!isInt(seped)) return 0;
    seped = strsep(&test,";");
    if(strcmp(seped,"")==0) return 0;
    seped = strsep(&test,"\n");
    if(strcmp(seped,"")==0) return 0;

    return 1;
}
   
/**
 * @brief Mapea dados para uma struct review
 * 
 * @param rev Apontador para struct reviews 
 * @param str string 
 * @return Reviews 
 */
Reviews addReview(char * str){
    Reviews rev;
    if(r_checkNewLine(str)){
        rev = malloc(sizeof(struct reviews));
        rev->review_id = strdup(strsep(&str,";"));
        rev->user_id = strdup(strsep(&str,";"));
        rev->business_id = strdup(strsep(&str,";"));
        rev->stars = atoi(strsep(&str,";"));
        rev->useful = atoi(strsep(&str,";"));
        rev->funny = atoi(strsep(&str,";"));
        rev->cool = atoi(strsep(&str,";"));
        rev->date = strdup(strsep(&str,";"));
        rev->text = strdup(strsep(&str,"\n"));
    }else{
        rev = NULL;
    }
    
    return rev;
}

