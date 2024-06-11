#ifndef TABLE_H
#define TABLE_H

#include "../hash/hash.h"

typedef struct KeySpace{
    int busy;
    int key;
    char *data;
}KeySpace;

typedef struct Table
{
    KeySpace *ks;
    int msize;
}Table;

int table_find(const Table *, const int);
int table_insert(Table *, const int, const char *);
int table_delete(Table *, const int);

#endif