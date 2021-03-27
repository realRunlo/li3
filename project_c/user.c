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
    char * newUserId = malloc(sizeof(u->user_id));
    newUserId = strcpy(newUserId,u->user_id);
    return newUserId;
}


char * getName(User u){
    char * newName = malloc(sizeof(u->name));
    newName = strcpy(newName,u->name);
    return newName;
}

char * getFriends(User u){
    char * newFriends = malloc(sizeof(u->friends));
    newFriends = strcpy(newFriends,u->friends);
    return newFriends;
}


User * UserList(){
    User* list = malloc(sizeof(User));
    list[0] = NULL;
    return list;
}



void addUser(User* uList, char * buffer, int n){
    uList[n] = malloc(sizeof(User));
    uList[n]->user_id = strdup(strsep(&buffer,";"));
    uList[n]->name = strdup(strsep(&buffer,";"));
    uList[n]->friends = strdup(strsep(&buffer,";"));
    printf("%d : %s;%s;%s\n",n,uList[n]->user_id,uList[n]->name,uList[n]->friends);
}



User* readUser(char * filename){

    FILE* f;
    f = fopen(filename,"r");
    if (f==NULL){
        printf("ERROR_FILE_readUser\n");
        return NULL;
    }

    char buffer[300];
    User* Ulist = UserList();
    int i = 0;

    while(fgets(buffer,300,f)){
        addUser(Ulist,buffer,i);
        i++;
    }
    fclose(f);

    return Ulist;
}



//main to test functions of user.c for now
int main(){
    char filename[100] ="./input_files/users_full.csv";

/*
    printf("Indique o ficheiro a ler.\n");
    scanf("%s",filename);
*/
    User* list = readUser(filename);

/*
//testes das funcoes
    User u = malloc(sizeof(User));
    u->user_id = "123456";
    u->name = "Goncalo";
    u->friends = "Joaquim,Jose,Pedro";

    printf("string original :%d\n",u->user_id);
    printf("string copiada :%d\n",getUserId(u));
*/


}
