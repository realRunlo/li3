#include "../includes/structs.h"

typedef struct SGR{

    GHashTable * user;
    GHashTable * business;
    GHashTable * review;

};

typedef struct TABLE{

    char * business_names;//q2
    int total_business; //q2 

    char *  info_business; //q3:nome;cidade;estado;stars;nTotal_reviews

    char * business_reviewed;//q4: negocios,id,nome

    char * business_nStars;//q5: negocio;id;nome

    char * business_topN;//q6: id,nome,nEstrelas

    char * users;//q7 lista de utilizadores que visitaram mais que um estado
    int total_users;//q7

    char * category_topN;//q8 id,nome,nEstrelas

    char * reviews_byKey; //q9: lista de ids de reviwes

};