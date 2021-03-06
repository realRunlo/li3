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
 * @brief Inicializa uma table
 * 
 * @return TABLE 
 */
TABLE initTable(){
    TABLE t = malloc(sizeof(struct table));
    t->tab = NULL;
    t->entries = 0;
    return t;
}

/**
 * @brief Inicializa uma table com um dado tamanho
 * 
 * @param size Tamanho a alocar a matriz da table
 * @return TABLE 
 */
TABLE init_Sized_Table(int size){
    TABLE t = malloc(sizeof(struct table));
    t->tab =  malloc(sizeof(char*) * size);
    t->entries = 0;
    return t;
}

/**
 * @brief Limpa a matriz da table libertando o espaço
 * 
 * @param t TABLE
 */
void clearTable(TABLE t){
    if(t){
        for(int i=0;i<t->entries;i++)
            free(t->tab[i]);
    }
}

/**
 * @brief Atribuiu um número de entradas
 * 
 * @param t TABLE
 * @param x Número de entradas
 */
void setEntries(TABLE t,int x){
    t->entries = x;
}

/**
 * @brief Atribuiu uma matrix ao campo tab da TABLE
 * 
 * @param t TABLE
 * @param result Matriz a atribuir
 */
void setTab(TABLE t, char** result){
    t->tab = result;
}

/**
 * @brief Adiciona nova linha à matriz
 * 
 * @param t TABLE
 * @param line line Linha a adicionar
 */
void setNewLine(TABLE t,char * line){
    t->tab[t->entries] = strdup(line);
    t->entries++;
}

/**
 * @brief Devolve número de entradas da matriz
 * 
 * @param t TABLE
 * @return int 
 */
int getEntries(TABLE t){
    return t->entries;
}

/**
 * @brief Devolve o campo tab de uma TABLE,uma matriz
 * 
 * @param t TABLE
 * @return char** 
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
 * @brief Devolve uma entrada da matriz
 * 
 * @param t TABLE
 * @param n Posição na matriz
 * @return char* 
 */
char * get_string_table(TABLE t,int n){
    char* r;
    if(t->tab[n]) r = strdup(t->tab[n]);
    else r = NULL;
    return r;
}

/**
 * @brief Devolve um array com o tamanho da maior string de cada coluna
 * 
 * @param t TABLE
 * @return int* 
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
 * @brief Imprime linhas dado um tamanho
 * 
 * @param n Tamanho da linha a imprimir
 */
void print_LineTops(int n){
    for(int i=0;i<n;i++)
        printf("-");
}

/**
 * @brief Imprime espaços dado um tamanho
 * 
 * @param n Quantidade de espaços a imprimir
 */
void printN_space(int n){
    for(int i=0;i<n;i++)
        printf(" ");
}

/**
 * @brief Retorna o número de colunas de uma table
 * 
 * @param t Table
 * @returns void
 */
int getColsNum(TABLE t){
    char *str = get_string_table(t,0);
    char *seped;
    int countCols = 0;
    while((seped = strsep(&str,";"))){
            countCols++;
    }
    return countCols;
}

/**
 * @brief Retorna o número total de páginas
 * 
 * @param t Table
 * @return int 
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
 * @brief Imprime a linha edentificadora do nome das colunas
 * 
 * @param str Header a imprimir
 * @param biggers Array de inteiros que guarda o tamanho da maior string de cada coluna
 * @param cols Número de colunas
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
 * @brief Imprime uma página da TABLE
 * 
 * @param t TABLE
 * @param current_page Página a imprimir
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
    int countCols = getColsNum(t);

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
    if(total_entries<MAXTPAGE){
        printf("Page %d out of %d || Total entries: %d\n",1,total_pages,total_entries-1);
    }else
    printf("Page %d out of %d || Total entries: %d\n",current_page+1,total_pages,total_entries-1);    
}

/**
 * @brief Indexa uma TABLE dado indices de linha e coluna atribui essa entrada numa nova variável TABLE
 * 
 * @param t TABLE
 * @param line Indice da linha
 * @param col Indice coluna
 * @return TABLE 
 */
