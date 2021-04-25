#ifndef ___INTERPRETADOR_H___
#define ___INTERPRETADOR_H___
#include "../includes/sgr.h"
#include "../includes/table.h"



typedef struct variavel *VARIAVEL; 
typedef struct variaveis *VARIAVEIS; 

//inicia a struct VARIAVEIS
VARIAVEIS  initVariaveis();

//atualiza i a partir do numero de espacos contados por skipSpaces
int addSpaces(int i,char *comando);

//retorna a table de uma dada variavel
TABLE varTable(VARIAVEIS v, char* var);

//funcao q recebe os inputs no terminal
char* getCommand();

//versao de getcomand com menos restricoes para os argumentos
char* getVar(char* comando);

//conta o numero de espacos entre a posicao atual e a proxima que n seja espaco
int skipSpaces(char* str);

//verifica se o char e digito, letra ou _(para o caso de nomes de query)
int isDigitOrLetter(char c);

//separa uma string pertencente ao comando (por exemplo um argumento)
char* commandString(char* c);

//verifica se uma variavel ja foi inicializada
int check_variable(VARIAVEIS v, char* variavel);

//executa o comando show
int executeShow(char *comando, int i, VARIAVEIS v);

//executa comando ToCSV
int executeToCSV(char* comando, int i, VARIAVEIS v);

//auxiliar de variable_command para identificar funcao passada como arumento
int functionId(char * function);

//executa funcoes dadas a variaveis
int variable_command(char *comando,char *var,char *function,SGR sgr,VARIAVEIS v);

//interpreta um comando dado
int executeCommand(char *comando,VARIAVEIS v,SGR sgr);

//recebe comandos do usuario e executa caso sejam validos
int interpretador();



#endif //___INTERPRETADOR_H___