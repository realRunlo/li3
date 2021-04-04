#include "../includes/reviews.h"
#include <stdlib.h>
#include <string.h>

char * getReviewId(Reviews  rev){
    return rev->review_id;
}

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















//pensar se é para fazer no reading ou aqui mhhh