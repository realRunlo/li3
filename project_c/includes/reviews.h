#ifndef ___REVIEWS_H___
#define ___REVIEWS_H___


typedef struct reviews * Reviews;

Reviews addReview(Reviews  rev,char * str);


char * r_getReviewId(Reviews  rev);
char * r_getUserId(Reviews  rev);
char * r_getBusinessId(Reviews  rev);
float r_getStars(Reviews  rev);
int r_getUseful(Reviews  rev);
int r_getFunny(Reviews  rev);
int r_getCool(Reviews  rev);
char *  r_getDate(Reviews  rev);
char * r_getText(Reviews rev);




#endif //___REVIEWS_H___