#ifndef ___REVIEWS_H___
#define ___REVIEWS_H___


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
}* Reviews;







#endif //___REVIEWS_H___