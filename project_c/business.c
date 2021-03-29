#include <stdio.h>
#include "business.h"

//Verifica se cada linha tem todos os campos corretamente
int valida_linha (char *str){
    char * a[5];
    for(int i=0; i<5;i++)
            a[i] =NULL;
    a[0] = strdup(strsep(&str,";"));
    a[1] = strdup(strsep(&str,";"));
    a[2] = strdup(strsep(&str,";"));
    a[3] = strdup(strsep(&str,";"));
    a[4] = strdup(strsep(&str,";"));
    char v [3] ="";
    int r = 1;
    for(int i=0;i<5;i++){
        if((strcmp(a[i],v)) == 0) return 0;
    }
    return r;
}

//Adiciona cada linha do ficheiro à estrutura Business
void add_b (Business *b, char *str,int p){
    b[p] = malloc(sizeof(struct business));
    b[p]->business_id = strdup(strsep(&str,";"));
    b[p]->name = strdup(strsep(&str,";"));
    b[p]->city = strdup(strsep(&str,";"));
    b[p]->state = strdup(strsep(&str,";"));
    b[p]->categories = strdup(strsep(&str,";"));
}

//Lê todo ficheiro linha a linha
void ler_ficheiro(char fic [] ){
    char buffer [5000];
    Business b [160587]; // número de linhas do ficheiro
    FILE *f = fopen(fic,"r");

    if(f!=NULL){
        for(int i=0; i<160587;i++)
            b[i] =NULL;
        
        int i=0;
        while(fgets(buffer,1024,f)){
            char dest [5000];
            strcpy(dest,buffer);
            int r = valida_linha(dest);
            if(r == 1){
                add_b(b,buffer,i);
                i++;
            }
        }/*para testar
        for(int j=0;j<10;j++){
            printf("indice %d: ",j);
            printf("%s ",b[j]->business_id);
            printf("%s ",b[j]->name);
            printf("%s ",b[j]->city);
            printf("%s ",b[j]->state);
            printf("%s",b[j]->categories); 
        }*/
    }
    else printf("ERROR opening file\n");
}

void main(){
    ler_ficheiro("business_full.csv");
}