#include "../includes/sgr.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*  ----------private structs----------  */
struct sgr{

    GHashTable * hashT_users;
    GHashTable * hashT_businesses;
    GHashTable * hashT_reviews;

};

/**
 * @brief struct query2 para usar no iterator
 * 
 */
typedef struct query2{
        char** result;
        char letter;
        int line;
}*Query2;

/**
 * @brief struct query3 para usar no iterator
 * 
 */
typedef struct query3{
      GHashTable * h_reviews_info;
}*Query3;

/**
 * @brief struct query4 para usar no iterator
 * 
 */
typedef struct query4{
        char** result; //[business_id1,business1],[business_id2,business2][...]
        char* user_id;
        GHashTable * hashT_businesses; // used to look for the name of the business in case there is a review on it by the user
        int line;
}*Query4;

/**
 * @brief struct query5 para usar no iterator
 * 
 */
typedef struct query5{
        TABLE t;
        char* city;
        float stars;
        GHashTable * hashT_business;
        GHashTable * h_reviews_info;
}*Query5;

/**
 * @brief struct da query6  para guardar informacoes sobre os top negocios de cada cidade 
 */
typedef struct city{
    char* name;
    char** top; //[score1,business1][score2,business2][...]
    int entries;
    float low_score;
}*CITY;

/**
 * @brief struct da query6
 * guarda a media de estrelas de um negocio
 */
typedef struct b_stars{
    char* b_id;
    char* b_name;
    char* city;
    int n_reviews;
    float total;
}*B_STARS;


/**
 * @brief struct da query6
 * user_data para business_average_stars
 */
typedef struct b_average_stars{
    SGR sgr;
    GHashTable * b_same;
    GHashTable * cities;
    int top;
    char* condition; //pode ser utilizado pelo query 8 para guardar a categoria procurada
    char** results;
    int entries; //numero de linhas preenchidas de results
    float lowScore;
}*B_AVERAGE_STARS;

/**
\brief struct query7 para usar no iterator
*/
typedef struct query7{
    TABLE t;
    GHashTable * h_user_and_businesses;// cada user tem lista de business que fez review
    GHashTable * hashT_businesses;
    GHashTable * h_state;
}*Query7;

typedef struct query9{
        TABLE t;
        char * word;
}*Query9;

/*  ----------private functions----------  */

/**
 * @brief iterator da query2 que coloca na table os business comecados com uma letra dada como argumento
 * 
 * @param key business_id
 * @param value business struct
 * @param user_data process, query2 struct onde esta guardado a letra para comparacao, a table e os numeros totais de entradas
 */
static void query2_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    char* name = get_name((Business) value);
    Query2 data = (Query2) user_data;
    char letter = data->letter;
    if(name[0] == tolower(letter) || name[0] == toupper(letter)){ 
        int line = data->line;
        data->result[line] = malloc(strlen(name) * sizeof(char));
        data->result[line] = name;
        data->line++;
    }
}

/**
 * @brief Coloca as estatisticas das reviews na hash h_reviews_info
 * 
 * @param key review_id
 * @param value review struct
 * @param user_data process, query3 struct onde esta guardado o apontador para a h_reviews_info
 */
static void reviews3_info(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    Reviews r = ((Reviews)value);
    char* b_id = r_getBusinessId((Reviews) value);
    Query3 data = (Query3)user_data;
    if(g_hash_table_lookup(data->h_reviews_info,GINT_TO_POINTER(b_id)) == NULL){
        B_STARS business = malloc(sizeof(struct b_stars));
        business->b_id = b_id;
        business->n_reviews = 1;
        business->total = r_getStars(r);
        addToHashT(data->h_reviews_info,GINT_TO_POINTER(b_id),business);
    }
    //se ja existir da update no numero de reviews e no total de estrelas
    else{
        B_STARS update = g_hash_table_lookup(data->h_reviews_info,GINT_TO_POINTER(b_id));
        update->n_reviews++;
        update->total += r_getStars(r);
    }
}

/**
 * @brief iterador da query4 procura na hash das reviews, reviews feitas por um user_id e guarda o business correspondente na table
 * 
 * @param key review_id
 * @param value review struct
 * @param user_data process, struct query4 que guarda a table, o apontador da hash dos businesses, o user_id em questao e o numero total de entries
 */
static void query4_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    Reviews r = (Reviews) value;
    char* user_id = r_getUserId(r);
    Query4 data = (Query4) user_data;

    if(strcmp(user_id,data->user_id) == 0){
        //Encontra o business correspondente ao business_id na review
        int l = data->line;
        char* b_id = r_getBusinessId(r);
        Business b = (Business) g_hash_table_lookup(data->hashT_businesses,GINT_TO_POINTER(b_id));
        char* b_name = get_name(b);
        char* result = malloc( sizeof(char) * (strlen(b_name) + strlen(b_id) + 1));
        //result = b_id,b_name
        snprintf(result,strlen(b_name) + strlen(b_id) + 2,"%s;%s",b_id,b_name);
        data->result[l] = result;
        data->line++;
        
    }
}
/**
 * @brief torna todos os elementos de uma string em minusculas
 * 
 * @param s string a modificar
 * @return char* 
 */
