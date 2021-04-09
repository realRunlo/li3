#ifndef ___BUSINESS_H___
#define ___BUSINESS_H___

#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct business{
    char * business_id;
    char * name;
    char * city;
    char * state;
    char * categories;

} * Business;

char * get_id(Business b);
char * get_name(Business b);
char * get_city(Business b);
char * get_state(Business b);
char * get_categ(Business b);

void iterator(gpointer key, gpointer value, gpointer user_data);

int check_line (char *str);

void add_b (Business *b, char *str,int p);

//void read_file (char fic []);

#endif //___BUSINESS_H___


