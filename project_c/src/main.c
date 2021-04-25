#include <stdlib.h>
#include <stdio.h>
#include "../includes/sgr.h"
#include "../includes/interpretador.h"



int main(){
    
    SGR  sgr = load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
    //g_hash_table_foreach(sgr.hashT_users, (GHFunc)print_user_iterator, " -> %s;%s;%s\n");
    //g_hash_table_foreach(sgr.hashT_businesses, (GHFunc)iterator, "-> %s;%s;%s;%s;%s\n");
    
    //TABLE t = businesses_started_by_letter(sgr,'M');                   //teste query 2 
    //TABLE t = business_info (sgr, "-l5w8_vwKDSUlpr9FSQoqA");             //teste query 3     
    //TABLE t = businesses_reviewed(sgr, "RNm_RWkcd02Li2mKPRe7Eg");      //teste query 4  
    //TABLE t = businesses_with_stars_and_city (sgr,1.0,"Portland");        //teste query 5
    //TABLE t = top_businesses_by_city(sgr,5);                           //teste query 6
    //TABLE t = top_businesses_with_category(sgr,15,"Chinese");          //teste query 8
    //TABLE t = reviews_with_word(x,"seem");                             //teste query 9  

/*
    char * r;
        for(int i = 0; i < getEntries(t);i++ ){
            r = get_string_table(t,i);
            printf("%d -> %s\n",i,r);
            free(r);
        }
  */ 

    //int f = interpretador();

    TABLE t = international_users(sgr);                                //teste query 7
    
    //toCSV(t,";","file");
    //TABLE t = fromCSV("file",";");
    //TABLE t = fromCSV("file.csv",";");
   // TABLE a = proj( t, "b_id");
    char * r;
        for(int i = 0; i < getEntries(t);i++ ){
        r = get_string_table(t,i);
        printf("%d -> %s\n",i,r);
        free(r);
    }
    return 0;
}

