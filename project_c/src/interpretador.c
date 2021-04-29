#include "../includes/interpretador.h"
#include "../includes/show.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_VAR 2
#define clrscr() printf("\e[1;1H\e[2J")

struct variavel{
    char* variavel;
    TABLE t;
};

struct variaveis{
    VARIAVEL* variaveis;
    int entries;
    int max;
};


/**
 * @brief inicia a struct variaveis com dois espacos para variaveis
 * 
 * @return VARIAVEIS 
 */
VARIAVEIS  initVariaveis(){
    VARIAVEIS v = malloc(sizeof(struct variaveis)); 
    v->variaveis = malloc(sizeof(struct variavel) * MAX_VAR);
    v->entries = 0;
    v->max = MAX_VAR;
    return v;
}

/**
 * @brief Adiciona ao argumento i, o numero de espacos consecutivos lidos a partir de (comando+i)
 * 
 * @param i posicao atual a ser lida na string comando
 * @param comando string a ser lida
 * @return int 
 */
int addSpaces(int i,char *comando){
    int espacos = skipSpaces(comando+i);
    i+= espacos; 
    return i;
}

//devolve a table de uma variavel caso ela exista
/**
 * @brief dado o nome de uma variavel, retorna caso exista a table correspondente
 * 
 * @param v lista das variaveis
 * @param var nome da variavel cuja table se pretende devolver
 * @return TABLE 
 */
TABLE varTable(VARIAVEIS v, char* var){
    int i = 0;
    for(; i<v->entries; i++){
        if(strcmp(v->variaveis[i]->variavel,var) == 0) return v->variaveis[i]->t;
    }
    
    return NULL;
}

/**
 * @brief verifica se uma string dada corresponde a um operador 
 * 
 * @param arg string a analisar
 * @return int 
 */
int isOperator(char* arg){
    if(strcmp(arg,"-1") == 0 || strcmp(arg,"0") == 0 || strcmp(arg,"1") == 0) return 0;
    return 1;
}

/**
 * @brief verifica se uma string dada corresponde a um int
 * 
 * @param arg string a analisar
 * @return int 
 */
int isNumber(char* arg){
    int erro = 0;
    if(arg[0] >= 48 && arg[0] <= 57){
        for(int i = 1; arg[i] != '\0' && erro == 0; i++){
            if(arg[i] >= 48 && arg[i] <= 57);
            else erro++;
        }
        return erro;
    }
    return -1;
}


/**
 * @brief verifica se uma string dada corresponde a um float
 * 
 * @param arg string a analisar
 * @return int 
 */
int isFloat(char* arg){
    int ponto = 0, erro = 0;
    if(arg[0] >= 48 && arg[0] <= 57){
        for(int i = 1; arg[i] != '\0' && erro == 0; i++){
            if(arg[i] >= 48 && arg[i] <= 57);
            else if(arg[i] == '.' && (arg[i+1] >= 48 && arg[i+1] <= 57)  && ponto == 0) ponto++;
                 else erro++;
        }
        return erro;
    }
    return -1;
}


/**
 * @brief adiciona ou atualiza uma variavel na lista de variaveis
 * 
 * @param v lista de variaveis
 * @param var nome da variavel a adicionar
 * @param t table correspondente a variavel var
 */
void addVar(VARIAVEIS v, char* var, TABLE t){
    int i = 0, flag = 0;
    if (v->entries == v->max){
        v->max *= 2;
        v->variaveis = realloc(v->variaveis,sizeof(struct variavel) * v->max);
    }
    VARIAVEL x = v->variaveis[0];
    //procura por um lugar livre ou por uma variavel com o mesmo nome passado a funcao
    while(x && flag == 0){
        if(strcmp(x->variavel, var) == 0) flag++;
        else{
        i++;
        x= v->variaveis[i];
        }
    }
    //caso em que a variavel ja existe
    if(x != NULL){
        clearTable(x->t);
        x->t = t;
    } 
    //caso de criar uma variavel nova
    else{
        v->variaveis[i] = malloc(sizeof(struct variavel));
        v->variaveis[i]->variavel = strdup(var);
        v->variaveis[i]->t = t;
        v->entries++;
    }
}


