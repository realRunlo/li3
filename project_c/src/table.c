#include "../includes/table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MARGIN 6
#define MAXTPAGE 10

struct table{

   char ** tab;
   int entries;

};

TABLE initTable(){
    TABLE t = malloc(sizeof(struct table));
    t->tab = NULL;
    t->entries = 0;
    return t;
}
TABLE init_Sized_Table(int size){
    TABLE t = malloc(sizeof(struct table));
    t->tab =  malloc(sizeof(char*) * size);
    t->entries = 0;
    return t;
}
void clearTable(TABLE t){
    if(t){
        for(int i=0;i<t->entries;i++)
            free(t->tab[i]);
    }
}
void setEntries(TABLE t,int x){
    t->entries = x;
}
void setTab(TABLE t, char** result){
    t->tab = result;
}

int isEndtable(TABLE t,int i){

    if(t->tab[i] == NULL)
        return 1;
    
    return 0;
}

void setNewLine(TABLE t,char * line){
    t->tab[t->entries] = strdup(line);
    t->entries++;
}

int getEntries(TABLE t){
    return t->entries;
}

char** getTab(TABLE t){
    int entries = getEntries(t);
    char **results = malloc(sizeof(char*) * entries);
    for(int i=0; i<entries ; i++){
        results[i] = strdup(t->tab[i]);
    }
    return results;
}

char * get_string_table(TABLE t,int n){
    char* r;
    if(t->tab[n]) r = strdup(t->tab[n]);
    else r = NULL;
    return r;
}

int * getBlen_str(TABLE t){
    int countCols = 1;
    int size = 0;
    int nEntries = getEntries(t);
    char * str_c =strdup(t->tab[0]); 
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

void print_LineTops(int n){
    for(int i=0;i<n;i++)
        printf("-");
}

void printN_space(int n){
    for(int i=0;i<n;i++)
        printf(" ");
}

void printPage_table(TABLE t,int current_page){
    int total_entries = getEntries(t);
    int total_pages,bottom,top,while_Iterator;
    char * str_zero;
    total_pages = total_entries/MAXTPAGE + 1;

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
    char * str_c =strdup(t->tab[0]); 
    int countCols = 0;
    while((seped = strsep(&str_c,";"))){
            countCols++;
    }
    int * biggers = getBlen_str(t);
    for(int i=bottom;i<top;i++){

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

        printN_space(space_left);
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
    printf("Page %d out of %d\n",current_page+1,total_pages);    
}
/*
void print_Table(TABLE t){
    int space_in_line = getBlen_str(t) + MARGIN;
    char * seped;
    for(int i=0;i<getEntries(t);i++){
        char * str_zero = strdup(t->tab[i]);
        print_LineTops(space_in_line);
        printf("|");
        while((seped = strsep(&str_zero,";"))){
        int str_length = strlen(seped);
        int space_left = (space_in_line-str_length)/2;
        int space_rigth = (space_in_line-space_left-str_length);

        printN_space(space_left);
        printf("%s",seped);
        printN_space(space_rigth);
        printf("|");
        }
        printf("\n");
    }
    print_LineTops(space_in_line);

}*/

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
        seped=strsep(&strLine,",");
    }
    setNewLine(indexed_table,strdup(seped));

    return indexed_table;
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
                if (token != NULL)  strcat(r,";");// para não colocar no último token
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
