#ifndef ___USER_H___
#define ___USER_H___
#include "structs.h"


typedef struct user * User;


char * getUserId(User u);


void setUserId(User u, char* newUserId);


char * getUserName(User u);


void setName(User u, char* newName);


char * getFriends(User u);


void setFriends(User u, char* newFriends);


void print_user_iterator(gpointer key, gpointer value, gpointer user_data);

int u_checkNewLine(char * str)

User createUser(char * buffer);


#endif //___USER_H___