/**
 * @brief guarda o input de uma linha no terminal na string "input" 
 * 
 * @return char* 
 */
char* getCommand(){
    char buff[200];
    buff[0] = '\0';
    char* input = malloc(sizeof(char) * 200);
    input[0] = '\0';
    size_t inputlen = 0, bufflen = 0;
   do {
       if(fgets(buff, 200, stdin)){
       bufflen = strlen(buff);
       input = realloc(input, inputlen+bufflen+1);
       strcat(input, buff);
       inputlen += bufflen;
       }
    } while (bufflen==200-1 && buff[200-2]!='\n');
    input[inputlen] ='\0';
    return input;
}


/**
 * @brief conta o numero de espacos consecutivos a partir da posicao inicial de uma string
 * 
 * @param str string a analisar
 * @return int 
 */
int skipSpaces(char* str){
    if(strlen(str) == 0) return 0;
    int i = 0;
    while(str[i] == ' ') i++;
    return i;
}

//Verifica se o caractere c pode pertencer ao nome de um comando ou variavel
/**
 * @brief verifica se um char se trata de uma letra, numero ou '_' (devido ao nome de algumas querys)
 *      funcao utilizada para verificar nomes de funcoes passadas ao interpretador
 * 
 * @param c char a analisar
 * @return int 
 */
int isDigitOrLetter(char c){    
    //  digito              maiscula            minuscula            nome de query 
    if((c>=48 && c<=57) || (c>=65 && c<=90) || (c>=97 && c<=122) || c == '_') return 0;
    return 1;
}

/**
 * @brief a partir da string c retira a primeira string cujos chars validem a "isDigitOrLetter"
 *      utilizado para retirar nomes de funcoes e de alguns argumentos simples do input  
 * 
 * @param c input do utilizador
 * @return char* 
 */
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


/**
 * @brief verifica se uma variavel ja foi iniciada
 * 
 * @param v lista das variaveis iniciadas
 * @param variavel nome da variavel em questao
 * @return int 
 */
int check_variable(VARIAVEIS v, char* variavel){
    int entries = v->entries;
    VARIAVEL * lista = v->variaveis;
    for(int i = 0; lista[i]; i++){
        
        if(strcmp(lista[i]->variavel,variavel) == 0) return 0;
    }
    return 1;
}

/**
 * @brief execucao do comando show
 * 
 * @param comando input do utilizador
 * @param i posicao a usar para ler o input
 * @param v lista das variaveis iniciadas
 * @return int 
 */
int executeShow(char *comando,int i, VARIAVEIS v){
    i = addSpaces(i,comando);
    char *buff = commandString(comando+i); //pega na variavel do show
    i += strlen(buff);
    i = addSpaces(i,comando);
    if (comando[i] == ')'){
        i++;
        i = addSpaces(i,comando); 
        if(comando[i] == ';'){
        //verificar se a variavel guardada em buff existe
        //se existir ,executar o comando, caso contrario mostrar mensagem de erro
            if(check_variable(v,buff) == 0){
                TABLE t = varTable(v,buff);
                if(t){
                    int q = 0, page = 0;
                    while(q == 0){
                        clrscr();
                        page = show_pagedTable(t,page);
                        printf("r -> return; p -> previous page; n -> next page\n");
                        char *c = getCommand();
                        c[strlen(c)-1] = '\0';
                        if(strcmp(c,"r") == 0) q++;
                        else if(strcmp(c,"p") == 0) page--;
                        else if(strcmp(c,"n") == 0) page++;
                        else if(isNumber(c) == 0) page = atoi(c)-1;
                    }
                    clrscr();
                    free(buff);
                    return 1;
                }
                printf("Empty table.\n");
                return -1;
            }
            else{
                printf("Variable not inicialize.\n");
                free(buff);
                return -1;
            }
        }
    } 
    free(buff);
    printf("Syntaxe error.\n");  
    return -1;
}


