#ifndef ___TABLE_H___
#define ___TABLE_H___


typedef struct table * TABLE;

TABLE initTable();
void clearTable(TABLE t);
void setEntries(TABLE t,int x);
void setTable(TABLE t,char ** matrix)
void setNewLine(TABLE t,char * line);
int getEntries(TABLE t);
char* get_string_table(TABLE t,int n);



#endif //___TABLE_H___