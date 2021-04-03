#include "../includes/user.h"





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



void print_user_iterator(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data, getUserId((User) value),getName((User) value),getFriends((User) value));
}



User createUser(char * buffer){
    User u = malloc(sizeof(struct user));
    setUserId(u,strsep(&buffer,";"));
    setName(u,strsep(&buffer,";"));
    setFriends(u,strsep(&buffer,"\n"));
    return u;
}




void readUser(GHashTable * table, char * filename){

    FILE* f;
    f = fopen(filename,"r");
    if (f==NULL){
        printf("ERROR_FILE_readUser\n");
        exit(1);
    }

    char buffer[400000]; // enough space for 3 excel cells
    User u;
    int i = 0;

    while(fgets(buffer,400000,f)){
        //printf("%d : %s",i,buffer);
        //printf("%d\n",i);
        u = createUser(buffer);
        addToHashT(table,GINT_TO_POINTER((getUserId(u))),u);
        i++;
    }
    fclose(f);
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