/**
 * @brief execucao do comando toCSV
 * 
 * @param comando input do utilizador
 * @param i posicao a usar para ler o input
 * @param v lista das variaveis iniciadas
 * @return int 
 */
int executeToCSV(char* comando, int i, VARIAVEIS v){
    char* var = commandString(comando+i); //primeira variavel de toCSV
    int erro = 0;
    if(check_variable(v,var) == 0){erro++;//verifica se variavel existe 1
        i += strlen(var);
        i = addSpaces(i,comando);
        if(comando[i] == ','){erro++;//2
            i++;
            i = addSpaces(i,comando);
            if(comando[i] == '"'){erro++;//delimitador  3
                char *delim = getVar(comando + i);
                i+= strlen(delim);
                printf(".%s.%s.\n",var,delim);
                if(comando[i-1] == '"'){erro++;//4
                    char *del_body = delim+1;
                    i = addSpaces(i,comando);
                    if(comando[i] == ','){erro++;//5
                        i++;
                        i = addSpaces(i,comando);
                        if(comando[i] == '"'){erro++;//guardar nome do ficheiro6
                        i = addSpaces(i,comando);
                        char* file = getVar(comando+i);
                        i+= strlen(file);
                        i = addSpaces(i,comando);
                            if(file[0] == '"' && file[strlen(file)-1] == '"'){erro++;//7
                                char* dir = file+1;  
                            if(comando[i] == ')'){erro++;// 8
                                i++;
                                i = addSpaces(i,comando);
                                if(comando[i] == ';'){erro++; //9
                                    TABLE t = varTable(v,var);
                                    toCSV(t,strsep(&del_body,"\""),strsep(&dir,"\""));
                                    printf("File saved.\n");
                                    free(delim);free(file);
                                    return 1;
                                }
                            }
                            }free(file);
                        }
                    }
                }free(delim);
            }
        }
    }
    else{
        printf("Variable not inicialize.\n");
        return -1;
    }
    printf("Erro no comando toCSV %d\n",erro);
    return -1;
}


/**
 * @brief versao de getcomand com menos restricoes para os argumentos(ex.: diretorios)
 *      a funcao tem em atencao que nao podem ser usados carecteres especiais do 
 *      interpretador como ';' e ')' fora de ""
 * @param comando input do utilizador
 * @return char* 
 */
char* getVar(char* comando){
    char *result = malloc(sizeof(char) * strlen(comando));
    result[0] = '\0';
    int i = 0, aflag = 0, fim = 0;
    while((comando[i] != ' ' || aflag != 0) && (comando[i] != ')' || aflag != 0) && fim == 0 && comando[i] != '\0' && comando[i] != '\n'){
        if(comando[i] == '"' && aflag ==0 ) aflag++;
        else if(comando[i] == '"' && aflag ==1 ) aflag--;
        if(comando[i] == ',' && aflag == 0){//caso de virgula fora de ""
            fim++;
            i--;
        }
        result[i] = comando[i];
        i++;
        
    } 
    result[i] ='\0';
    return result;


}

/**
 * @brief analisa uma string e devolve um int identificante do tipo de comando reconhecido pelo interpretador
 * 
 * @param function comando a ser analisado
 * @return int 
 */
