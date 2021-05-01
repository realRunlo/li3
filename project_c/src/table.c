#include "../includes/table.h"
#include "../includes/interpretador.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MARGIN 6
#define MAXTPAGE 11
#define FLOAT 1
#define INT 0
#define FROMCSV_BUFFER_SIZE 2000

/*  ----------private----------  */
struct table{

   char ** tab;
   int entries;

};


/* ----------public---------- */

/**
\brief Inicializa uma table
@returns TABLE apontador para struct table
*/
TABLE initTable(){
    TABLE t = malloc(sizeof(struct table));
    t->tab = NULL;
    t->entries = 0;
    return t;
}

/**
\brief Inicializa uma table com um dado tamanho
@param size tamanho a alocar a matriz da table
@returns TABLE apontador para struct table
*/
TABLE init_Sized_Table(int size){
    TABLE t = malloc(sizeof(struct table));
    t->tab =  malloc(sizeof(char*) * size);
    t->entries = 0;
    return t;
}

/**
\brief Limpa a matriz da table libertando o espaço
@param t TABLE
@returns void
*/
void clearTable(TABLE t){
    if(t){
        for(int i=0;i<t->entries;i++)
            free(t->tab[i]);
    }
}

/**
\brief Atribuiu um número de entradas
@param t TABLE
@param x Númeor de entradas
@returns void
*/
void setEntries(TABLE t,int x){
    t->entries = x;
}

/**
\brief Atribuiu uma matrix ao campo tab da TABLE
@param t TABLE
@param result Matriz a atribuir
@returns void
*/
void setTab(TABLE t, char** result){
    t->tab = result;
}

/**
\brief Adiciona nova linha à matriz
@param t TABLE
@param line Linha a adicionar
@returns void
*/
void setNewLine(TABLE t,char * line){
    t->tab[t->entries] = strdup(line);
    t->entries++;
}

/**
\brief Devolve número de entradas da matriz
@param t TABLE
@returns int 
*/
int getEntries(TABLE t){
    return t->entries;
}

/**
\brief Devolve o campo tab de uma TABLE,uma matriz
@param t TABLE
@returns char**
*/
char** getTab(TABLE t){
    int entries = getEntries(t);
    char **results = malloc(sizeof(char*) * entries);
    for(int i=0; i<entries ; i++){
        results[i] = strdup(t->tab[i]);
    }
    return results;
}

/**
\brief Devolve uma entrada da matriz
@param t TABLE
@param n Posição na matriz
@returns char *
*/
char * get_string_table(TABLE t,int n){
    char* r;
    if(t->tab[n]) r = strdup(t->tab[n]);
    else r = NULL;
    return r;
}

/**
\brief Devolve um array com o tamanho da maior string de cada coluna
@param t TABLE
@returns int *
*/
int * getBlen_str(TABLE t){
    int countCols = 1;
    int size = 0;
    int nEntries = getEntries(t);
    char * str_c = strdup(t->tab[0]); 
    char * seped;
    int bigIt;
    while((seped = strsep(&str_c,";"))){
            countCols++;
    }
    int * bigger = malloc(sizeof(int)*countCols);
    for(int y=0;y<countCols;y++)
        bigger[y] = 0;
     for(int i=0;i<nEntries;i++){
        char * str = get_string_table(t,i);
        bigIt = 0;
        while((seped = strsep(&str,";"))){
            size = strlen(seped);
            if((int) size > bigger[bigIt]){
                bigger[bigIt] = size;
            }
            bigIt++; 
        }              
    }
    return bigger;
}

/**
\brief Imprime linhas dado um tamanho
@param n tamanho da linha a imprimir
@returns void
*/
void print_LineTops(int n){
    for(int i=0;i<n;i++)
        printf("-");
}

/**
\brief Imprime espaços dado um tamanho
@param n quantidade de espaços a imprimir
@returns void
*/
void printN_space(int n){
    for(int i=0;i<n;i++)
        printf(" ");
}


/**
\brief Retorna o número total de páginas
@param t - Table
@returns int
*/
int getTotalPages(TABLE t){
    int total_entries = getEntries(t);
    int total_pages = total_entries/MAXTPAGE ;
    if(total_pages%2==0)
        total_pages = total_entries/MAXTPAGE;
    else
    total_pages++;

    return total_pages;
}

/**
\brief Imprime uma header da TABLE,indentificando as colunas
@param str - Header a imprimir
@param biggers - Array de inteiros que guarda o tamanho da maior string de cada coluna
@param cols - Número de colunas
@returns void
*/
void printHeader(char * str,int *biggers,int cols){
    char * seped;

    for(int j=0;j<cols;j++){
        print_LineTops(biggers[j]+MARGIN);
    }
        printf("\n");
        printf("|");
        int while_Iterator = 0;
        while((seped = strsep(&str,";"))){
        int str_length = strlen(seped);
        int space_left = (biggers[while_Iterator]+MARGIN-str_length)/2;
        int space_rigth = (biggers[while_Iterator]+MARGIN-space_left-str_length);

        printN_space(space_left-1);
        printf("%s",seped);
        printN_space(space_rigth);
        printf("|");
        while_Iterator++;

        }
        printf("\n");
}

