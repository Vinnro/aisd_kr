#ifndef TABLE_H
#define TABLE_H

#include "../hash/hash.h"


typedef struct KeySpace{
    int key;
    char *data;
    struct KeySpace *next;
}KeySpace;

typedef struct Table{
    KeySpace **ks;
    int msize;
}Table;

KeySpace *table_find(const Table *, const int);
int table_insert(Table *, const int, const char *);
int table_delete(Table *, const int);

#endif