#include "../includes/reviews.h"
#include <stdlib.h>
#include <string.h>

typedef struct reviews{
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
\brief Mapea dados de uma linha de texto para uma estrutrutua review
@param rev apontador para struct reviews
@param str string
@returns rev apontador para struct reviews
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
    rev->text = strdup(strsep(&str,";"));
    return rev;
}

char * r_getReviewId(Reviews  rev){
    return rev->review_id;
}
char * r_getUserId(Reviews  rev){
    return rev->user_id;
}
char * r_getBusinessId(Reviews  rev){
    return rev->business_id;
}

int r_getStars(Reviews  rev){
    return rev->stars;
}
int r_getUseful(Reviews  rev){
    return rev->useful;
}
int r_getFunny(Reviews  rev){
    return rev->funny;
}
int r_getCool(Reviews  rev){
    return rev->cool;
}
char *  r_getDate(Reviews  rev){
    return rev->date;
}
char * r_getText(Reviews rev){
    return rev->text;
}