/**
\brief Imprime uma página da TABLE
@param current_page Página a imprimir
@returns void
*/
void printPage_table(TABLE t,int current_page){
    int total_entries = getEntries(t);
    int total_pages,bottom,top,while_Iterator;
    char * str_zero;
    
    total_pages = getTotalPages(t);

    if(total_entries<MAXTPAGE){ // quando só tem uma pagina como menos entradas das que é suposto imprimir por pagina
        total_pages = 1;
        bottom = 0;
        top = total_entries;
    }else if(current_page + 1  == total_pages){ // quando estamos na ultima pagina
        int entriesLeft = total_entries - (total_pages-1)*MAXTPAGE;
        bottom = current_page*MAXTPAGE;
        top = bottom + entriesLeft;
    }else{ //situação normal
        bottom = current_page*MAXTPAGE;
        top = bottom+MAXTPAGE;
    }

    char * seped;
    char * str_c = strdup(t->tab[0]); 
    int countCols = 0;
    while((seped = strsep(&str_c,";"))){
            countCols++;
    }
    int * biggers = getBlen_str(t);

    printHeader(strdup(t->tab[0]),biggers,countCols);

    for(int i=bottom+1;i<top;i++){

        str_zero = strdup(t->tab[i]);
       
        for(int j=0;j<countCols;j++){
            print_LineTops(biggers[j]+MARGIN);
        }
        printf("\n");
        printf("|");
        while_Iterator = 0;
        while((seped = strsep(&str_zero,";"))){
        int str_length = strlen(seped);
        int space_left = (biggers[while_Iterator]+MARGIN-str_length)/2;
        int space_rigth = (biggers[while_Iterator]+MARGIN-space_left-str_length);

        printN_space(space_left-1);
        printf("%s",seped);
        printN_space(space_rigth);
        printf("|");
        while_Iterator++;
        }
        printf("\n");
    
    }

    for(int j=0;j<countCols;j++){
            print_LineTops(biggers[j]+MARGIN);
            
    }
    printf("\n");
    printf("Page %d out of %d || Total entries: %d\n",current_page+1,total_pages,total_entries-total_pages);    
}
/**
\brief Indexa uma TABLE dado indices de linha e coluna atribui essa entrada numa nova variável TABLE
@param t TABLE
@param line Indice da linha
@param col Indice coluna
@returns TABLE
*/
TABLE index_table(TABLE t,int line,int col){
    TABLE indexed_table = init_Sized_Table(2);
    
    char * headLine = get_string_table(t,0);
    char * seped;
    for(int i=0;i<col+1;i++){
        seped=strsep(&headLine,";");
    }
    setNewLine(indexed_table,strdup(seped));

    char * strLine = get_string_table(t,line+1);
     for(int i=0;i<col+1;i++){
        seped=strsep(&strLine,";");
    }
    setNewLine(indexed_table,strdup(seped));

    return indexed_table;
}

/**
\brief Converte uma TABLE para ficheiro csv
@param x TABLE
@param delim Delimitador de campos
@param name Nome do ficheiro
@returns void
*/
void toCSV (TABLE x,char* delim, char* name){
    char s[2] =";";
    int entries = getEntries(x);
    FILE* f = fopen(name,"w"); 
    for(int i=0; i<entries ; i++){
        char * r = get_string_table(x,i);  
        char *tok = r, *end = r;
        while (tok != NULL) {
            strsep(&end, s);
            fprintf(f,"%s", tok);
            tok = end;
            if (tok != NULL) fprintf(f,"%s",delim); // para não colocar no último token
        }
        fprintf(f,"\n");
        free(r);
    }
    
    fclose(f);
}

//Recebe o input dado pelo o utilizador a passa-o para um array
/**
 * @brief le uma linha de um ficheiro utilizando um buffer dinamico
 * 
 * @param f ficheiro
 * @return char* 
 */
char* getLine_file(FILE *f){
    char buff[2000];
    buff[0] = '\0';
    char* input = malloc(sizeof(char) * 2000);
    input[0] = '\0';
    size_t inputlen = 0, bufflen = 0;
   do {
       if(fgets(buff, 2000, f)){
       bufflen = strlen(buff);
       input = realloc(input, inputlen+bufflen+1);
       strcat(input, buff);
       inputlen += bufflen;
       }
    } while (bufflen==2000-1 && buff[2000-2]!='\n');
    input[inputlen] ='\0';
    return input;
}


