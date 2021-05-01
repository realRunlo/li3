#include "../includes/business.h"
#include <stdio.h>

/*  ----------private----------  */
struct business{
    char * business_id;
    char * name;
    char * city;
    char * state;
    char * categories;

};

/*  ----------public----------  */


/**
\brief Verifica se o campo city tem uma vírgula no meio, se tiver tudo a partir dai é 
ignorado
@param s A string city
@returns char * - string com o nome
*/
void check_comma (char* city){
    char s =',';
    int i=0;
    while(city[i] != '\0'){
        if ((city[i] - s)==0){
            city[i] = '\0';
            break;            
        }i++;
    }    
}
/**
\brief Conta quantos campos tem cada linha 
ignorado
@param str A string linha do ficheiro business
@returns int número de ';' que existem na string
*/
int count_fiels (char* str){
    char s =';';
    int i=0,r=0;
    while(str[i] != '\n'){
        if ((str[i] - s)==0){
          r++;             
        }
        i++;
    }
    return r;    
}
/**
\brief Verifica se cada linha tem todos os campos corretamente e  se não tem campos a mais
@param str A linha
@returns int 0 se estiver algo mal e 1 se estiver tudo correto
*/
int check_line (char *str){
    if(count_fiels(str) == 4){
        char * test = strdup(str);
        char * seped;
        int i = 0;
        seped = strsep(&test,";");
        if(strcmp(seped,"")==0) return 0;// testa o business_id
        seped = strsep(&test,";");
        if(strcmp(seped,"")==0) return 0;// testa o name
        seped = strsep(&test,";");
        if(strcmp(seped,"")==0) return 0;// testa a city
        check_comma(seped);
        seped = strsep(&test,";");
        if(strcmp(seped,"")==0) return 0;// testa o state
        //seped = strsep(&test,";");      as categories  podem ser vazias
        //if(strcmp(seped,"")==0) return 0;
        return 1;
    }
    else return 0;
}


/**
\brief Mapea dados para uma struct business
@param str com informação
@returns Business - apontador struct business
*/
Business create_b (char *str){
    Business b= malloc(sizeof(struct business));
    b->business_id = strdup(strsep(&str,";"));
    b->name = strdup(strsep(&str,";"));
    b->city = strdup(strsep(&str,";"));
    b->state = strdup(strsep(&str,";"));
    b->categories = strdup(strsep(&str,"\n")); 
    return b;
}
/**
\brief Devolve o campo id
@param b Apontador para struct business
@returns char * - string com o id
*/
char * get_id(Business b){
    return strdup(b->business_id);
}
/**
\brief Devolve o campo name
@param b Apontador para struct business
@returns char * - string com o name
*/
char * get_name(Business b){
    return strdup(b->name);
}
/**
\brief Devolve o campo city
@param b Apontador para struct business
@returns char * - string com a city
*/
char * get_city(Business b){
    return strdup(b->city);
}
/**
\brief Devolve o campo  state
@param b Apontador para struct business
@returns char * - string com o state
*/
char * get_state(Business b){
    return strdup(b->state);
}
/**
\brief Devolve o campo  categories
@param b Apontador para struct business
@returns char * - string com as categories
*/
char * get_categ(Business b){
    return strdup(b->categories);
}

/**
\@brief simples iterator para imprimir uma hashtable de business
@param key business_id
@param value business
@param user_data formato de print
*/
void iterator(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data,  get_id((Business) value),
                    get_name((Business) value),
                    get_city((Business) value),
                    get_state((Business) value),
                    get_categ((Business) value));
}
