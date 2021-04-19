#include "../includes/table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MARGIN 6

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
    int nEntries = getEntries(t);
    for(int i=0;i<nEntries;i++){
        if((int) strlen(t->tab[i]) > bigger){
            bigger = strlen(t->tab[i]);
            //printf("%d------%d: %s\n",bigger,i,get_string_table(t,i));
            //printf("%d------%s\n",bigger,get_string_table(t,i));
        }
            
        
            
    }
    return bigger;
}

void print_LineTops(int n){
    for(int i=0;i<n;i++)
        printf("-");
    printf("\n");
}
void printN_space(int n){
    for(int i=0;i<n;i++)
        printf(" ");
}
void print_Table(int space_in_line,TABLE t){
    
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

void show(TABLE t){
    int space_in_line = getBlen_str(t) + MARGIN;
    print_Table(space_in_line,t);
    

}
void toCSV (TABLE x){
    int entries = getEntries(x);
    FILE* f = fopen("filepath.csv","w");
    for(int i=0; i<entries ; i++){
        char * r = get_string_table(x,i);
        fprintf(f,"%s\n",r);   
    }
    fclose(f);
}


TABLE fromCSV (char* file){
    TABLE t = init_Sized_Table(1000000);
    FILE* f = fopen(file,"r");
    if (f==NULL){
        printf("ERROR_FILE_readFILE\n");
    }
    else{
        char buffer[1024]; // espaco suficiente para os exemplos do input file
        while(fgets(buffer,1024,f)){
            setNewLine(t,buffer);
            printf("%s",buffer);
        }
    }
    fclose(f);
    printf("Read File.\n");
    return t;

}
