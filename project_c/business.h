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

int valida_linha (char *str);

void add_b (Business *b, char *str,int p);

void ler_ficheiro(char fic []);

#endif //___BUSINESS_H___


