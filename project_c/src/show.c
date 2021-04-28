#include <stdio.h>
#include <stdlib.h>
#include "../includes/show.h"

/* -----public----- */

void show_welcome(){
    printf("********************************************************\n");
    printf("            Welcome to Management system               \n\n");
    printf("Developed by: Gonçalo Braz,Gonçalo Pereira,Maria Sofia  \n");
    printf("                                                        \n");
    printf("                  Copyrigth (c)                         \n");
    printf("********************************************************\n");
}

void show_exit(){
    
    printf("\nThat's all,folks!\n");

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
    }else if(page>=totalPages){
        printPage_table(t,page - totalPages );
    }else{
        printPage_table(t,page);
    }
}