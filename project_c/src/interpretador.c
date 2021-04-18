#include "../includes/interpretador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct variavel{
    char* variavel;
    TABLE t;
};

struct variaveis{
    VARIAVEL* variaveis;
    int entries;
};

VARIAVEIS  initVariaveis(){
    VARIAVEIS v = malloc(sizeof(struct variaveis)); 
    v->variaveis = malloc(sizeof(struct variavel) * 20); //apenas 20 variaveis disponiveis
    v->entries = 0;
    return v;
}

//Recebe o input dado pelo o utilizador a passa-o para um array
char* getCommand(){
    char buff[200];
    buff[0] = '\0';
    char* input = malloc(sizeof(char) * 200);
    input[0] = '\0';
    size_t inputlen = 0, bufflen = 0;
   do {
       fgets(buff, 200, stdin);
       bufflen = strlen(buff);
       input = realloc(input, inputlen+bufflen+1);
       strcat(input, buff);
       inputlen += bufflen;
    } while (bufflen==200-1 && buff[200-2]!='\n');
    input[inputlen] ='\0';
    return input;
}

//conta o numero de espacos consecutivos a partir da posicao inicial
int skipSpaces(char* str){
    if(strlen(str) == 0) return 0;
    int i = 0;
    while(str[i] == ' ') i++;
    return i;
}

//Verifica se o caractere c pode pertencer ao nome de um comando ou variavel
int isDigitOrLetter(char c){    
    //  digito              maiscula            minuscula            nome de query 
    if((c>=48 && c<=57) || (c>=65 && c<=90) || (c>=97 && c<=122) || c == '_') return 0;
    return 1;
}

char* commandString(char* c){
    char* buff = malloc(sizeof(char) * strlen(c));
    int i =0;
    while(isDigitOrLetter(c[i]) == 0){
        buff[i] = c[i];
        i++;
    }
    buff[i] = '\0';
    return buff;
}

//funcao para executar, caso a sintaxe esteja correta, a funcao dada a uma variavel
void variable_command(char* var, char *function,char *comando,SGR sgr,VARIAVEIS v){
    printf("executar funçao\n");
    if(strcmp(function, "fromCSV") == 0){

    }
    

}

//funcao que verifica se a variavel existe
int check_variable(VARIAVEIS v, char* variavel){
    int entries = v->entries;
    VARIAVEL * lista = v->variaveis;
    for(int i = 0; i<entries; i++){
        if(strcmp(lista[i]->variavel,variavel) == 0) return 0;
    }
    return 1;
}


int executeShow(char *comando,int i, VARIAVEIS v){
    int espacos = skipSpaces(comando+i);
    i+= espacos;

    char *buff = commandString(comando+i); //pega na variavel do show
    i += strlen(buff);
    i += skipSpaces(comando+i);
    if (comando[i] == ')'){
        i++;
        i += skipSpaces(comando+i);
        if(comando[i] == ';'){
        //verificar se a variavel guardada em buff existe
        //se existir ,executar o comando, caso contrario mostrar mensagem de erro
            if(check_variable(v,buff) == 0){
                printf("show\n");
                    return 1;
            }
            else{
                printf("variavel nao existe\n");
                    return -1;
            }
        }
    } 
    printf("Erro de sintaxe.\n");  
    return -1;
}

