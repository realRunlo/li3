#include "../includes/user.h"
#include <stdio.h>


/*  ----------private----------  */
struct user{
    char * user_id;
    char * name;
    char * friends;
};

/*  ----------public----------  */

/**
\brief Devolve campo user_id
@param u Apontador para struct user
@returns char * - string com o user id
*/
char * getUserId(User u){
    return strdup(u->user_id);
}

/**
\brief Devolve campo name
@param u Apontador para struct user
@returns char * - string com o nome
*/
char * getUserName(User u){
    return strdup(u->name);
}

/**
\brief Devolve campo friend
@param u Apontador para struct user
@returns char * - string com os friends
*/
char * getFriends(User u){
    return strdup(u->friends);
}

void setUserId(User u, char* newUserId){
    u->user_id = strdup(newUserId);
}


void setName(User u, char* newName){
    u->name = strdup(newName);
}


void setFriends(User u, char* newFriends){
    u->friends = strdup(newFriends);
}



void print_user_iterator(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data, getUserId((User) value),getUserName((User) value),getFriends((User) value));
}

/**
\brief Mapea dados para uma struct user
@param buffer Buffer com informação
@returns USER - apontador struct user
*/
User createUser(char * buffer){
    User u = malloc(sizeof(struct user));
    u->user_id = strdup(strsep(&buffer,";"));
    u->name = strdup(strsep(&buffer,";"));
    u->friends = strdup(strsep(&buffer,"\n"));
    return u;
}










////main to test functions of user.c for now
//int main(){
//    char filename[100] ="./input_files/users_full.csv";
///*
//    printf("Indique o ficheiro a ler.\n");
//    scanf("%s",filename);
//*/
//
//    GHashTable* table = initHashT();
//    readUser(table,filename);
//    g_hash_table_foreach(table, (GHFunc)iterator, " ->%s;%s;%s;\n");
//
//
////testes das funcoes
///*
//    User *list = userList();
//    list[0] = malloc(sizeof(User));
//    setUserId(list[0],"122341");
//    setName(list[0],"goncalo");
//    setFriends(list[0],"joaquim,jose,pedro");
//    list[1]=malloc(sizeof(User));
//    list[1] = NULL;
//    printUserList(list);
//
//    printf("string original :%d\n",u->user_id);
//    printf("string copiada :%d\n",getUserId(u));
//*/
//
//
//    printf("Programa terminado\n");
//    return 0;
//}
//