#ifndef ___READING_H___
#define ___READING_H___
#include "structs.h"

void  readReviews(GHashTable * table,char * filename);

void readUser(GHashTable * table, char * filename);

void readBusiness (GHashTable * hash, char * filename );
#endif //___READING_H___