int executeToCSV(char* comando, int i, VARIAVEIS v){
    char* var = commandString(comando+i); //primeira variavel de toCSV
    if(check_variable(v,var) == 0){
        i += strlen(var);
        int espacos = skipSpaces(comando+i);
        i+= espacos;
        if(comando[i] == ','){printf("1\n");
            i++;
            espacos = skipSpaces(comando+i);
            i+= espacos;
            if(comando[i] == '\''){ printf("2\n");
                i++;
                char delim = comando[i];
                i++;
                if(comando[i] == '\''){printf("3\n");
                    i++;
                    espacos = skipSpaces(comando+i);
                    i+= espacos;
                    if(comando[i] == ','){printf("4\n");
                        i++;
                        espacos = skipSpaces(comando+i);
                        i+= espacos;
                        if(comando[i] == '"'){printf("5\n"); 
                        //guarda diretorio do ficheiro, usando strsep
                        //precisa de strcat para adicionar " no inicio sem ter espaços
                        char *body =malloc(sizeof(char) * strlen(comando));
                        strcpy(body,comando+i+1);
                        body = strsep(&(body),"\"");
                        char * file = malloc(sizeof(char) * (strlen(body) + 2)); 
                        file[0] = '"';
                        file[1] = '\0';
                        strcat(file,body);
                        int lenFile = strlen(file);
                        file[lenFile] = '"';
                        file[lenFile+1] = '\0';
                        lenFile++;
                        i+=lenFile;
                        espacos = skipSpaces(comando+i);
                        i+= espacos;
                        printf("%s\n%c\n",file,comando[i]);
                        if(comando[i] == ')'){printf("6\n");
                            i++;
                            espacos = skipSpaces(comando+i);
                            i+= espacos;
                            if(comando[i] == ';'){printf("7\n");
                                printf("toCSV(%s,'%c',%s)\n",var,delim,file);
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        }
    }
    else{
        printf("variavel nao existe\n");
        return -1;
    }
    printf("Erro no comando toCSV\n");
    return -1;
}



//funcao que analisa o comando passado, e caso seja possivel executa-o
    //provavelmente sera necessario passar uma lista de elementos variaveis
    //elemento variavel precisara de uma string para guardar o nome da variavel e um parametro para
    //guardar os dados, por exemplo uma table
int executeCommand(char *comando,VARIAVEIS v, SGR sgr){ 
    printf("executar: %s\n",comando);
    int len = strlen(comando);
    int i = 0, espacos = 0;
    
    espacos = skipSpaces(comando);
    i+= espacos;
    char * buff = commandString(comando+i);

    //verificar comando quit;
    if(strcmp(buff,"quit") == 0){
        if(comando[i + 4 + skipSpaces(comando + i + 4)] == ';'){
            //terminar programa
            printf("Terminar programa!\n");
            exit(0);
        }
    }
    
    //verificar comando show()
    //falta executar e talvez comprimir para uma funçao separada
    if(strcmp(buff,"show") == 0){
        if(comando[i + 4] == '('){
        free(buff);
        i += 5;
        return executeShow(comando,i,v);
        }
    }

    //verificar comando toCSV()
    //falta comprimir para uma funçao separada e executar
    if(strcmp(buff,"toCSV") == 0){
        if(comando[i + 5] == '('){
        i += 6;
        espacos = skipSpaces(comando+i);
        i+= espacos;
        free(buff);
        return executeToCSV(comando,i,v);
        
    }
    }

    i = espacos;
    //verificar se e variavel, so aceita variaveis com char, digitos ou alfabeticos
    //falta fazer uma funçao para interpretar se a string function pode ser executada
    if(isDigitOrLetter(buff[0]) == 0){
        i += strlen(buff);
        i += skipSpaces(comando+i);
        //verificar se tem igual depois de espacos
        //senao dar erro por comando desconhecido
        if(comando[i] == '='){
            i++;
            i += skipSpaces(comando+i);
            char * function = commandString(comando+i);
            //verificar se a variavel esta a ser atribuida a um comando compativel e executar
            //variable_command(buff,function,comando+i,sgr,v);
            i+= strlen(function) + 1;
            if(comando[i] == '('){
                i++;
                i+=skipSpaces(comando+i);
                
                if(comando[i] == ';'){
                int k = v->entries;
                v->variaveis[k] = malloc(sizeof(struct variavel));
                v->variaveis[k]->variavel = strdup(buff);
                v->variaveis[k]->t = initTable();
                v->variaveis[k]->t = NULL;
                v->entries++;
                printf("variavel guardada\n");
                return 1;
                }
            }
        }
        else{ 
            printf("Erro na sintaxe de inicializacao de variavel.\n");
            return -1;
        }
        
    }


    //cuidar do espacos ate encontrar um char(e sempre entre cada conjunto de char)
    //verificar se se trata de um comando ou de uma variavel
    //executar comando ou iniciar variavel dependendo do caso
    free(buff);
    
}



//funcao principal que ira receber os comandos e interpreta-los
int interpretador(){
    SGR  sgr = NULL;//= load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
    VARIAVEIS v = initVariaveis();
    v->variaveis[0] = malloc(sizeof(struct variavel));
    v->variaveis[0]->variavel = strdup("x");
    v->entries++;
    int q = 0;
    while(q == 0){
        printf("Digite o seu comando: ");
        char *s = getCommand();
        //interpretar comandos
        char *buff = malloc(sizeof(char) * strlen(s));
        size_t commandlen = 0;
        int pflag = 0, cflag = 0 , dflag = 0, perro = 0; //flags para deteçao de parenteses, delimitadores, e erros
        int j = 0;
        for(int i =0; perro == 0 && s[i] != '\n'; i++){
            buff[j] = s[i];
            j++;
            if(s[i] == '(') pflag++; 
            if(s[i] == ')') pflag--;
            if(s[i] == '\'' || s[i] == '"'){
                if(dflag == 1) dflag--;
                else dflag++;
            }
            if(s[i] == ';' && pflag == 0){
                buff[j] = '\0';
                executeCommand(buff,v,sgr);
                j = 0;
            }
            if(s[i] == ';' && pflag != 0 && dflag == 0){
                printf("Erro de sintaxe.\n");
                perro++;
            }
        }
        free(s);
        free(buff);
    }
    
    return 0;
}

