#ifndef ___INTERPRETADOR_H___
#define ___INTERPRETADOR_H___
#include "../includes/sgr.h"
#include "../includes/table.h"

typedef struct variavel *VARIAVEL; 
typedef struct variaveis *VARIAVEIS; 
VARIAVEIS  initVariaveis();
int addSpaces(int i,char *comando);
TABLE varTable(VARIAVEIS v, char* var);
int isOperator(char* arg);
int isNumber(char* arg);
int isFloat(char* arg);
int skipSpaces(char* str);
int isDigitOrLetter(char c);
char* commandString(char* c);
int check_variable(VARIAVEIS v, char* variavel);
int executeShow(char *comando, int i, VARIAVEIS v);
int executeToCSV(char* comando, int i, VARIAVEIS v);
char* getVar(char* comando);
int functionId(char * function);
int variable_command(char *comando,char *var,char *function,SGR sgr,VARIAVEIS v);
int executeLoadSgr(char* comando, int i, SGR sgr);
int executeCommand(char *comando,VARIAVEIS v,SGR sgr,int* r);
SGR initial_load_sgr();
int interpretador();



#endif //___INTERPRETADOR_H___