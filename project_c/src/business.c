#include "../includes/business.h"
#include <stdio.h>


struct business{
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
