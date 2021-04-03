#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "structs.c"
#include "reviews.c"
#include "business.c"
#include "user.c"
#include "reading.c"
#include "sgr.c"








int main(){

    char filename[100] = "../input_files/users_teste.csv";

    SGR sgr = init_sgr();
    readUser(sgr.hashT_users,filename);
    g_hash_table_foreach(sgr.hashT_users, (GHFunc)print_user_iterator, " ->%s;%s;%s;\n");

    printf("End program!\n");
    return 0;
}