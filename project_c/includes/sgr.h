#ifndef ___SGR_H___
#define ___SGR_H___

#include "../includes/structs.h"
#include "../includes/reading.h"
#include "../includes/user.h"
#include "../includes/reviews.h"
#include "../includes/business.h"

typedef struct sgr * SGR;

typedef struct table * TABLE;


int getEntries(TABLE t);
char* get_string_table(TABLE t,int n);

SGR init_sgr();
void free_sgr(SGR sgr);
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file);



//iterator for query2, used to find a business started by a certain char 
//and if so store the results in user_data
void query2_iterator(gpointer key, gpointer value, gpointer user_data);

/* query 2 */
//list of businesses whose name starts with char "letter" and total amount found
TABLE businesses_started_by_letter(SGR sgr, char letter);
/* query 3*/
void query3_iterator(gpointer key, gpointer value, gpointer user_data);
TABLE business_info (SGR sgr, char* business_id);

//iterator for query4, verifies if the user_id from value(review) equals user_id from user_data
//if so finds the name of the business from the corresponding review and adds both the business_id 
//and business_name to the result in user_data
void query4_iterator(gpointer key, gpointer value, gpointer user_data);

/* query 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id);

/* query 5*/
void query5_iterator(gpointer key, gpointer value, gpointer user_data);
TABLE businesses_with_stars_and_city (SGR sgr, float stars,char* city);

/* query 6 */
void city_hash(gpointer key, gpointer value, gpointer user_data);

void b_add_stars(gpointer key, gpointer value, gpointer user_data);

void top_city(gpointer key, gpointer value, gpointer user_data);

TABLE top_businesses_by_city(SGR sgr, int top);




/*query 7 */
void query7_iterator(gpointer key, gpointer value, gpointer user_data);
TABLE international_users (SGR sgr);

/*query 8 */

int cmp_category(char* c_condition,char* c_comparing); 

void b_category(gpointer key, gpointer value, gpointer user_data);

void top_category(gpointer key, gpointer value, gpointer user_data);

TABLE top_businesses_with_category(SGR sgr, int top, char *category);


/*query 9 */
TABLE reviews_with_word(SGR sgr,char * word);
#endif //___SGR_H___