/**
\brief Dá o número de linhas de um ficheiro, é necessária para a fromCSV
@param file Nome do ficheiro
@returns int
*/
int nLinhas (char* file){
    FILE *fp;
    int count = 0; 
    fp = fopen(file, "r");
    char* buff = getLine_file(fp);
    while(strlen(buff) != 0){
        count++;
        buff = getLine_file(fp);
    }
    free(buff);
    // Close the file
    fclose(fp);
    return count;
}
/**
\brief Converte de um ficheiro csv para TABLE
@param delim Delimitador de campos
@param file Nome do ficheiro
@returns TABLE
*/
TABLE fromCSV (char* file, char* delim){
    FILE* f = fopen(file,"r");
    if (f==NULL){
        printf("ERROR_FILE_readFILE\n");
        TABLE z = init_Sized_Table(0);
        return z;
    }
    else{
        int n_lin = nLinhas(file);
        TABLE t = init_Sized_Table(n_lin);
        char* buffer = getLine_file(f); 
        char* pointer = buffer;
        char *aux = malloc(sizeof(char) * FROMCSV_BUFFER_SIZE);
        size_t auxlen = FROMCSV_BUFFER_SIZE, bufflen = strlen(buffer);
        while( bufflen != 0){
            aux[0] ='\0';
            if(auxlen < bufflen){
                auxlen = (auxlen + bufflen )*2;
                aux = realloc(aux,auxlen);
            }
            while (buffer != NULL) {
                strcat(aux,strsep(&buffer, delim));
                if (buffer != NULL && aux[strlen(aux)-1]!= ';')  strcat(aux,";"); // para não colocar no último token
            }
            setNewLine(t,aux);
            buffer = getLine_file(f);
            bufflen = strlen(buffer);
        }
        free(pointer);
        free(aux);
        fclose(f);
        printf("Read File.\n");
        return t;
    }
    
}

/**
\brief Projeta determinada coluna da TABLE recebida
@param x TABLE 
@param cols Nome da coluna a projetar
@returns TABLE
*/
TABLE proj(TABLE x, char* cols){
    TABLE t = init_Sized_Table(getEntries(x));
    char s [2] =";";
    char * str = get_string_table(x,0);  
    char *token = strtok(str,s);
    int col = 0;
    int r = 0;
    while(token != NULL && r == 0) {
        if(strcmp(token,cols)== 0){r = 1;setNewLine(t,token);break;}
        token = strtok(NULL, s);
        col++;
    }
    if (r == 1){
        for(int j = 1;j<getEntries(x);j++ ){
            char * res = get_string_table(x,j);
            char *aux = strtok(res,s);
            int tam = 0;
            while(aux != NULL && tam<col) {
                aux = strtok(NULL, s);
                tam++;
            }
            setNewLine(t,aux);
        }
        return t;
    }else {
        clearTable(t);
        printf("Coluna inexistente\n");
        TABLE z = init_Sized_Table(0);
        return z; 
    }
        
}

/**
 * @brief verifica se uma coluna existe na table
 * 
 * @param t table
 * @param column_name nome da coluna a procurar
 * @return int 
 */
int valid_column_name(TABLE t, char* column_name){
    if(t){
        char *line = strdup(t->tab[0]);
        char * buff = malloc(sizeof(char) * strlen(line));
        char * pointer = buff;
        buff = strsep(&line,";");
        while(buff != NULL){
            if(strcmp(buff,column_name) == 0){
                free(pointer); return 0;
                }
            buff = strsep(&line,";");
        }
        free(pointer);
    }
    return -1;
}



/**
\brief Filtra determinada coluna da TABLE recebida
@param x TABLE 
@param column_name Nome da coluna que será analizada
@param value Palavra utilizada na comparação
@param op Operador a aplicar na comparação
@returns TABLE
*/
TABLE filter (TABLE x,char* column_name,char* value, OPERADOR op){printf(".%s. .%s.\n",column_name,value);
    if(valid_column_name(x,column_name) == 0){ 
        TABLE comp = proj(x,column_name);
        int entries = getEntries(comp);
        //filtra ints
       if (entries!=0){
            TABLE res = init_Sized_Table(getEntries(x));
            setNewLine(res,get_string_table(x,0));
            char * r = get_string_table(comp,1);//vai buscar linha 1 porque 
            int c = 0;                          // a linha 0 e o formato da table
            if (isNumber(value)==0 || isFloat(value) == 0){ //filter para numeros
                for(int i = 1; i < entries;i++ ){
                    r = get_string_table(comp,i);
                    c = strcmp (r, value);
                    if (0 == op && c == 0) setNewLine(res,get_string_table(x,i));
                        else if (1 == op && c>0) setNewLine(res,get_string_table(x,i));
                            else if (-1 == op && c<0) setNewLine(res,get_string_table(x,i));
                }
            }
            else{ //filter para palavras
                for(int i = 1; i < entries;i++ ){
                    r = get_string_table(comp,i);
                    c = strcmp (r, value);
                    if (0 == op && c == 0) setNewLine(res,get_string_table(x,i));
                        else if (1 == op && c<0) setNewLine(res,get_string_table(x,i));
                            else if (-1 == op && c>0) setNewLine(res,get_string_table(x,i));
                }
            }
            free (r);
            return res;
        }
    }
    return NULL;
}


void printTable(TABLE t){
    if(t){
        int entries = getEntries(t);
        char * r;
        for(int i = 0; i < entries;i++ ){
        r = get_string_table(t,i);
        printf("%d -> %s\n",i,r);
        free(r);
        }
    }
    else printf("Table vazia.\n");
}
