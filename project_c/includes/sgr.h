#ifndef ___SGR_H___
#define ___SGR_H___
#include "structs.h"
#include "reading.h"
#include "user.h"
#include "reviews.h"
#include "business.h"

typedef struct sgr{

    GHashTable * hashT_users;
    GHashTable * hashT_businesses;
    GHashTable * hashT_reviews;

}SGR;

typedef struct table{

   char ** tab;
   int entries;

}*TABLE;

SGR init_sgr();
void free_sgr(SGR sgr);
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file);


//struct used to store results found by query2_iterator
typedef struct query2{
        char* result; //[business1,business2,...]
        char letter;
        int total;
}*Query2;

//iterator for query2, used to find a business started by a certain char 
//and if so store the results in user_data
void query2_iterator(gpointer key, gpointer value, gpointer user_data);

/* query 2 */
//list of businesses whose name starts with char "letter" and total amount found
TABLE businesses_started_by_letter(SGR sgr, char letter);



typedef struct query4{
        char* result; //[business_id1,business1,business_id2,business2,...]
        char* user_id;
        GHashTable * hashT_businesses; // used to look for the name of the business in case there is a review on it by the user
}*Query4;

//iterator for query4, verifies if the user_id from value(review) equals user_id from user_data
//if so finds the name of the business from the corresponding review and adds both the business_id 
//and business_name to the result in user_data
void query4_iterator(gpointer key, gpointer value, gpointer user_data);

/* query 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id);



//primeiras ideias para query 6

typedef struct city_business{
    char* id;
    char* name;
    struct city_business* next;
}*City_business;


typedef struct cities{
    char* name;
    int total_businesses;
    int total_stars;
    City_business node;
}*Cities;

typedef struct query6{
    Cities * result; 
    GHashTable * hashT_reviews; // used to search the number of stars
}*Query6;





/* query 6 */
TABLE top_businesses_by_city(SGR sgr, int top);



#endif //___SGR_H___


