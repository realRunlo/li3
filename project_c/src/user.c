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
 * @brief Devolve campo user_id
 * 
 * @param u Apontador para struct user
 * @return char* 
 */
char * getUserId(User u){
    return strdup(u->user_id);
}

/**
 * @brief Devolve campo name
 * 
 * @param u Apontador para struct user
 * @return char* 
 */
char * getUserName(User u){
    return strdup(u->name);
}

/**
 * @brief Devolve campo friend
 * 
 * @param u Apontador para struct user
 * @return char* 
 */
char * getFriends(User u){
    return strdup(u->friends);
}

/**
 * @brief atualiza o userId de um user
 * 
 * @param u user
 * @param newUserId novo id
 */
void setUserId(User u, char* newUserId){
    u->user_id = strdup(newUserId);
}

/**
 * @brief atualiza o nome de um user
 * 
 * @param u user
 * @param newName novo nome
 */
void setName(User u, char* newName){
    u->name = strdup(newName);
}

/**
 * @brief atualiza os amigos de um user
 * 
 * @param u user
 * @param newFriends novos amigos
 */
void setFriends(User u, char* newFriends){
    u->friends = strdup(newFriends);
}

//seped[strlen(seped) - 1] != ';'
/**
 * @brief verifica se o user lido e valido, se tem user_id e user_name, o campo dos friends pode estar vazio
 * 
 * @param str 
 * @return int 
 */
int u_checkNewLine(char * str){
    char * test = strdup(str);
    char* pointer = test;
    char * seped;
    int empty = 0;
    seped = strsep(&test,";"); // user_id
    if(strcmp(seped,"")==0) empty++;
    else{
        seped = strsep(&test,";"); // user_name
        if(strcmp(seped,"")==0) empty++;
        else{
            if(strlen(test)){ 
                seped = strsep(&test,";"); //friends
                if(seped[strlen(seped) - 1] == ';') empty++;  //verificar se nao tem campos a mais
        }
        }
    }
    free (pointer);
    return empty;
}

/**
 * @brief Mapea dados para uma struct user
 * 
 * @param buffer Buffer com informação
 * @return User 
 */
User createUser(char * buffer){
    User u = malloc(sizeof(struct user));
    u->user_id = strdup(strsep(&buffer,";"));
    u->name = strdup(strsep(&buffer,";"));
    u->friends = strdup(strsep(&buffer,"\n"));
    return u;
}