char * turn_lowerCases(char* s){
    int i = 0;
    char *lower = strdup(s);
    while(s[i] != '\0'){
        lower[i] = tolower(s[i]);
        i++;
    }
    lower[i] = '\0';
    return lower;
}
/**
@brief Verifica se tem o n??mero m??dio de estrelas necess??rio e a city correpondente.
A hash table analisada cont??m as estatisticas das reviews
@param key business_id
@param value struct bstar
@param user_data proc, struct query5 que guarda a table, a city dada, o n??mero de stars 
dado, o apontador da hash dos businesses e o apontador da h_reviews_info;
*/
static void query5_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    float b_stars = (((B_STARS) value)->total)/(((B_STARS) value)->n_reviews);
    Query5 data = (Query5) user_data;
    char* city_data = strdup(data->city);
    if(b_stars >= (data->stars)){
        char* b_id = strdup(((B_STARS) value)->b_id);
        Business b = (Business) g_hash_table_lookup(data->hashT_business,
                                        GINT_TO_POINTER(b_id));
    
        char* city_name = get_city(b);
        char* city = turn_lowerCases(city_name);
        if(strcmp(city,city_data) == 0){
            char* b_name = get_name(b);
            char* a = malloc( sizeof(char) * (strlen(b_id) + strlen(b_name) + 5));
            sprintf(a,"%s;%s",b_id, b_name);
            setNewLine(data->t,a);
        }
    }
}
/**
@brief Coloca as estatisticas das reviews na hash h_reviews_info;
@param key review_id
@param value review struct
@param user_data proc, struct query5 que guarda a table, a city dada, o n??mero de stars 
dado, o apontador da hash dos businesses e o apontador da h_reviews_info;
*/
static void reviews5_info(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    Reviews r = ((Reviews)value);
    char* b_id = r_getBusinessId((Reviews) value);
    Query5 data = (Query5)user_data;
    if(g_hash_table_lookup(data->h_reviews_info,GINT_TO_POINTER(b_id)) == NULL){
        B_STARS business = malloc(sizeof(struct b_stars));
        business->b_id = b_id;
        business->n_reviews = 1;
        business->total = r_getStars(r);
        addToHashT(data->h_reviews_info,GINT_TO_POINTER(b_id),business);
    }
    //se ja existir da update no numero de reviews e no total de estrelas
    else{
        B_STARS update = g_hash_table_lookup(data->h_reviews_info,GINT_TO_POINTER(b_id));
        update->n_reviews++;
        update->total += r_getStars(r);
    }
}

/**
 * @brief auxiliar da query6 que cria uma hash das diferentes cidades
 * 
 * @param key business_id
 * @param value business struct
 * @param user_data process, struct auxiliar da query 6 onde se vai guardar a hash das cidades
 */
static void city_hash(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Business b = (Business) value;

    //verifica se ja foi adicionada a cidade na table
    char* city_name = get_city(b);
    char* city = turn_lowerCases(city_name);
    city[0] = toupper(city[0]);
    if(g_hash_table_lookup(data->cities,GINT_TO_POINTER(city)) == NULL){
        CITY c = malloc(sizeof(struct city));
        c->entries = 0;
        c->low_score = 0;
        c->name = city;
        c->top = malloc(sizeof(char*) * data->top);
        addToHashT(data->cities,GINT_TO_POINTER(city),c);
    }
}

/**
 * @brief auxiliar da query 6 que percorre cada review para calcular a media de estrelas de cada negocio, guardando/atualizando
 *      numa nova hash de negocios (unindo os de mesmo id) onde guarda o numero total de estrelas e de reviews
 * 
 * @param key review_id
 * @param value review struct
 * @param user_data process, auxiliar da query 6 onde se vai guardar a nova hash de negocios com os dados das estrelas
 */
static void b_add_stars(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Reviews r = (Reviews) value;
    char *b_id = r_getBusinessId(r);
    
    //encontra o id do negocio da review
    Business b = g_hash_table_lookup(data->sgr->hashT_businesses,GINT_TO_POINTER(b_id));
    char* b_name = get_name(b);

    //verifica se ja existe um negocio na table de media de estrelas com o mesmo id
    if(g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id)) == NULL)
    {
        B_STARS business = malloc(sizeof(struct b_stars));
        business->b_id = b_id;
        business->b_name= b_name;
        business->city = get_city(b);
        business->n_reviews = 1;
        business->total = r_getStars(r);
        addToHashT(data->b_same,GINT_TO_POINTER(b_id),business);
    }
    //se ja existir da update no numero de reviews e no total de estrelas
    else{
        B_STARS update = g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id));
        update->n_reviews++;
        update->total += r_getStars(r);
    }
}

/**
 * @brief auxiliar da query6 que guarda/atualiza a matriz de cada struct de cidade da hash das cidades, os top negocios 
 *      
 * @param key business_id
 * @param value business struct
 * @param user_data process, struct auxiliar da query 6, onde tem a hash das cidades para guardar os tops
 *      de cada cidade, e a hash das estrelas de cada negocio(para comparar os negocios de uma cidade com o top do momento)
 */
