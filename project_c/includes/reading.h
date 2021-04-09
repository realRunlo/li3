#ifndef ___READING_H___
#define ___READING_H___
#include "structs.h"

GHashTable *  mapToHash_ReviewsFile(char *filename,GHashTable * table);

void readBusiness (GHashTable * hash, char fic [] );
#endif //___READING_H___