#ifndef ___SGR_H___
#define ___SGR_H___

#include "../includes/table.h"
#include "../includes/structs.h"
#include "../includes/reading.h"
#include "../includes/user.h"
#include "../includes/reviews.h"
#include "../includes/business.h"
#define UNUSED(x) (void)(x)


typedef struct sgr * SGR;


SGR init_sgr();

int check_sgr(SGR sgr);

void free_sgr(SGR sgr);

/* query 1 */
SGR load_sgr(char * users_file,char *buinesses_file,char * reviews_file);

/* query 2 */
TABLE businesses_started_by_letter(SGR sgr, char letter);

/* query 3*/
TABLE business_info (SGR sgr, char* business_id);

/* query 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id);

/* query 5 */
TABLE businesses_with_stars_and_city (SGR sgr, float stars,char* city);

/* query 6 */
TABLE top_businesses_by_city(SGR sgr, int top);

/* query 7 */
TABLE international_users (SGR sgr);

/* query 8 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category);

/* query 9 */
TABLE reviews_with_word(SGR sgr,char * word);


void sgr_new_hashes(SGR sgr,char * users, char* businesses, char* reviews);

TABLE reviews_catalog(SGR sgr);

TABLE users_catalog(SGR sgr);

TABLE businesses_catalog(SGR sgr);

#endif //___SGR_H___