static void top_city(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    B_STARS bStar = (B_STARS) value;
    GHashTable * cities = data->cities;
    char* b_name    = bStar->b_name;
    char* b_id      = bStar->b_id;
    char* city      = bStar->city;
    char* city_name = turn_lowerCases(city);
    city_name[0]    = toupper(city_name[0]);
    CITY c          = g_hash_table_lookup(cities,GINT_TO_POINTER(city_name));
    //verifica se houve reviews para o negocio em questao
    if(bStar != NULL){
    float average   = bStar->total / bStar->n_reviews;
    int i = 0; int top = data->top;
    
    //verifica se o negocio tem reviews e caso tenha o top cheio, se o score do negocio e menor do que o minimo do top
    //caso a cidade ja n tenha espaco no top e o score do negocio e menor do que o minimo do top
    if(c->entries == top && average < c->low_score);
    else{
        char stars[20]; //string para colocar as estrelas medias
        sprintf(stars,"%.2f",average); //float to string
        char * result = malloc(sizeof(char) * (strlen(stars) + strlen(b_name) + strlen(b_id) + 3)); //declaracao da string q sera colocada
        snprintf(result,strlen(stars) + strlen(b_id) + strlen(b_name)+ 3,"%s;%s;%s",stars,b_id,b_name);
        //caso em que ainda nao foram adicionados nenhuns negocios
        if(c->entries == 0){
            c->top[0] = result;
            c->low_score = average;
            c->entries++;
        }
        else{
            //verificar se o negocio ja foi adicionado
            i = 0;
            size_t maxLen = strlen(result);
            while(i < c->entries){
                if(strlen(c->top[i]) > maxLen) maxLen = strlen(c->top[i]);
                i++;
            }
            char*buffer = malloc(sizeof(char) * (maxLen + 1));    
            char *pointer = buffer;
            int found = 0;
            int i_lowest = 0;
            float lowest;
            i=0;
            while(i < c->entries && found !=1){
                buffer = pointer;
                buffer[0] = '\0';
                strcpy(buffer,c->top[i]);
                lowest = atof(strsep(&buffer,";"));  //torna a string da media de estrelas em um float  
                if (lowest == c->low_score) i_lowest = i; //guarda a posicao do menor score
                if (strcmp(b_id,strsep(&buffer,";")) == 0) found++;
                i++;
            }
            free(pointer);
            //se o negocio ainda n foi adicionado(e o seu score e superior ao minimo da cidade) mas o top ja esteja cheio, necessario trocar pelo de menor score
            if(found == 0 && c->entries == data->top && average > c->low_score){
                i = 0;
                maxLen = strlen(result);
                while(i < c->entries){
                    if(strlen(c->top[i]) > maxLen) maxLen = strlen(c->top[i]);
                    i++;
                }
                c->top[i_lowest] = result;
                //atualizar score mais baixo
                float min = 20;
                float s = 20;
                char*buffer2 = malloc(sizeof(char) * (maxLen + 1));
                char *pointer2 = buffer2;
                i=0;
                while(i < top){
                    buffer2 = pointer2;
                    buffer2[0] = '\0';
                    strcpy(buffer2,c->top[i]);
                    s = (float) atof(strsep(&buffer2,";"));
                    if(s< min) min = s;
                    i++;
                }
                c->low_score = min;
                free(pointer2);
            }
            //se a cidade ainda nao tem top negocios guardados, adiciona imediatamente numa posicao livre
            if(found == 0 && c->entries < data->top){
                c->top[c->entries] = result;
                if(average < c->low_score) c->low_score = average;
                c->entries++;
            }
        }
        }   
    }
}

/**
 * @brief Auxiliar da query6, recolhe o campo das estrelas de uma string e torna em float
 * 
 * @param business business com as suas estrelas medias
 * @return float estrelas 
 */
static float get_stars(char *business){
    char* buffer = strdup(business);
    char* pointer = buffer;
    float stars = atof(strsep(&buffer,";"));
    free(pointer);
    return stars;
}

/**
 * @brief auxiliar da quickSort_top
 * 
 * @param stars_index matriz a ordenar
 * @param low indice inferior da particao
 * @param high indice superior da particao
 * @return int 
 */
static int partition_top(float stars_index[][2], int low, int high){

    float pivot[2]; 
    pivot[0] = stars_index[high][0];
    pivot[1] = stars_index[high][1];
    int i = low-1;

    float swapper1[2] = {0,0}; float swapper2[2] = {0,0};
    for(int j = low; j <= high- 1; j++){
        if(stars_index[j][0] < pivot[0]){
            i++;  
            swapper1[0] = stars_index[j][0];swapper1[1] = stars_index[j][1];
            swapper2[0] = stars_index[i][0];swapper2[1] = stars_index[i][1];
            
            stars_index[i][0] = swapper1[0]; stars_index[i][1] = swapper1[1];  
            stars_index[j][0] = swapper2[0]; stars_index[j][1] = swapper2[1];  
        }
    }
    swapper1[0] = stars_index[high][0]; swapper1[1] = stars_index[high][1];
    swapper2[0] = stars_index[i+1][0];  swapper2[1] = stars_index[i+1][1];
    stars_index[high][0] = swapper2[0]; stars_index[high][1] = swapper2[1];  
    stars_index[i+1][0] = swapper1[0];  stars_index[i+1][1] = swapper1[1];  
    return (i + 1);
}

/**
 * @brief adaptacao do algoritmo quicksort para ordenar uma matriz em que o primeiro indice
 *  serve como valor para ordenar e o segundo indice indica a sua posicao original
 * @param stars_index matriz a ordenar
 * @param low indece inferior da particao
 * @param high indice superior da particao
 */
