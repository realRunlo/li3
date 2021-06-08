#include <stdio.h>
#include "../includes/sgr.h"
#include "../includes/interpretador.h"
#include "../includes/show.h"
#include <time.h>


int main(){
   //SGR  sgr = load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
   //
   //
   //clock_t begin = clock();
   //TABLE t = top_businesses_with_category(sgr,15,"Chinese");
   //clock_t end = clock();
   //double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
   //printf("time elapsed : %f seconds\n",time_spent);
    
   //TABLE t = top_businesses_by_city(sgr,15);TABLE x = proj(t," business_id,stars,");show_pagedTable(t,0);show_pagedTable(x,0);
    //TABLE t = businesses_catalog(sgr);
    int f = interpretador(); 
    return f;
}



    //g_hash_table_foreach(sgr.hashT_users, (GHFunc)print_user_iterator, " -> %s;%s;%s\n");
    //g_hash_table_foreach(sgr.hashT_businesses, (GHFunc)iterator, "-> %s;%s;%s;%s;%s\n");
    
    //TABLE t = businesses_started_by_letter(sgr ,'c');                    //teste query 2 
    //TABLE t = business_info(sgr,"-l5w8_vwKDSUlpr9FSQoqA");             //teste query 3     
    //TABLE t = businesses_reviewed(sgr, "RNm_RWkcd02Li2mKPRe7Eg");      //teste query 4  
    //TABLE t = businesses_with_stars_and_city(sgr,1.0,"Portland");        //teste query 5
    //TABLE t = top_businesses_by_city(sgr,5000);                           //teste query 6
    //TABLE t = international_users(sgr);                                //teste query 7
    //TABLE t = top_businesses_with_category(sgr,15,"Chinese");          //teste query 8
    //TABLE t = reviews_with_word(sgr,"the");                             //teste query 9  

    //TABLE t = fromCSV("./input_files/reviews_1M.csv",";");
    //printf("hello world\n");

    //toCSV( t , ";" , "./input_files/teste.csv");
    //TABLE x = fromCSV("./input_files/teste.csv",";");
    //TABLE t = fromCSV("file.csv",";");
   //  t = top_businesses_by_city(sgr,5); x = proj( t ,   "       business_name"  )  ;

//t = top_businesses_by_city(sgr,5);toCSV(t,")(","./input_files/teste.csv");
// t = fromCSV("./input_files/reviews_1M.csv", ";");
// t = fromCSV("./input_files/users_full.csv", ";");
// t = top_businesses_by_city(sgr,5); x = filter(t,stars,3.0,1); show(x);
// t = top_businesses_by_city(sgr,10); x = filter(t,city,Austin,-1); show(x);
// x = filter(t,stars,3.0,-1);
// x = t[1][20];
//  load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
//t = top_businesses_by_city(sgr,15); x = proj(t," ,stars");show(x);


//"-l5w8_vwK DSUlpr9FSQoqA"