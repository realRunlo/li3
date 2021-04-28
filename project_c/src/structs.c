#include "../includes/structs.h"

/**
 * @brief inicia uma nova GHashTable
 * 
 * @return GHashTable* 
 */
GHashTable * initHashT(){

    GHashTable * ht = g_hash_table_new(g_str_hash, g_str_equal); 
    return ht;
}

/**
 * @brief adiciona uma nova entrada numa hashtable
 * 
 * @param ht GHashTable
 * @param c key da nova entrada
 * @param value nova entrada
 * @return gboolean 
 */
gboolean addToHashT(GHashTable * ht,void * c,void * value){
    gboolean  rt = g_hash_table_insert(ht,c,value);
    return rt;
}

/**
 * @brief procura uma entrada numa hashtable dada uma key
 * 
 * @param ht GHashTable
 * @param tofind key
 * @return gpointer 
 */
gpointer lookUpHashT(GHashTable * ht,char * tofind){
    
    gpointer rt = g_hash_table_lookup(ht,tofind);
    return rt;
}

/**
 * @brief free de uma entrada numa hashtable
 * 
 * @param key chave de uma entrada
 * @param value entrada
 * @param user_data NULL
 */
void free_a_hash_table_entry (gpointer key, gpointer value, gpointer user_data){
    g_free (key);
    g_free (value);
}

/**
 * @brief aplica a todas as entradas de uma hashtable um free e destroi a table no fim
 * 
 * @param table 
 */
void free_all_key_value_entries (GHashTable* table){
    g_hash_table_foreach (table, free_a_hash_table_entry, NULL);
    g_hash_table_destroy (table);
}