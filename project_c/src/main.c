#include <stdlib.h>
#include <stdio.h>
#include "../includes/sgr.h"




int main(){
   
   SGR  x = load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
    
    //g_hash_table_foreach(sgr.hashT_users, (GHFunc)print_user_iterator, " -> %s;%s;%s\n");
    //g_hash_table_foreach(sgr.hashT_businesses, (GHFunc)iterator, "-> %s;%s;%s;%s;%s\n");
    
    //TABLE t = businesses_reviewed(sgr, "RNm_RWkcd02Li2mKPRe7Eg");
    //TABLE t = reviews_with_word(x,"seem");
    return 0;
}