static void quickSort_top(float stars_index[][2], int low, int high){
    if(low < high){
        int pi = partition_top(stars_index, low, high);

        quickSort_top(stars_index, low, pi -1);
        quickSort_top(stars_index, pi + 1, high);
    }
}

/**
 * @brief auxiliar das query 6 e 8, que ordena os top business utilizando uma adaptacao do 
 * algoritmo quicksort
 * @param top lista a ordenar
 * @param entries numero de entradas da lista
 * @param low limite inferior da lista para ordenar
 * @return char** lista original ordenada
 */
static char** sort_top(char** top, int entries,int low){
    float stars_index[entries][2];
    int k = 0;
    for(int i = low; i<entries ; i++,k++){
        stars_index[k][0] = get_stars(top[i]);
        stars_index[k][1] = i;
    }
    quickSort_top(stars_index,0,entries-1-low);
    char** sorted_top = malloc(sizeof(char*) * entries);
    int j = low;
    for(int i = 0; i<low;i++){
        sorted_top[i] = top[i];
    }
    k=0;
    for(int i = low; i<entries; i++,k++){
        j = (int) stars_index[k][1];
        sorted_top[i] = top[j];
    }
    return sorted_top;
}

/**
 * @brief transfere a matriz do top guardada em cada struct de city para a table
 * 
 * @param key city_name
 * @param value city struct (struct auxiliar da query 6)
 * @param user_data table onde se guardara os tops de cada cidade
 */
static void city_to_table(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    TABLE result = (TABLE) user_data;
    CITY c = (CITY) value;
    int j = 0 ,k = 0;
    size_t maxlength = 0 ;
    if(c->entries > 0){
    //calcula o tamanho necessario para concatenar os dados dos negocios todos da cidade
    for(; j< c->entries;j++){ 
        if (maxlength < strlen(c->top[j])) maxlength = strlen(c->top[j]);
        }
    char  buff[strlen(c->name) + maxlength + 2];
    
    //concatena os dados dos negocios e coloca-os na table
    char** sorted_top = sort_top(c->top,c->entries,0); 
    for(k=0 ; k<j;k++){
        buff[0] = '\0';
        snprintf(buff,strlen(c->name)+strlen(sorted_top[k]) + 2,"%s;%s",c->name,sorted_top[k]);
        setNewLine(result,buff);
    }
    }
}

/**
 * @brief Coloca o user_id na table se tiver pelo menos dois estados diferentes com review
 * 
 * @param key user_id
 * @param value lista com os business_id onde o user fez review
 * @param user_data proc, struct query7 que guarda a table, o apontador da hash dos businesses,
o apontador da hash dos users que fizeram reviews 
e o apontador da hash que cont??m os estados
 */
static void check_state_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    Query7 data = (Query7) user_data;
    data->h_state = g_hash_table_new(g_str_hash, g_str_equal);
    int t = g_slist_length((GSList*)value);
    GSList* iterator = NULL;
    if(t>1){
        for (iterator = (GSList*)value; iterator; iterator = iterator->next) {
            char* b_id = strdup(iterator->data);
            Business b = (Business) g_hash_table_lookup(data->hashT_businesses,
                                            GINT_TO_POINTER(b_id));
            char* b_state = get_state(b);
            g_hash_table_insert(data->h_state, b_state,NULL);
        }
        if((g_hash_table_size(data->h_state))>=2){
            setNewLine(data->t,key);
        }
    } 
}

/**
 * @brief Coloca na hash h_user o user_id como key e uma lista com os business_id que
foram visitados pelo user
 * 
 * @param key review_id
 * @param value review struct
 * @param user_data proc, struct query7 que guarda a table, o apontador da hash dos businesses,
o apontador da hash dos users que fizeram reviews 
e o apontador da hash que cont??m os estados
 */
static void query7_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    char* user_id = strdup(r_getUserId((Reviews) value));
    char* b_id =  strdup(r_getBusinessId((Reviews) value));
    Query7 data = (Query7) user_data;
    g_hash_table_insert(data->h_user_and_businesses, user_id,
        g_slist_append(g_hash_table_lookup(data->h_user_and_businesses, user_id),b_id));
}

/**
 * @brief auxiliar da query 8, verifica se a categoria procura na query8 se encontra na lista de categorias 
 *      do negocio analisado no momento
 * 
 * @param c_condition categoria procura na query8
 * @param c_comparing lista de categorias de um negocio
 * @return int 
 */
static int cmp_category(char* c_condition,char* c_comparing){
    int i = 0, j = 0;
    if(c_condition[0] == '\0' && c_comparing[0] == '\0') return 0;
    for(;c_comparing[j] != '\0' ;j++){
        if(c_condition[i] == '\0' && (c_comparing[j] == ',' || c_comparing[j] == ';')) return 0;
        else if(c_condition[i] == tolower(c_comparing[j]) || c_condition[i] == toupper(c_comparing[j])) i++;
            else if(c_condition[i] != c_comparing[j]) i = 0;
    }
    return 1;
}



/**
 * @brief auxiliar da query8, similar ao da query6, calcula o numero de estrelas medias de cada negocio,
 *      neste caso que tenham a categoria procurada
 * 
 * @param key reviews_id
 * @param value reviews struct
 * @param user_data struct auxiliar da query8, onde se vai guardar uma hash de negocios da categoria procurada
 *             com o respetivo numero de estrelas e reviews
 */
