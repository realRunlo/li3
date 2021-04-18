#include "../includes/table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    t->tab = (char **) malloc(sizeof(char *)*size);
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
