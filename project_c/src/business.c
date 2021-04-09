#include "../includes/business.h"
#include <stdio.h>

typedef struct business{
    char * business_id;
    char * name;
    char * city;
    char * state;
    char * categories;

};

//Verifica se cada linha tem todos os campos corretamente
int check_line (char *str){
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
Business create_b (char *str){
    Business b= malloc(sizeof(struct business));
    b->business_id = strdup(strsep(&str,";"));
    b->name = strdup(strsep(&str,";"));
    b->city = strdup(strsep(&str,";"));
    b->state = strdup(strsep(&str,";"));
    b->categories = strdup(strsep(&str,";")); 
    return b;
}
char * get_id(Business b){
    return strdup(b->business_id);
}
char * get_name(Business b){
    return strdup(b->name);
}
char * get_city(Business b){
    return strdup(b->city);
}
char * get_state(Business b){
    return strdup(b->state);
}
char * get_categ(Business b){
    return strdup(b->categories);
}
void iterator(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data,  get_id((Business) value),
                    get_name((Business) value),
                    get_city((Business) value),
                    get_state((Business) value),
                    get_categ((Business) value));
}



/*//Lê todo ficheiro linha a linha
void read_file (char fic [] ){
    char buffer [5000];
    Business b;
    FILE *f = fopen(fic,"r");

    if(f!=NULL){
        GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
        
        int i=0;
        while(fgets(buffer,1024,f)){
            char dest [5000];
            strcpy(dest,buffer);
            int r = check_line(dest);
            if(r == 1){
                b = create_b(buffer);
                g_hash_table_insert(hash,GINT_TO_POINTER(get_id(b)),b);
                i++;
            }
        }
        int t = g_hash_table_size(hash);
        printf("%d\n",t);
        g_hash_table_foreach(hash, (GHFunc)iterator, "%s;%s;%s;%s;%s");
    }
    else printf("ERROR opening file\n");
}*/

/*
void main(){
    read_file("business_full.csv");
}
*/