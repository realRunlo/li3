#include <stdio.h>
#include <stdlib.h>
#include "../includes/show.h"

/* -----public----- */

void show_banner(){
    printf(YEL"                          _____  _____ _____  \n");
    printf(YEL"                         / ____|/ ____|  __ \\ \n");
    printf(YEL"                        | (___ | |  __| |__) |\n");
    printf(YEL"                         \\___ \\| | |_ |  _  / \n");
    printf(YEL"                         ____) | |__| | | \\ \\ \n");
    printf(YEL"                        |_____/ \\_____|_|  \\_\\ ");
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
    printf("                            Copyrigth (c)                         \n");
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
    printf("[2] -> Load costum sgr\n");
    printf("[3] -> Go to sgr terminal\n");
    printf("[4] -> Help\n");
    printf("[5] -> Quit\n");
}

void show_help(){
    printf(YEL"\n\n\t\t            WELCOME TO OUR SGR GUIDE     \n"RESET);
    printf("Available commands: \n");
    printf("Query1 :load_sgr( \"[user_file]\", \"[business_file]\", \"[reviews_file]\");\n"RESET);
    printf("\tLoads a costum sgr using the files given as arguments.\n\n");
    printf("Query2 :[var] = businesses_started_by_letter(sgr, [letter]); \n"RESET);
    printf("\tSaves all the businesses started by the letter given.\n\n");
    printf("Query3 :[var] = business_info(sgr,[business_id]); \n"RESET);
    printf("\tSaves the information of a business with the id given.\n\n");
    printf("Query4 :[var] = business_reviewed(sgr,[user_id]); \n"RESET);
    printf("\tSaves the information of the businesses reviewd by the user with the given id.\n\n");
    printf("Query5 :[var] = business_with_stars_and_city(sgr,[stars],[city]); \n"RESET);
    printf("\tSaves the businesses that meet the number of stars and city given.\n\n");
    printf("Query6 :[var] = top_businesses_by_city(sgr,[top]); \n"RESET);
    printf("\tSaves the information of the top businesses of each city.\n\n");
    printf("Query7 :[var] = international_users(sgr); \n"RESET);
    printf("\tSaves the information of the users who have visited more than one state.\n\n");
    printf("Query8 :[var] = top_businesses_with_category(sgr,[stars],[category]); \n"RESET);
    printf("\tSaves the information of the businesses that meet the number of stars and category given.\n\n");
    printf("Query9 :[var] = reviews_with_word(sgr,[word]); \n"RESET);
    printf("\tSaves the id of the reviews which use the word given in their text.\n\n");
    printf("[var] = fromCSV(\"[file]\",\"delimiter\");\n"RESET);
    printf("\tSaves the information of the file given into a TABLE structure, using the delimiter given to separate each element.\n\n");
    printf("[var] = proj([var],[column_names]);\n"RESET);
    printf("\tSaves the given columns, if valid, from an initialized variable to a variable.\n\n");
    printf("[var] = [var][line][column];\n"RESET);
    printf("\tSaves a specific element from an initialized variable (using the line and column given), to a variable.\n\n");
    printf("toCSV([var],[delimiter],\"[file]\"); \n"RESET);
    printf("\tTransfers the information from an initialized variable to a given file, using the given delimiter to separate each line from the TABLE\n\n");
    printf("show([var]); \n"RESET);
    printf("\tShows the information saved in an initialized variable\n\n");
    printf("help; \n"RESET);
    printf("\tShows this page.\n\n");
    printf("clear; \n"RESET);
    printf("\tClears the screen.\n\n");
    printf("quit; \n"RESET);
    printf("\tEnds the program.\n\n");
    printf("Information: follow the sintax of each command as shown above, not forgetting to end each command with ';'.\n");
    printf("Multiple commands can be issued in each line, which will then executed one at a time.\n");
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