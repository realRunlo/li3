#ifndef ___USER_H___
#define ___USER_H___
#include "structs.h"


typedef struct user * User;

// gets UserId
char * getUserId(User u);

// sets UserId
void setUserId(User u, char* newUserId);

// gets Name
char * getName(User u);

// sets Name
void setName(User u, char* newName);

// gets Friends
char * getFriends(User u);

// sets Friends
void setFriends(User u, char* newFriends);

// hash table iterator that prints every element
void print_user_iterator(gpointer key, gpointer value, gpointer user_data);

// creates a new user by processing the contents of a buffer into 3 strings, one for each parameter of User
User createUser(char * buffer);

// reads the user type file, and line by line adds a new user to a hash table
void readUser(GHashTable * table, char * filename);














#endif //___USER_H___



