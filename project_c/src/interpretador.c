#include <stdlib.h>
#include <stdio.h>
#include "../includes/sgr.h"


char* getCommand(){
    char buff[200];
    char* input = NULL;
    size_t inputlen = 0, bufflen = 0;
    int d;
   do {
       d = fgets(buff, 200, stdin);
       bufflen = strlen(buff);
       input = realloc(input, inputlen+bufflen+1);
       strcat(input, buff);
       inputlen += bufflen;
    } while (bufflen==200-1 && buff[200-2]!='\n');
    
    return input;
}





int main(){
    //SGR  sgr = load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
    
    
    printf("Digite o seu comando: ");
    char *s = getCommand();
    //interpretar comandos
    char buff[strlen(s)];
    size_t commandlen = 0;
    int pflag = 0, cflag = 0; //flag para detecao de parenteses e para detecao de fim de comando
    int j = 0;
    for(int i =0; s[i] != '\n'; i++){
        buff[j] = s[i];
        if(s[i] == '('){
            pflag++;
        }
        if(s[i] == ')'){
            pflag--;
        }
        if(s[i] == ';' && pflag == 0){
            //executeCommand(buff)
            j = 0;
        }
        j++;
    }
    
    return 0;
}

//g_hash_table_foreach(sgr.hashT_users, (GHFunc)print_user_iterator, " -> %s;%s;%s\n");
    //g_hash_table_foreach(sgr.hashT_businesses, (GHFunc)iterator, "-> %s;%s;%s;%s;%s\n");
    
    //TABLE t = businesses_started_by_letter(sgr,'M');                   //teste query 2   
    //TABLE t = businesses_reviewed(sgr, "RNm_RWkcd02Li2mKPRe7Eg");      //teste query 4   
    //TABLE t = top_businesses_by_city(sgr,5);                           //teste query 6
    //TABLE t = top_businesses_with_category(sgr,15,"Chinese");          //teste query 8
    //TABLE t = reviews_with_word(x,"seem");                             //teste query 9  


//char * r;
//    for(int i = 0; i < getEntries(t);i++ ){
//        r = get_string_table(t,i);
//        printf("%d -> %s\n",i,r);
//        free(r);
//    }