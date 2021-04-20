#include "../includes/table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
    t->tab = (char **) malloc(size);
    t->entries = 0;
    return t;
}
void clearTable(TABLE t){
    for(int i=0;i<t->entries;i++)
        free(t->tab[i]);
}
void setEntries(TABLE t,int x){
    t->entries = x;
}
void setTab(TABLE t, char** result){
    t->tab = result;
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

int getBlen_str(TABLE t){
    int bigger = 0;
    int size=0;
    int nEntries = getEntries(t);
    char * seped;
    for(int i=0;i<nEntries;i++){
        char * str = get_string_table(t,i);
        while((seped = strsep(&str,";"))){
            size = strlen(seped);
            if((int) size> bigger){
                bigger = size;
            } 
        }              
    }
    return bigger;
}

void print_LineTops(int n){
    for(int i=0;i<n;i++)
        printf("-");
    //printf("\n");
}
void printN_space(int n){
    for(int i=0;i<n;i++)
        printf(" ");
}

void printPage_table(TABLE t,int current_page){
    int total_entries = getEntries(t);
    printf("%d\n",getBlen_str(t));
    int space_in_line = getBlen_str(t) + MARGIN;
    int total_pages,bottom,top;

    if(total_entries<MAXTPAGE){
        total_pages = 0;
        bottom = 0;
        top = total_entries;
    }else{
        total_pages = total_entries/MAXTPAGE;
        bottom = current_page*MAXTPAGE;
        top = bottom+MAXTPAGE;
    }

    char * seped;
    char * str_c =strdup(t->tab[0]); 
    int countCols = 0;
    while((seped = strsep(&str_c,";"))){
            countCols++;
    }

    for(int i=bottom;i<top;i++){
        char * str_zero = strdup(t->tab[i]);
       
        for(int j=0;j<countCols;j++){
            print_LineTops(space_in_line);
        }
        printf("\n");
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

    for(int j=0;j<countCols;j++){
            print_LineTops(space_in_line);
        }
    printf("\n");
    printf("Page %d out of %d\n",current_page+1,total_pages+1);
}

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

}

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

/*
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
*/