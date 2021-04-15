#include "../includes/table.h"
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
void clearTable(TABLE t){
    for(int i=0;i<t->entries;i++)
        free(t->tab[i]);
}
void setEntries(TABLE t,int x){
    t->entries = x;
}
void setTable(TABLE t,char ** matrix){
    t->tab = matrix;
}
void setNewLine(TABLE t,char * line){
    t->entries++;
    t->tab[t->entries] = strdup(line);
}

int getEntries(TABLE t){
    return t->entries;
}

char * get_string_table(TABLE t,int n){
    char* r;
    if(t->tab[n]) r = strdup(t->tab[n]);
    else r = NULL;
    return r;
}