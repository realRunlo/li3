#include <stdio.h>
#include <stdlib.h>
#include "../includes/show.h"

/* -----public----- */

void show_welcome(){
    printf("----------------------------------------\n");
    printf("            Hello!,welcome              \n");
    printf("----------------------------------------\n");
}

void show_exit(){
    printf("----------------------------------------\n");
    printf("         Bye!,see you next time.        \n");
    printf("----------------------------------------\n");
}

void show_error(char * str_err){
    printf("ERROR: %s",str_err);
}

void show_options(char *options){
    printf("Type: %s",options);
}

void show_pagedTable(TABLE t ,int page){
    int totalPages = getTotalPages(t);
    if(totalPages==1){
        printPage_table(t,0);
    }else if(page<0){
        printPage_table(t,totalPages + page);
    }else if(page>totalPages){
        printPage_table(t,page - totalPages );
    }else{
        printPage_table(t,page);
    }
}