TABLE index_table(TABLE t,int line,int col){
    TABLE indexed_table = init_Sized_Table(2);
    char * headLine = get_string_table(t,0);
    char * seped =strsep(&headLine,";");;
    for(int i=1;i<col+1;i++){
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
 * @brief Converte uma TABLE para ficheiro csv
 * 
 * @param x  TABLE
 * @param delim Delimitador de campos
 * @param name Nome do ficheiro
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


/**
 * @brief Dá o número de linhas de um ficheiro, é necessária para a fromCSV
 * 
 * @param file Nome do ficheiro
 * @return int 
 */
int nLinhas (char* file){
    FILE *fp;
    int count = 0; 
    fp = fopen(file, "r");
    ssize_t linelen = 0; size_t line_buf_len = 0;
    char * line = NULL;
    linelen = getline(&line,&line_buf_len,fp);
    while(linelen >=0)
    {   
        count++;
        linelen = getline(&line,&line_buf_len,fp);
    }
    free(line);
    // Close the file
    fclose(fp);
    return count;
}

/**
 * @brief Converte de um ficheiro csv para TABLE
 * 
 * @param file Nome do ficheiro
 * @param delim Delimitador de campos
 * @return TABLE 
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
        ssize_t linelen = 0; size_t line_buf_len = 0;
        char * line = NULL;
        linelen = getline(&line,&line_buf_len,f);
        char *aux = malloc(sizeof(char) * linelen);
        size_t auxlen = linelen;
        while( linelen >=0){
            aux[0] ='\0';
            if(auxlen < linelen){
                auxlen = (auxlen + linelen )*2;
                aux = realloc(aux,auxlen);
            }
            while (line != NULL) {
                strcat(aux,strsep(&line, delim));
                if (line != NULL && aux[strlen(aux)-1]!= ';')  strcat(aux,";"); // para não colocar no último token
                else if(aux[strlen(aux)-1]== '\n') aux[strlen(aux)-1] = '\0';
            }
            setNewLine(t,aux);
            linelen = getline(&line,&line_buf_len,f);
        }
        free(line);
        free(aux);
        fclose(f);
        printf("Read File.\n");
        return t;
    }
    
}

/**
 * @brief verifica se um array contem um certo valor
 * 
 * @param arr array a analisar
 * @param size tamanho do array
 * @param value valor a procurar
 * @return int 
 */
int in_array(int* arr, int size, int value){
    int found = 0;
    for(int i =0; found == 0 && i<size; i++){
        if(arr[i] == value) found++;
    }
    return found;
}

/**
 * @brief Projeta numa nova estrutura table determinadas colunas da TABLE recebida
 * 
 * @param x TABLE 
 * @param cols Nome da coluna a projetar
 * @return TABLE 
 */
TABLE proj(TABLE x, char* cols){
    int valid = 0, columns = 0;
    for(int i = 0; cols[i] != '\0' ;i++){//conta o numero de colunas pedido
        if(cols[i] == ',') columns++;
    }
    columns++;
    if(cols != NULL){
        char** c = malloc(sizeof(char*) * columns);
        int j = 0, k = 0, i = 0; 
        int save[columns]; //guarda a posicao das colunas no formato da primeira linha
        while(cols[i] != '\0' && valid == 0){//verifica se todas as colunas sao validas
            i = addSpaces(i,cols);
            c[j] = commandString(cols+i);
            i+= strlen(c[j]);
            i = addSpaces(i,cols);
            if(cols[i] == ',') i++;
            i = addSpaces(i,cols);
            if((k = valid_column_name(x,c[j])) == -1){
                 valid++;
            }
            else save[j] = k; 
            j++;
        }
        if(valid == 0){//todas as colunas sao validas
            int entries = getEntries(x);
            TABLE t = init_Sized_Table(entries); 
            char* aux;char* line ;
            char *projLine = malloc(sizeof(char) * 200);
            size_t projLen = 200; size_t lineLen = 0;
            int r = 0, l = 0;
            for(j = 0;j<entries;j++){
                r = 0; l =0;
                projLine[0] = '\0';
                line = get_string_table(x,j);
                lineLen = strlen(line);
                if(projLen < lineLen){
                    projLen = lineLen*2;
                    projLine = realloc(projLine,projLen);
                } 
                char* pointer = line;
                aux = strsep(&line,";");
                while(aux != NULL) {
                    if(in_array(save,columns,r)){l++;
                        strcat(projLine,aux);
                        if(l<columns) strcat(projLine,";");
                    }
                    aux = strsep(&line,";");
                    r++;
                }
                setNewLine(t,projLine);
                free(pointer);
            }
            return t;
        }
    }
    printf("Invalid column\n");
    TABLE z = NULL;
    return z; 
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
        int i = 0;
        while(buff != NULL){
            if(strcmp(buff,column_name) == 0){
                free(pointer); return i;
                }
            buff = strsep(&line,";");
            i++;
        }
        free(pointer);
    }
    return -1;
}

/**
 * @brief Filtra determinada coluna da TABLE recebida
 * 
 * @param x TABLE 
 * @param column_name Nome da coluna que será analizada
 * @param value Palavra utilizada na comparação
 * @param op Operador a aplicar na comparação
 * @return TABLE 
 */
TABLE filter (TABLE x,char* column_name,char* value, OPERADOR op){
    if(valid_column_name(x,column_name) != -1){ 
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

/**
 * @brief funcao de testes
 * 
 * @param t table a dar print
 */
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