int functionId(char * function){
    if(strcmp(function, "fromCSV") == 0) return 0;
    if(strcmp(function, "filter") == 0) return 1;
    if(strcmp(function, "businesses_started_by_letter") == 0) return 2;
    if(strcmp(function, "business_info") == 0) return 3;
    if(strcmp(function, "businesses_reviewed") == 0) return 4;
    if(strcmp(function, "businesses_with_stars_and_city") == 0) return 5;
    if(strcmp(function, "top_businesses_by_city") == 0) return 6;
    if(strcmp(function, "international_users") == 0) return 7;
    if(strcmp(function, "top_businesses_with_category") == 0) return 8;
    if(strcmp(function, "reviews_with_word") == 0) return 9;
    if(strcmp(function, "proj") == 0) return 10;
    return -1;
}



/**
 * @brief executa as querys, filter, fromCSV, proj 
 *      e inicializacao de variaveis como colunas da table de outra variavel(ex.:z = x[0][0])
 * 
 * @param comando input do utilizador
 * @param var variavel a inicializar/atualizar
 * @param function funcao pedida pelo utilizador
 * @param sgr data dos ficheiros lidos ao iniciar o programa
 * @param v lista das variaveis iniciadas
 * @return int 
 */
int variable_command(char* comando, char* var, char *function,SGR sgr,VARIAVEIS v){
    int funcao = functionId(function);
    int espacos = 0 , i = 0 , erro = 0;
    if(comando[i] == '('){// 1ºargumento
        if(funcao == 0){//fromCSV (segundo elemento delimitador
                        //primeiro argumento sendo um diretorio tem de se usar getVar
            i++;erro++;
            i = addSpaces(i,comando);
            char* dir = getVar(comando+i);
            i+= strlen(dir);
            i = addSpaces(i,comando);
            if(comando[i] == ',' && dir[0] == '"' && dir[strlen(dir)-1] == '"'){// 2ºargumento delimitador
                i++;erro++;
                i = addSpaces(i,comando);
                char* delim = getVar(comando+i);
                i+= strlen(delim);
                if(delim[0] == '"' && delim[strlen(delim) -1] == '"'){
                    i = addSpaces(i,comando);erro++;    
                    if(comando[i] == ')'){
                        i++;erro++;
                        i = addSpaces(i,comando);
                        if(comando[i] == ';'){erro = 0;
                            char* body = dir+1;
                            char* d = delim+1;
                            TABLE t = fromCSV(strsep(&body,"\""),strsep(&d,"\""));
                            addVar(v,var,t);
                        }
                    }free(delim);    
                }        
            }    
            free(dir);
            return erro;
        }
        i++;
        i = addSpaces(i,comando);
        char* arg1 = commandString(comando+i);
        i+= strlen(arg1);
        i = addSpaces(i,comando);
        if(funcao == 7){
            if(comando[i] == ')' && strcmp(arg1,"sgr") == 0){
                i++;
                i = addSpaces(i,comando);
                if(comando[i] == ';'){
                    TABLE t = international_users(sgr);
                    addVar(v,var,t);
                    printf("Variable %s stored!\n",var);
                    free(arg1);
                    return 1;
                }
            }
            return -1;
        }
        if(comando[i] == ','){// 2ºargumento
            i++;
            i = addSpaces(i,comando);
            char* arg2 = getVar(comando+i);
            i+= strlen(arg2);
            i = addSpaces(i,comando);
            if(funcao == 1 && check_variable(v,arg1) == 0){//filter
                if(comando[i] == ','){//valor
                    i++;
                    i = addSpaces(i,comando);
                    char* arg3 = getVar(comando+i);
                    i+= strlen(arg3);
                    i = addSpaces(i,comando);
                    if(comando[i] == ','){//operador
                        i++;
                        i = addSpaces(i,comando);
                        char* arg4 = getVar(comando+i);
                        i+= strlen(arg4);
                        i = addSpaces(i,comando);
                        if(comando[i] == ')' && isOperator(arg4) == 0){
                            i++;
                            i = addSpaces(i,comando);
                            if(comando[i] == ';'){
                                TABLE t1 = varTable(v,arg1);
                                TABLE t2 = filter(t1,arg2,arg3,atoi(arg4));
                                addVar(v,var,t2);
                                printf("filter(%s,%s,%s,%s)\n",arg1,arg2,arg3,arg4);
                                printf("Variable %s stored!\n",var);
                                free(arg1);free(arg2);free(arg3);free(arg4);
                                return 1;
                            }
                        }
                        free(arg4);
                    }
                    free(arg3);
                }
                free(arg1);free(arg2);
                return -1;
            }
            if(funcao == 2 || funcao == 3 || funcao == 4 || funcao == 6 || funcao == 9 ){//query de 2 argumentos
                if(comando[i] == ')' && strcmp(arg1,"sgr") == 0){
                    i++;
                    i = addSpaces(i,comando);
                    if(comando[i] == ';'){
                        switch(funcao){
                            case(2):{
                                char c;
                                if(arg2[0] == '\'' && arg2[2] == '\''){
                                    c = arg2[1];
                                    TABLE t = businesses_started_by_letter(sgr, c);
                                    addVar(v,var,t);
                                    printf("Variable %s stored!\n",var);
                                    free(arg1);free(arg2);
                                    return 1;
                                } 
                                free(arg1);free(arg2);
                                return -1;
                                }
                            case(6):{
                                int isDigit = 0;
                                for(int i = 0; arg2[i] != '\0' && isDigit == 0; i++){
                                    if(arg2[i] >= 48 && arg2[i] <= 57);
                                    else isDigit++;
                                }
                                if(isDigit == 0){
                                    int top = atoi(arg2);
                                    if(top > 0){
                                        TABLE t = top_businesses_by_city(sgr,top);
                                        addVar(v,var,t);
                                        printf("Variable %s stored!\n",var);
                                        free(arg1);free(arg2);
                                        return 1;
                                    }
                                    printf("Utilize um valor maior que 0.\n");
                                    free(arg1);free(arg2);
                                    return 1;
                                }
                                free(arg1);free(arg2);
                                return -1;
                                }
                            default:{ //query 3, 4 e 9
                                if(arg2[0] == '"' && arg2[strlen(arg2)-1] == '"'){
                                char* search = arg2+1;
                                TABLE t;
                                if(funcao == 3) t = business_info(sgr,strsep(&search,"\""));
                                if(funcao == 4) t = businesses_reviewed(sgr,strsep(&search,"\""));
                                if(funcao == 9) t = reviews_with_word(sgr,strsep(&search,"\""));
                                addVar(v,var,t);
                                printf("Variable %s stored!\n",var);
                                free(arg1);free(arg2);
                                return 1;
                                }
                                free(arg1);free(arg2);
                                return -1;
                            }
                        }
                    }
                }
                return -1;
            }
            if(funcao == 5 || funcao == 8){//query de 3 argumentos
                if(comando[i] == ',' && strcmp(arg1,"sgr") == 0){
                    i++;
                    i = addSpaces(i,comando);
                    char* arg3 = getVar(comando+i);
                    i+= strlen(arg3);
                    i = addSpaces(i,comando);
                    if(comando[i] == ')'){
                        i++;
                        i = addSpaces(i,comando);
                        if(comando[i] == ';'){
                            if(isFloat(arg2) == 0 && arg3[0] == '"' && arg3[strlen(arg3)-1] == '"'){
                                float stars = atof(arg2);
                                char* search = arg3+1;
                                TABLE t = NULL;
                                if(funcao == 5) t = businesses_with_stars_and_city(sgr,stars,strsep(&search,"\""));
                                if(funcao == 8) t = top_businesses_with_category(sgr,stars,strsep(&search,"\""));
                                addVar(v,var,t);
                                printf("Variable %s stored!\n",var);
                                free(arg1);free(arg2);free(arg3);
                                return 1;
                                }
                                printf("Invalid arguments.\n");
                                free(arg1);free(arg2);free(arg3);
                                return -1;
                                }
                        }
                    }
                return -1;
            }
            if(funcao == 10 && check_variable(v,arg1) == 0){//proj
                if(comando[i] == ')'){
                        i++;
                        i = addSpaces(i,comando);
                        if(comando[i] == ';'){
                            TABLE t1 = varTable(v,arg1);
                            char * seped;
                            seped = strsep(&arg2,"\"");
                            seped = strdup(strsep(&arg2,"\""));
                            TABLE t2 = proj(t1,seped);
                            addVar(v,var,t2);
                            printf("Variable %s stored!\n",var);
                            free(arg1);//free(arg2);
                            return 1;
                        }
                }
                free(arg1);free(arg2);
                return -1;
            }
        }
                            
    }
    i = addSpaces(i,comando);
    if(check_variable(v,function) == 0 && comando[i] == '['){
    //associar uma coluna de uma table a uma variavel -  ex: z = x[1][0]
        i++;
        i = addSpaces(i,comando);
        char *line = commandString(comando+i);
        i+= strlen(line);
        i = addSpaces(i,comando);
        if(comando[i] == ']' && isNumber(line) == 0){
        i++;
        if(comando[i] == '['){
            i++; 
            i = addSpaces(i,comando);
            char *col = commandString(comando+i);
            i+= strlen(col);
            i = addSpaces(i,comando);
            if(comando[i] == ']' && isNumber(col) == 0){
                i++;
                i = addSpaces(i,comando);
                if(comando[i] == ';'){
                    TABLE t1 = varTable(v,function);
                    TABLE t2 = index_table(t1,atoi(line),atoi(col));
                    addVar(v,var,t2);
                    printf("Variable %s stored!\n",var);
                    return 1;
                }
            }
            free(col);
        }
        }
        free(line);
        return -1;
    }
    printf("Erro na inicializacao de variavel\n");
    return -1;

}




