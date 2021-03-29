#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "user.h"


char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}


char * getUserId(User u){
    return strdup(u->user_id);
}

void setUserId(User u, char* newUserId){
    //printf("%s\n",newUserId);
    u->user_id = strdup(newUserId);
}


char * getName(User u){
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


User * userList(){
    User* list = malloc(sizeof(User));
    list[0] = NULL;
    return list;
}


void printUserList(User * uList){
    for(int n = 0; uList[n] != NULL;n++){
        //printf("%d : %s;\n",n,getUserId(uList[n]));

        printf("%d : %s;%s;%s\n",n,getUserId(uList[n]),getName(uList[n]),getFriends(uList[n]));

    }
}


void addUser(User* u, char * buffer, int n){
    u[n] = malloc(sizeof(struct user));


    setUserId(u[n],strsep(&buffer,";"));
    setName(u[n],strsep(&buffer,";"));
    setFriends(u[n],strsep(&buffer,"\n"));

}



User* readUser(char * filename){

    FILE* f;
    f = fopen(filename,"r");
    if (f==NULL){
        printf("ERROR_FILE_readUser\n");
        return NULL;
    }

    char buffer[300];
    User* ulist = userList();
    int i = 0;

    while(fgets(buffer,300,f)){
        printf("%d : %s\n",i,buffer);
        addUser(ulist,buffer,i);
        i++;
    }
    ulist[i] = malloc(sizeof(User));
    ulist[i] = NULL;
    fclose(f);

    return ulist;
}

void iterator(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data, key,getName((User) value),getFriends((User) value));
}


//main to test functions of user.c for now
int main(){
    char filename[100] ="./input_files/users_teste.csv";
/*
    printf("Indique o ficheiro a ler.\n");
    scanf("%s",filename);
*/


    User* uList = readUser(filename);
    printUserList(uList);
/*
    User u = malloc(sizeof(struct user));
    setUserId(u,"primeiro");
    setName(u,"goncalo");
    setFriends(u,"ze,runlo,nuno");

    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(hash, GINT_TO_POINTER((getUserId(u))),u);
    g_hash_table_foreach(hash, (GHFunc)iterator, "%s;%s;%s;\n");



//testes das funcoes
/*
    User *list = userList();
    list[0] = malloc(sizeof(User));
    setUserId(list[0],"122341");
    setName(list[0],"goncalo");
    setFriends(list[0],"joaquim,jose,pedro");
    list[1]=malloc(sizeof(User));
    list[1] = NULL;
    printUserList(list);

    printf("string original :%d\n",u->user_id);
    printf("string copiada :%d\n",getUserId(u));
*/

    return 0;
}
