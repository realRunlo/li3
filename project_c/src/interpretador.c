#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/table.h"

typedef struct variaveis{
    char* variavel;
    TABLE t;
}*VARIAVEIS;

char* getCommand(){
    char buff[200];
    char* input = NULL;
    size_t inputlen = 0, bufflen = 0;
   do {
       fgets(buff, 200, stdin);
       bufflen = strlen(buff);
       input = realloc(input, inputlen+bufflen+1);
       strcat(input, buff);
       inputlen += bufflen;
    } while (bufflen==200-1 && buff[200-2]!='\n');
    
    return input;
}

int skipSpaces(char* str){
    if(strlen(str) == 0) return 1;
    int i = 0;
    while(str[i] == ' ') i++;
    return i;
}


//funcao que analisa o comando passado, e caso seja possivel executa-o
    //provavelmente sera necessario passar uma lista de elementos variaveis
    //elemento variavel precisara de uma string para guardar o nome da variavel e um parametro para
    //guardar os dados, por exemplo uma table
void executeCommand(char *comando){ 
    int len = strlen(comando);
    char* compare = malloc(sizeof(char) * len);
    char buff[50];
    int i = 0, espacos = 0;
    
    espacos = skipSpaces(comando);
    i+= espacos + 1;

    //verificar comando quit;
    if(comando[i] == 'q'){
        snprintf(buff,5,"%s",comando+i);
        if(strcmp(buff,"quit") == 0 && comando[i + skipSpaces(comando[i+4])] == ';'){
            //terminar programa
            printf("Terminar programa!\n");
            exit(0);
        }
    }


    //verificar comando show()
    if(comando[i] == 's'){ 
        snprintf(buff,6,"%s",comando+i);
        if(strcmp(buff,"show(") == 0){
            espacos = skipSpaces(comando+i);i+= espacos + 1;
            int pflag = 0, eflag = 0 , j=0;
            char c;
            while(pflag == 0 && eflag ==0){
                c = comando[i];
                if(c == ' ') 
                if(c == ')'){ 
                    pflag++;
                    buff[j] = '\0';
                }
                if(c == '\0' || c == '\n' || c == ';') eflag++;
                else{
                    buff[j] = c;
                    j++;
                }
                i++;
            }
            if (pflag == 1 && comando[i+skipSpaces(comando+i)] == ';'){
                //verificar se a variavel guardada em buff existe
                //se existir ,executar o comando, caso contrario mostrar mensagem de erro
            }
        }
    free(compare);
    
    }


    //cuidar do espacos ate encontrar um char(e sempre entre cada conjunto de char)
    //verificar se se trata de um comando ou de uma variavel
    //executar comando ou iniciar variavel dependendo do caso
    
}




int interpretador(){
    //SGR  sgr = load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
    
    int q = 0;
    printf("Digite o seu comando: ");
    while(q == 0){
        char *s = getCommand();
        //interpretar comandos
        char buff[strlen(s)];
        size_t commandlen = 0;
        int pflag = 0, cflag = 0; //flag para detecao de parenteses e para detecao de fim de comando
        int j = 0;
        for(int i =0; s[i] != '\n'; i++){
            buff[j] = s[i];

            if(s[i] == '(') pflag++; 
            if(s[i] == ')') pflag--;
            if(s[i] == ';' && pflag == 0){
                //executeCommand(buff)
                j = 0;
            }
            j++;
        }
    }
    
    return 0;
}

