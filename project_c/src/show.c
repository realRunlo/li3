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
int show_pagedTable(TABLE t ,int page){
    int totalPages = getTotalPages(t);
    int r = 0;
    if(totalPages==1){
        printPage_table(t,0);
    }else if(page<0){
        r = totalPages + page;
        printPage_table(t,r);
    }else if(page>=totalPages){
        r = page - totalPages ;
        printPage_table(t,r);
    }else{
        r = page;
        printPage_table(t,r);
    }

    return r;
}