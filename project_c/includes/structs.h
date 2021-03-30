#ifndef ___STRUCTS_H___
#define ___STRUCTS_H___

#include "glibWarningAvoid.h"


GHashTable * initHashT();

gboolean addToHashT(GHashTable * ht,void * c,void * value);

gpointer lookUpHashT(GHashTable * ht,char * tofind);


#endif //___STRUCTS_H___