/**
 * @brief analisa o input dado pelo utilizador, separando a funcao a executar
 * 
 * @param comando input do utilizador
 * @param v lista das variaveis iniciadas
 * @param sgr data dos ficheiros lidos ao iniciar o programa
 * @return int 
 */
int executeCommand(char *comando,VARIAVEIS v, SGR sgr){ 
    int len = strlen(comando);
    int i = 0, espacos = 0;
    
    espacos = skipSpaces(comando);
    i+= espacos;
    char * buff = commandString(comando+i);

    //verificar comando quit;
    if(strcmp(buff,"quit") == 0){
        if(comando[i + 4 + skipSpaces(comando + i + 4)] == ';'){
            show_exit();
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
        i = addSpaces(i,comando);
        free(buff);
        return executeToCSV(comando,i,v);
        
    }
    }

    i = espacos;
    //verificar se e variavel, so aceita variaveis com char, digitos ou letras
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
            i+= strlen(function);
            return variable_command(comando+i, buff, function,sgr,v);
        }
        else{ 
            printf("Erro na sintaxe de inicializacao de variavel.\n");
            return -1;
        }
        
    }
    free(buff);
    
}



//funcao principal que ira receber os comandos e interpreta-los
/**
 * @brief le o input de um utilizador e separa a linha em diferentes comandos, 
 *      executando de forma sequencial, caso mais do que um comando sejam dados.
 *      Antes de passar um comando para outras funcoes o processarem, verifica se 
 *      este segue uma sintaxe basica de comandos (ex.: termina o comando com ;, nao abre parenteses
 *      sem os fechar, sem ser fora de aspas,etc)
 * 
 * @return int 
 */
int interpretador(){
    show_welcome();
    printf("Enter any key to start...");
    char c[200];
    while(fgets(c,200,stdin) == 0);
    clrscr();
    SGR  sgr = load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
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
                printf("Syntaxe error.\n");
                perro++;
            }
        }
        free(s);
        free(buff);
        
    }
    
    return 0;
}