static void b_category(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    Reviews r = (Reviews) value;
    char *b_id = r_getBusinessId(r);
    
    //encontra o id do negocio da review
    Business b = g_hash_table_lookup(data->sgr->hashT_businesses,GINT_TO_POINTER(b_id));
    char* b_category = get_categ(b);

    //verifica se o negocio reviewed pertence a categoria procurada
    if(cmp_category(data->condition,b_category) == 0){
        //verifica se ja existe um negocio na table de media de estrelas com o mesmo id
        if(g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id)) == NULL)
        {
            char* b_name = get_name(b);
            B_STARS business = malloc(sizeof(struct b_stars));
            business->b_id = b_id;
            business->b_name= b_name;
            business->n_reviews = 1;
            business->total = r_getStars(r);
            addToHashT(data->b_same,GINT_TO_POINTER(b_id),business);
        }
        //se ja existir da update no numero de reviews e no total de estrelas
        else{
            B_STARS update = g_hash_table_lookup(data->b_same,GINT_TO_POINTER(b_id));
            update->n_reviews++;
            update->total += r_getStars(r);
        }
    }

}


/**
 * @brief auxiliar da query8, similar ao da query6, guarda/atualiza o top negocios de uma dada categoria
 *      
 * @param key business_id
 * @param value B_STARS struct, onde se guarda os negocios com as respetivas estrelas e reviews
 * @param user_data B_AVERAGE_STARS struct, onde se guarda os resultados para a table
 */
static void top_category(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    B_AVERAGE_STARS data = (B_AVERAGE_STARS) user_data;
    B_STARS b = (B_STARS) value;
    char** results  = data->results; 
    char* b_name    = b->b_name;
    char* b_id      = b->b_id;    
    float average   = b->total / b->n_reviews;
    int i = 0; int top = data->top;
    //verifica se o negocio tem reviews e caso tenha o top cheio, se o score do negocio e menor do que o minimo do top
    //caso a cidade ja n tenha espaco no top e o score do negocio e menor do que o minimo do top
    if(data->entries == top && average < data->lowScore);
    else{
        char stars[20]; //string para colocar as estrelas medias
        sprintf(stars,"%.2f",average); //float to string
        char * result = malloc(sizeof(char) * (strlen(stars) + strlen(b_name) + strlen(b_id) + 3)); //declaracao da string q sera colocada
        snprintf(result,strlen(stars) + strlen(b_id) + strlen(b_name)+ 3,"%s;%s;%s",stars,b_id,b_name);
        //caso em que ainda nao foram adicionados nenhuns negocios
        if(data->entries == 0){
            results[1] = result;
            data->lowScore = average;
            data->entries++;
        }
        else{
            //verificar se o negocio ja foi adicionado
            i = 1;
            size_t maxLen = strlen(result);
            while(i < data->entries+1){
                if(strlen(results[i]) > maxLen) maxLen = strlen(results[i]);
                i++;
            }
            i = 1;
            char*buffer = malloc(sizeof(char) * (maxLen +1));
            buffer[0] = '\0';
            char *pointer = buffer;

            int found = 0;
            int i_lowest = 1;
            float lowest;
            while(i < data->entries+1 && found !=1){
                buffer = pointer;
                strcpy(buffer,results[i]);
                lowest = atof(strsep(&buffer,";"));  //torna a string da media de estrelas em um float 
                if (lowest == data->lowScore) i_lowest = i; //guarda a posicao do menor score
                if (strcmp(b_id,strsep(&buffer,";")) == 0) found++;
                i++;
            }
            free(pointer);
            //se o negocio ainda n foi adicionado(mas tem score superior ao minimo da categoria) mas o top ja esteja cheio, necessario trocar pelo de menor score
            if(found == 0 && data->entries == top && average > data->lowScore){
                i = 1;
                maxLen = strlen(result);
                while(i < data->entries+1){
                    if(strlen(results[i]) > maxLen) maxLen = strlen(results[i]);
                    i++;
                }
                i=1;
                results[i_lowest] = result;
                //atualizar score mais baixo
                float min = 20;
                float s = 20;
                char*buffer2 = malloc(sizeof(char) * (maxLen + 1));
                buffer2[0] = '\0';
                char *pointer2 = buffer2;
                while(i < data->entries+1){
                    buffer2 = pointer2;
                    strcpy(buffer2,results[i]);
                    s = (float) atof(strsep(&buffer2,";"));
                    if(s< min) min = s;
                    i++;
                }
                data->lowScore = min;
                free(pointer2);
                
            }
            //se a cidade ainda nao tem top negocios guardados, adiciona imediatamente numa posicao livre
            if(found == 0 && data->entries < data->top){
                results[data->entries+1] = result;
                //atualizar min score se necessario
                if (average < data->lowScore) data->lowScore = average;
                data->entries++;
            }
        }
    }   
}

/**
 * @brief Verifica se uma palavra ocorre numa stri g
 * 
 * @param str String
 * @param word Palavra
 * @return int 
 */
static int wordInString(char *str,char * word){
    char * buffer = malloc(strlen(str) + 1);
    int j=0;
    for(int i=0;str[i]!='\0';i++){
        if((!isspace(str[i]) && !ispunct(str[i])) || str[i] == '\''){
            buffer[j++] = str[i];
        }else{
            
            buffer[j] = '\0';
            if(strcmp(buffer,word)==0){
                free(buffer);
                return 1;
            }
            j = 0;
            
        }
        
    }
     buffer[j] = '\0';
        if(strcmp(buffer,word)==0){
            free(buffer);
            return 1;
        }
    free(buffer);
    return 0;
}

