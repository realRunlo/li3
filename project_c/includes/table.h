#ifndef ___TABLE_H___
#define ___TABLE_H___


typedef struct table * TABLE;

TABLE initTable();
TABLE init_Sized_Table(int size);
void clearTable(TABLE t);
void setEntries(TABLE t,int x);
void setTab(TABLE t, char** result);
void setNewLine(TABLE t,char * line);
int getEntries(TABLE t);
char* get_string_table(TABLE t,int n);
char** getTab(TABLE t);

int *getBlen_str(TABLE t);
int * getBlen_strV2(TABLE t);
void printPage_table(TABLE t,int current_page);
void print_Table(TABLE t);
TABLE index_table(TABLE t,int line,int col);
void toCSV (TABLE x,char delim, char* name);
TABLE fromCSV (char* file, char* delim);
TABLE proj(TABLE x, char* cols);



#endif //___TABLE_H___