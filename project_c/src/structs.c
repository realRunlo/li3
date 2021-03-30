#include <stdlib.h>
#include <stdio.h>
#include "../includes/structs.h"
#include "../includes/reviews.h"
#include "../includes/reading.h"

GHashTable * initHashT(){

    GHashTable * ht = g_hash_table_new(g_str_hash, g_str_equal); 
    return ht;
}

gboolean addToHashT(GHashTable * ht,void * c,void * value){
    gboolean  rt = g_hash_table_insert(ht,c,value);
    return rt;
}

gpointer lookUpHashT(GHashTable * ht,char * tofind){
    
    gpointer rt = g_hash_table_lookup(ht,tofind);
    return rt;
}

