#ifndef ___STRUCTS_H___
#define ___STRUCTS_H___

#include "glibWarningAvoid.h"

typedef GHashTable * hashTable;

GHashTable * initHashT();

gboolean addToHashT(GHashTable * ht,void * c,void * value);

gpointer lookUpHashT(GHashTable * ht,char * tofind);

void free_a_hash_table_entry (gpointer key, gpointer value, gpointer user_data);

void free_all_key_value_entries (GHashTable* table);


#endif //___STRUCTS_H___