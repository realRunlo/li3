#ifndef ___SHOW_H___
#define ___SHOW_H___
#include "../includes/table.h"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void show_banner();

void show_info_banner();

void show_bar();

void show_welcome();

void show_exit();

void show_sgr_options();

int show_pagedTable(TABLE t ,int page);





#endif //___SHOW_H___