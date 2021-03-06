#ifndef ___TABLE_H___
#define ___TABLE_H___


typedef struct table * TABLE;

typedef enum oper{
    LT = -1,
    EQ = 0,
    GT = 1,
}OPERADOR;

TABLE initTable();

TABLE init_Sized_Table(int size);

void clearTable(TABLE t);

void setEntries(TABLE t,int x);

void setTab(TABLE t, char** result);

void setNewLine(TABLE t,char * line);

int getEntries(TABLE t);

char* get_string_table(TABLE t,int n);

char** getTab(TABLE t);

int getTotalPages(TABLE t);

int * getBlen_str(TABLE t);

int getColsNum(TABLE t);

void printPage_table(TABLE t,int current_page);

TABLE index_table(TABLE t,int line,int col);

void toCSV (TABLE x,char* delim, char* name);

TABLE fromCSV (char* file, char* delim);

TABLE proj(TABLE x, char* cols);

int valid_column_name(TABLE t, char* column_name);

TABLE filter (TABLE x,char* column_name,char* value, OPERADOR op);

void printTable(TABLE t);//não vai ser precisa


#endif //___TABLE_H___