/**
 * @brief Iterador da query9 
 * 
 * @param key 
 * @param value
 * @param user_data 
 */
static void query9_iterator(gpointer key, gpointer value, gpointer user_data){ 
    UNUSED(key);
    Query9 data = (Query9) user_data;
    char * word = strdup(data->word);
    char * txt = r_getText((Reviews) value);
    
    if(wordInString(txt,word))
        setNewLine(data->t,r_getReviewId((Reviews) value));  
   
}

/**
 * @brief Iterador para cria????o de catalogo de reviews
 * 
 * @param key 
 * @param value
 * @param user_data 
 */
static void revCatalog_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    TABLE catalog = (TABLE) user_data;

    char * revId = r_getReviewId((Reviews) value);
    char * usId = r_getUserId((Reviews) value);
    char * busId = r_getBusinessId((Reviews) value);
    float stars = r_getStars((Reviews) value);
    int useful = r_getUseful((Reviews) value);
    int funny = r_getFunny((Reviews) value);
    int cool = r_getCool((Reviews) value);
    char * date = r_getDate((Reviews) value);
    

    size_t size = strlen(revId)+strlen(usId)+strlen(busId) + 6 +strlen(date) + 7 ;
    char * buffer = malloc(sizeof(char)*size);
    snprintf(buffer,size,"%s;%s;%s;%.2f;%d;%d;%d;%s",revId,usId,busId,stars,useful,funny,cool,date);
    setNewLine(catalog,buffer);
}

/**
 * @brief Iterador para cria????o de catalogo de users
 * 
 * @param key 
 * @param value
 * @param user_data 
 */
static void usCatalog_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    TABLE catalog = (TABLE) user_data;

    char * usId = getUserId((User) value);
    char * name = getUserName((User) value);
    
    size_t size = strlen(usId) + strlen(name) + 2 ;
    char * buffer = malloc(sizeof(char) * size);
    snprintf(buffer,size,"%s;%s",usId,name);
    setNewLine(catalog,buffer);

}

/**
 * @brief Iterador para cria????o de catalogo de business
 * 
 * @param key 
 * @param value
 * @param user_data 
 */
static void busCatalog_iterator(gpointer key, gpointer value, gpointer user_data){
    UNUSED(key);
    TABLE catalog = (TABLE) user_data;

    char * bus_id = get_id((Business) value);
    char * name = get_name((Business) value);
    char * city = get_city((Business) value);
    char * state = get_state((Business) value);

    size_t size = strlen(bus_id) + strlen(name) + strlen(city) + strlen(state) + 3;
    char * buffer = malloc(sizeof(char) * size);
    snprintf(buffer,size,"%s;%s;%s;%s",bus_id,name,city,state);
    setNewLine(catalog,buffer);
}
/*  ----------public----------  */

/**
 * @brief verifica se o sgr e valido, tem as 3 hashTables nao nulas
 * 
 * @param sgr 
 * @return int 
 */
int check_sgr(SGR sgr){
    if(sgr == NULL) return 0;
    if(sgr->hashT_users != NULL && sgr->hashT_businesses != NULL && sgr->hashT_reviews != NULL) return 1;
    return 0;
}


/**
 * @brief da free nas hashes tables de uma estrutura sgr
 * 
 * @param sgr 
 */
void free_sgr_hashes(SGR sgr){
    free_all_key_value_entries(sgr->hashT_users);
    free_all_key_value_entries(sgr->hashT_businesses);
    free_all_key_value_entries(sgr->hashT_reviews); 
}

/**
 * @brief modifica o sgr atual, dando free nas hashes e guardando novas
 *      criadas a partir de novos diretorios
 * 
 * @param sgr 
 * @param users 
 * @param businesses 
 * @param reviews 
 */
void sgr_new_hashes(SGR sgr,char * users, char* businesses, char* reviews){
    free_sgr_hashes(sgr);
    sgr->hashT_users = initHashT();
    sgr->hashT_businesses = initHashT();
    sgr->hashT_reviews = initHashT();
    readUser(sgr->hashT_users,users);
    readBusiness(sgr->hashT_businesses,businesses);
    readReviews(sgr->hashT_reviews,reviews,sgr->hashT_users,sgr->hashT_businesses);
}

/**
 * @brief Inicializador de dados SGR
 * 
 * @return SGR 
 */
SGR init_sgr(){

    SGR new_sgr = malloc(sizeof(struct sgr));

    new_sgr->hashT_users = initHashT();
    new_sgr->hashT_reviews= initHashT();
    new_sgr->hashT_businesses = initHashT();

    return new_sgr;
}

/**
 * @brief Liberta espa??o das tabelas de hash da estrutura sgr
 * 
 * @param sgr Apontador struct sgr
 */
void free_sgr(SGR sgr){
    free_all_key_value_entries(sgr->hashT_users);
    free_all_key_value_entries(sgr->hashT_businesses);
    free_all_key_value_entries(sgr->hashT_reviews);
}

