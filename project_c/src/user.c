#include "../includes/user.h"
#include <stdio.h>

struct user{
    char * user_id;
    char * name;
    char * friends;
};

char * getUserId(User u){
    return strdup(u->user_id);
}

void setUserId(User u, char* newUserId){
    //printf("%s\n",newUserId);
    u->user_id = strdup(newUserId);
}


char * getUserName(User u){
    return strdup(u->name);
}

void setName(User u, char* newName){
    u->name = strdup(newName);
}

char * getFriends(User u){

    return strdup(u->friends);
}

void setFriends(User u, char* newFriends){
    u->friends = strdup(newFriends);
}



void print_user_iterator(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data, getUserId((User) value),getUserName((User) value),getFriends((User) value));
}

User createUser(char * buffer){
    User u = malloc(sizeof(struct user));
    setUserId(u,strsep(&buffer,";"));
    setName(u,strsep(&buffer,";"));
    setFriends(u,strsep(&buffer,"\n"));
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