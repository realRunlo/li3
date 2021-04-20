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

int addSpaces(int i,char *comando){
    int espacos = skipSpaces(comando+i);
    i+= espacos; 
    return i;
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

void toCSV (TABLE x,char* delim, char* name){
    char s[2] = ",";
    int entries = getEntries(x);
    char* f_csv = malloc(sizeof(char)*(strlen(name)+4));
    sprintf(f_csv,"%s%s",name,".csv");
    FILE* f = fopen(f_csv,"w"); 
    if(strcmp(delim,s)!=0){
        for(int i=0; i<entries ; i++){
            char * str = get_string_table(x,i);  
            char *token = strtok(str,s);
            while(token != NULL) {
                fprintf(f,"%s", token);
                token = strtok(NULL, s);
                if (token != NULL) fprintf(f,"%s",delim);// para não colocar no último token
                
            }
            fprintf(f,"\n");
        }
    }
    fclose(f);
}


TABLE fromCSV (char* file, char* delim){
    TABLE t = init_Sized_Table(1000000);
    FILE* f = fopen(file,"r");
    if (f==NULL){
        printf("ERROR_FILE_readFILE\n");
    }
    else{
        char buffer[1024]; // espaco suficiente para os exemplos do input file
        
        int i =0;
        while(fgets(buffer,1024,f) ){
            char r [1024] = "\0";
            char *token = strtok(buffer,delim);
            while(token != NULL) {                
                strcat(r,token);
                token = strtok(NULL, delim);
                if (token != NULL)  strcat(r,",");// para não colocar no último token
            }
            setNewLine(t,r);
            i++;
        }
        fclose(f);
        printf("Read File.\n");
    }
    return t;
}
TABLE proj(TABLE x, char* cols){
    TABLE r = init_Sized_Table(getEntries(x));
    char s [2] =";";
    char * str = get_string_table(x,0);  
    char *token = strtok(str,s);
    int col = 0;
    while(token != NULL && (strcmp(token,cols)!= 0)) {
        token = strtok(NULL, s);
        col++;
    }
    setNewLine(r,token);
    
    for(int j = 1;get_string_table(x,j)!=NULL;j++ ){
        char * res = get_string_table(x,j);
        char *aux = strtok(res,s);
        int t = 0;
        while(aux != NULL && t<col) {
            aux = strtok(NULL, s);
            t++;
        }
        setNewLine(r,aux);
    }
    return r;
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
            if(comando[i] == '\''){ printf("2\n"); //delimitador
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
                        if(comando[i] == ')'){printf("6\n");//encerrar da funçao
                            i++;
                            espacos = skipSpaces(comando+i);
                            i+= espacos;
                            if(comando[i] == ';'){printf("7\n");
                                //executar toCSV
                                toCSV(var->t,delim,file);
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
/*
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
}

//2-3-4-6
//5-8-9
//7
//funcao para executar, caso a sintaxe esteja correta, a funcao dada a uma variavel
int variable_command(char* comando, char* var, char *function,SGR sgr,VARIAVEIS v){
    printf("executar funçao\n");
    int funcao = functionId(function);
    int espacos = 0 , i = 0;
    if(comando[i] == '('){// 1ºargumento
        i++;
        i = addSpaces(i,comando);
        char* arg1 = commandString(comando+i);
        i+= strlen(arg1);
        i = addSpaces(i,comando);
        if(funcao == 7){  printf("%s   %s\n",comando,arg1);
            if(comando[i] == ')' && strcmp(arg1,"sgr") == 0){printf("1\n");
                i++;
                i = addSpaces(i,comando);
                if(comando[i] == ';'){
                    printf("query7\n");
                    free(arg1);
                    return 1;
                }
            }
            return -1;
        }
        if(comando[i] == ','){// 2ºargumento
            i++;
            i = addSpaces(i,comando);
            if(funcao == 0){ //fromCSV (segundo elemento delimitador)
                if(comando[i] == '\''){  //delimitador
                    i++;
                    char delim = comando[i];
                    i++;
                    if(comando[i] == '\''){
                        i++;
                        i = addSpaces(i,comando);    
                        if(comando[i] == ')'){
                            i++;
                            i = addSpaces(i,comando);
                            if(comando[i] == ';')
                                printf("fromCSV\n");
                                free(arg1);
                                return 0;
                        }
                    }
                }
                return -1;
            }
            char* arg2 = commandString(comando+i);
            i+= strlen(arg2);
            i = addSpaces(i,comando);
            if(funcao == 1 && check_variable(v,arg1) == 0){//filter
            if(comando[i] == ','){
                i++;
                i = addSpaces(i,comando);
                char* arg3 = commandString(comando+i);
                i+= strlen(arg3);
                i = addSpaces(i,comando);
                if(comando[i] == ','){//filter
                    i++;
                    i = addSpaces(i,comando);
                    char* arg4 = commandString(comando+i);
                    i+= strlen(arg4);
                    i = addSpaces(i,comando);
                    if(comando[i] == ')'){
                        i++;
                        i = addSpaces(i,comando);
                        if(comando[i] == ';'){
                            printf("filter\n");
                            free(arg1);free(arg2);free(arg3);free(arg4);
                            return 1;
                        }
                    }
                }
             }
                return -1;
            }
            if(funcao == 2 || funcao == 3 || funcao == 4 || funcao == 6){//query de 2 argumentos
                if(comando[i] == ')' && strcmp(arg1,"sgr") == 0){
                    i++;
                    i = addSpaces(i,comando);
                    if(comando[i] == ';'){
                        switch(funcao){
                            case(2):{printf("query2\n");free(arg1);free(arg2);return 1;}
                            case(3):{printf("query3\n");free(arg1);free(arg2);return 1;}
                            case(4):{printf("query4\n");free(arg1);free(arg2);return 1;}
                            case(6):{printf("query6\n");free(arg1);free(arg2);return 1;}
                        }
                    }
                }
                return -1;
            }
            if(funcao == 5 || funcao == 8 || funcao == 9){//query de 3 argumentos
                if(comando[i] == ',' && strcmp(arg1,"sgr") == 0){
                    i++;
                    i = addSpaces(i,comando);
                    char* arg3 = commandString(comando+i);
                    i+= strlen(arg3);
                    i = addSpaces(i,comando);
                    if(comando[i] == ')'){
                        i++;
                        i = addSpaces(i,comando);
                        if(comando[i] == ';'){
                            switch(funcao){
                            case(5):{printf("query5\n");free(arg1);free(arg2);free(arg3);return 1;}
                            case(8):{printf("query8\n");free(arg1);free(arg2);free(arg3);return 1;}
                            case(9):{printf("query9\n");free(arg1);free(arg2);free(arg3);return 1;}
                            }
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
                        printf("proj\n");
                        free(arg1);free(arg2);
                        return 1;
                    }
            }
            return -1;
                
            }
        }
                            
    }
    //ainda falta o de associar a uma coluna de uma tabela z = x[1][0]
    
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
            i+= strlen(function);
            return variable_command(comando+i, buff, function,sgr,v);
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

