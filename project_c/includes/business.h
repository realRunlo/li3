#ifndef ___BUSINESS_H___
#define ___BUSINESS_H___

#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct business * Business;

char * get_id(Business b);
char * get_name(Business b);
char * get_city(Business b);
char * get_state(Business b);
char * get_categ(Business b);

void iterator(gpointer key, gpointer value, gpointer user_data);

int check_line (char *str);

void add_b (Business *b, char *str,int p);

int count_fiels (char* str);

void check_comma (char* city);

Business create_b (char *str);

#endif //___BUSINESS_H___


