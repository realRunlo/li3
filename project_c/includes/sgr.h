#ifndef ___SGR_H___
#define ___SGR_H___

#include "../includes/structs.h"

typedef struct sgr{

    GHashTable * hashT_users;
    GHashTable * hashT_businesses;
    GHashTable * hashT_reviews;

}SGR;

typedef struct table{

   char ** tab;
   int entries;

}TABLE;

SGR init_sgr();
void free_sgr(SGR sgr);
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file);

#endif //___SGR_H___


