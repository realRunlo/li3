#include "../includes/reviews.h"
#include <stdlib.h>
#include <string.h>

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

/*  ----------public----------  */

/**
\brief Devolve campo review_id
@param rev apontador para struct reviews
@returns char *
*/
char * r_getReviewId(Reviews  rev){
    return strdup(rev->review_id);
}

/**
\brief Devolve campo user_id
@param rev apontador para struct reviews
@returns char *
*/
char * r_getUserId(Reviews  rev){
    return strdup(rev->user_id);
}

/**
\brief Devolve campo business_id
@param rev apontador para struct reviews
@returns char *
*/
char * r_getBusinessId(Reviews  rev){
    return strdup(rev->business_id);
}

/**
\brief Devolve campo stars
@param rev apontador para struct reviews
@returns float
*/
float r_getStars(Reviews  rev){
    return rev->stars;
}

/**
\brief Devolve campo useful
@param rev Apontador para struct reviews
@returns int
*/
int r_getUseful(Reviews  rev){
    return rev->useful;
}

/**
\brief Devolve campo funny
@param rev Apontador para struct reviews
@returns int
*/
int r_getFunny(Reviews  rev){
    return rev->funny;
}

/**
\brief Devolve campo cool
@param rev Apontador para struct reviews
@returns int
*/
int r_getCool(Reviews  rev){
    return rev->cool;
}

/**
\brief Devolve campo date
@param rev Apontador para struct reviews
@returns char *
*/
char *  r_getDate(Reviews  rev){
    return strdup(rev->date);
}

/**
\brief Devolve campo text
@param rev Apontador para struct reviews
@returns char *
*/
char * r_getText(Reviews rev){
    return strdup(rev->text);
}

int r_checkNewLine(char * str){
    char * test = strdup(str);
    char * seped;
    while((seped =strsep(&test,";"))!=NULL){
        if(strcmp(seped,"")==0)
            return 0;
    }
    return 1;
}

/**
\brief Mapea dados para uma struct review
@param rev Apontador para struct reviews
@param str string
@returns REVIEWS
*/
Reviews addReview(Reviews  rev,char * str){
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
    return rev;
}

