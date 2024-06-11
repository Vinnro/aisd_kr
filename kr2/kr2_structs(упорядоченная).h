#ifndef TABLE_H
#define TABLE_H

typedef struct KeySpace{
    int key;
    char *data;
}KeySpace;

typedef struct Table{
    KeySpace *ks;
    int msize;
    int csize;
}Table;

int table_find(const Table *, const int);
int table_insert(Table *, const int, const char *);
int table_delete(Table *, const int);

#endif