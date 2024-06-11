#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "хэш сложение.h"

int hash_int(const int key){
    int hash = INT_MAX;
    for (int i = 0; i < sizeof(key); ++i) {
        hash = 37 * hash + ((key >> i * 8) & 0xff);
    }
    return abs(hash);
}

int table_find(const Table *table, const int key)
{
    int i = hash_int(key) % table->msize, n = 0;
    while (n < table->msize && table->ks[i].busy != 0)
    {
        if (table->ks[i].busy == 1 && table->ks[i].key == key)
            return i;

        i = (i + 1) % table->msize;
        ++n;
    }

    return -1;
}

int table_insert(Table *table, const int key, const char *info)
{
    if (table_find(table, key) >= 0)
        return 1;

    int i = hash_int(key) % table->msize, n = 0;
    while (n < table->msize && table->ks[i].busy == 1)
    {
        i = (i + 1) % table->msize;
        ++n;
    }

    if (n >= table->msize)
        return 1;

    table->ks[i].busy = 1;
    table->ks[i].key = key;
    table->ks[i].data = malloc(sizeof(char));
    table->ks[i].data = strdup(info);

    return 0;
}

int table_delete(Table *table, const int key)
{
    int i = table_find(table, key);
    if (i < 0)
        return 1;

    table->ks[i].busy = -1;
    free(table->ks[i].data);

    return 0;
}