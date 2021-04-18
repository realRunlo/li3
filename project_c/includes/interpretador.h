#ifndef ___INTERPRETADOR_H___
#define ___INTERPRETADOR_H___
#include "../includes/sgr.h"
#include "../includes/table.h"



typedef struct variavel *VARIAVEL; 
typedef struct variaveis *VARIAVEIS; 

char* getCommand();

int skipSpaces(char* str);

int isDigitOrLetter(char c);

char* commandString(char* c);

int variable_command(char *comando,char *var,char *function,SGR sgr,VARIAVEIS v);

int check_variable(VARIAVEIS v, char* variavel);

int executeShow(char *comando, int i, VARIAVEIS v);

int executeCommand(char *comando,VARIAVEIS v,SGR sgr);

int interpretador();



#endif //___INTERPRETADOR_H___