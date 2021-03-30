#ifndef ___BUSINESS_H___
#define ___BUSINESS_H___

#include <stdlib.h>
#include <string.h>

typedef struct business{
    char * business_id;
    char * name;
    char * city;
    char * state;
    char * categories;

} * Business;

int check_line (char *str);

void add_b (Business *b, char *str,int p);

void read_file(char fic []);

#endif //___BUSINESS_H___


