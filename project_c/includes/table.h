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




#endif //___TABLE_H___