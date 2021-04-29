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


/**
 * @brief simples iterator para imprimir uma hashtable de users
 * 
 * @param key user_id
 * @param value user
 * @param user_data formato de print
 */
void print_user_iterator(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data, getUserId((User) value),getUserName((User) value),getFriends((User) value));
}

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
    int i = 0 , empty = 0;
    seped = strsep(&test,";"); // user_id
    if(strcmp(seped,"")==0) empty++;
    seped = strsep(&test,";"); // user_name
    if(strcmp(seped,"")==0) empty++;
    free (pointer);
    return empty;
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