/**
 * @brief QUERY1,carrega ficheiros para uma struct sgr
 * 
 * @param users_file Nome do ficheiro de users
 * @param buinesses_file Nome de ficheiro de businesses
 * @param reviews_file Nome de ficheiro de reviews
 * @return SGR 
 */
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file){
    
    SGR sgr_load = init_sgr();
    
    readUser(sgr_load->hashT_users,users_file);

    readBusiness(sgr_load->hashT_businesses,buinesses_file);

    readReviews(sgr_load->hashT_reviews,reviews_file,sgr_load->hashT_users,sgr_load->hashT_businesses);
    return sgr_load;
}

/**
 * @brief QUERY2,procura os neg??cios cujo o nome come??a com uma dada letra
 * 
 * @param sgr Apontador struct sgr
 * @param letter Letra
 * @return TABLE 
 */
TABLE businesses_started_by_letter(SGR sgr, char letter){
    int max_lines = g_hash_table_size(sgr->hashT_businesses) + 1;
    Query2 process = malloc(sizeof(struct query2));
    char* firstLine = "business_name";
    process->letter = letter;
    process->result = (char ** ) malloc(max_lines * sizeof(*process->result));
    process->result[0] = strdup(firstLine);
    process->line = 1;
    //search every key in the hash for a business name starting with letter
    //if one is found, then result and total are updated 
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)query2_iterator,process);
    
    //turning the results from process into TABLE
    TABLE result = initTable();
    setTab(result,process->result);
    setEntries(result,process->line);
    return result;
}

/**
 * @brief QUERY3,dado um id de neg??cio determinar sua informa????o
 * 
 * @param sgr Apontador struct sgr
 * @param business_id Id do neg??cio
 * @return TABLE 
 */
TABLE business_info (SGR sgr, char* business_id){
    TABLE r = init_Sized_Table(2);
    char* indicador = "total_rev;stars;business_id;business_name;business_city;business_state;business_categories";
    setNewLine(r,indicador);
    Business b = (Business) g_hash_table_lookup(sgr->hashT_businesses,
                                            GINT_TO_POINTER(business_id));
    if(b){
        char* b_name = get_name(b);
        char* b_c = get_city(b);
        char* b_s = get_state(b);
        char* b_cat = get_categ(b);
        Query3 pro = malloc(sizeof(struct query3));
        pro->h_reviews_info = g_hash_table_new(g_str_hash, g_str_equal);

        g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)reviews3_info,pro);
        B_STARS u = g_hash_table_lookup(pro->h_reviews_info,GINT_TO_POINTER(business_id));
        float s = u->total/u->n_reviews;
        char* res = malloc( sizeof(char) * (strlen(business_id) + strlen(b_name) + 
                            strlen(b_cat)+strlen(b_c)+ strlen(b_s)+15));
        sprintf(res,"%d;%.2f;%s;%s;%s;%s;%s",u->n_reviews,s,business_id, b_name,b_c,b_s,b_cat);
        setNewLine(r,res);
    }
    else r = NULL;
    return r;
}

/**
 * @brief  QUERY4,dado um utilizador determina a lista de neg??cios aos quais fex review
 * 
 * @param sgr Apontador struct sgr
 * @param user_id Id do utilizador
 * @return TABLE 
 */
TABLE businesses_reviewed(SGR sgr, char *user_id){
    int max_lines = g_hash_table_size(sgr->hashT_businesses) + 1;
    Query4 process = malloc(sizeof(struct query4));
    char* firstLine = "business_id;business_name";
    process->result = (char ** ) malloc(max_lines * sizeof(*process->result));
    process->result[0] = strdup(firstLine);
    process->user_id = strdup(user_id);
    process->hashT_businesses = sgr->hashT_businesses;
    process->line = 1;
    
    //procura o user_id nas reviews
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)query4_iterator, process);
    TABLE result = initTable();
    setTab(result,process->result);
    setEntries(result,process->line);
    free(process->user_id);
    return result;
}

/**
 * @brief QUERY5,determina a lista de neg??cios na dada cidade com n ou mais estrelas
 * 
 * @param sgr Apontador struct sgr
 * @param stars Estrelas
 * @param city Cidade
 * @return TABLE 
 */
TABLE businesses_with_stars_and_city (SGR sgr, float stars,char* city){
    Query5 pro = malloc(sizeof(struct query5));
    int max_lines = g_hash_table_size(sgr->hashT_businesses);
    pro->t = init_Sized_Table(max_lines);
    char* ind = "business_id;business_name";
    setNewLine(pro->t,ind);
    pro->city = turn_lowerCases(city);
    pro->stars = stars;
    pro->hashT_business = sgr->hashT_businesses;
    
    pro->h_reviews_info = g_hash_table_new(g_str_hash, g_str_equal);
    
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)reviews5_info,pro);  
    
    g_hash_table_foreach(pro->h_reviews_info, (GHFunc)query5_iterator,pro); 
    return pro->t;
}

/**
 * @brief QUERY6,determina os top neg??cios de cada cidade
 * 
 * @param sgr Apontador struct sgr
 * @param top Top
 * @return TABLE 
 */
