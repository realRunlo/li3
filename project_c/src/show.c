#include <stdio.h>
#include <stdlib.h>
#include "../includes/show.h"

/* -----public----- */

void show_banner(){
    printf(YEL"                       _____  _____ _____  \n");
    printf(YEL"                      / ____|/ ____|  __ \\ \n");
    printf(YEL"                     | (___ | |  __| |__) |\n");
    printf(YEL"                      \\___ \\| | |_ |  _  / \n");
    printf(YEL"                      ____) | |__| | | \\ \\ \n");
    printf(YEL"                     |_____/ \\_____|_|  \\_\\ ");
    printf("\n"RESET);

}

void show_info_banner(){
    printf(YEL"                          _____ _   _ ______ ____  \n");
    printf(YEL"                         |_   _| \\ | |  ____/ __ \\ \n");
    printf(YEL"                           | | |  \\| | |__ | |  | |\n");
    printf(YEL"                           | | | . ` |  __|| |  | |\n");
    printf(YEL"                          _| |_| |\\  | |   | |__| |\n");
    printf(YEL"                         |_____|_| \\_|_|    \\____/ \n");
    printf("\n"RESET);
}

void show_bar(){
    printf(BLU" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______\n"RESET);
    printf(BLU"|______|______|______|______|______|______|______|______|______|______|\n"RESET);

}
void show_welcome(){
    show_bar();
    printf("\n");
    show_banner();
    printf("\n\n");
    printf("                         Copyrigth (c)                         \n");
    show_bar();
}
void show_exit(){
    printf("PROGRAM TERMINATED...\n");
    show_bar();
    printf("\n");
    show_info_banner();
    printf("Institution: University of Minho                                  \n");
    printf("Course: Software Engineering                                      \n");
    printf("Class: LI3                                                        \n");
    printf("Group: 6                                                           \n");
    printf("Developers: Gonçalo Braz,Gonçalo Pereira,Maria Sofia              \n");
    show_bar();

}

void show_menu(){
    show_banner();
    printf("\n");
    printf("[1] -> Load default sgr\n");
    printf("[2] -> Costumize a sgr\n");
    printf("[3] -> Go to sgr terminal\n");
    printf("[4] -> Help\n");
    printf("[5] -> Quit\n");
}

void show_help(){
    printf("             Welcome to sgr guide      \n");
   
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