TABLE top_businesses_by_city(SGR sgr, int top){
    B_AVERAGE_STARS process = malloc(sizeof(struct b_average_stars));
    process->b_same = initHashT(); //hash para guardar o numero medio de estrelas de cada negocio
    process->sgr = sgr;
    process->cities = initHashT(); //hash para descobrir o numero total de cidades diferentes 
    process->top = top;

    //cria table em q cada elemento e uma cidade distinta
    g_hash_table_foreach(sgr->hashT_businesses, (GHFunc)city_hash, process);
    int total_cities = g_hash_table_size(process->cities);

    //percorrer todas as reviews e vai criando uma hash de negocios para guardar o numero total de reviews dele e a soma das estrelas
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)b_add_stars, process);
    
    //para cada business verifica a cidade a que pertence e verifica se pertence ao top dessa cidade
    g_hash_table_foreach(process->b_same, (GHFunc)top_city, process);
    

    TABLE result = initTable();
    setEntries(result,0);
    setTab(result,malloc(sizeof(char*) * (total_cities * top + 1)));
    setNewLine(result,"city;stars;business_id;business_name");
    
    g_hash_table_foreach(process->cities, (GHFunc)city_to_table, result);

    free_all_key_value_entries(process->b_same);   
    free_all_key_value_entries(process->cities);     
    return result;
}

/**
 * @brief QUERY7,determina lista de utilizadores que tenham visitado mais de um estado
 * 
 * @param sgr Apontador struct sgr
 * @return TABLE 
 */
TABLE international_users (SGR sgr){
    Query7 pro = malloc(sizeof(struct query7));
    int max_lines = g_hash_table_size(sgr->hashT_reviews);
    pro->t = init_Sized_Table(max_lines);
    char* ind = "user_id";
    setNewLine(pro->t,ind);
    pro->hashT_businesses=sgr->hashT_businesses;
    pro->h_user_and_businesses = g_hash_table_new(g_str_hash, g_str_equal);
    pro->h_state = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)query7_iterator,pro);
    g_hash_table_foreach(pro->h_user_and_businesses, (GHFunc)check_state_iterator,pro);
    return pro->t;
}

/**
 * @brief QUERY8,determina lista dos top n neg??cios que pertencem a uma determianda caegoria
 * 
 * @param sgr Apontador struct sgr
 * @param top Top
 * @param category Categoria
 * @return TABLE 
 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category){
    B_AVERAGE_STARS process = malloc(sizeof(struct b_average_stars));
    process->b_same = initHashT(); //hash para guardar o numero medio de estrelas de cada negocio
    process->sgr = sgr;
    process->top = top+1;
    process->condition = strdup(category);
    process->results = malloc(sizeof(char*) * (top + 2));
    process->results[0] = strdup("stars;business_id;business_name");
    process->entries = 0;

    //percorrer todas as reviews e vai criando uma hash de negocios para guardar o numero total de reviews dele e a soma das estrelas
    g_hash_table_foreach(sgr->hashT_reviews, (GHFunc)b_category, process);

    //calcular os top negocios e guardar numa matriz de top linhas
    g_hash_table_foreach(process->b_same, (GHFunc)top_category, process);
    
    //tornar a matriz em forma TABLE
    TABLE result = initTable();
    setEntries(result,process->entries+1);
    setTab(result,sort_top(process->results,process->entries+1,1));

    return result;
}

/**
 * @brief QUERY9:Dada uma palavra,determinar a lista de ids de reviews que a referem no campo text
 * 
 * @param sgr struct sgr
 * @param word Palavra a procurar
 * @return TABLE 
 */
TABLE reviews_with_word(SGR sgr,char * word){
    int max_lines = g_hash_table_size(sgr->hashT_reviews);
    Query9 query_data = malloc(sizeof(struct query9));
    query_data->t = init_Sized_Table(max_lines);
    query_data->word = strdup(word);
 
    setNewLine(query_data->t,"review_id");
    
    
    g_hash_table_foreach(sgr->hashT_reviews,(GHFunc) query9_iterator,query_data);
    
    return query_data->t;
}

/**
 * @brief Retorna um catalogo de businesses numa table
 * 
 * @param sgr Estrutura com as hashtables do dados
 * @return TABLE 
 */
TABLE businesses_catalog(SGR sgr){
    int max_lines = g_hash_table_size(sgr->hashT_businesses);
    TABLE catalog = init_Sized_Table(max_lines);

    setNewLine(catalog,"business_id;name;city;state");

    g_hash_table_foreach(sgr->hashT_businesses,(GHFunc)busCatalog_iterator,catalog);

    return catalog;
}

/**
 * @brief Retorna um catalogo de users numa table
 * 
 * @param sgr Estrutura com as hashtables do dados
 * @return TABLE 
 */
TABLE users_catalog(SGR sgr){
    int max_lines = g_hash_table_size(sgr->hashT_users);
    TABLE catalog = init_Sized_Table(max_lines);

    setNewLine(catalog,"user_id;name");

    g_hash_table_foreach(sgr->hashT_users,(GHFunc)usCatalog_iterator,catalog);

    return catalog;
}

/**
 * @brief Retorna um catalogo de reviews numa table
 * 
 * @param sgr Estrutura com as hashtables do dados
 * @return TABLE 
 */
TABLE reviews_catalog(SGR sgr){
    int max_lines = g_hash_table_size(sgr->hashT_reviews);
    TABLE catalog = init_Sized_Table(max_lines);

    setNewLine(catalog,"review_id;user_id;business_id;stars;useful;funny;cool;date");

    g_hash_table_foreach(sgr->hashT_reviews,(GHFunc) revCatalog_iterator,catalog);

    return catalog;
}
