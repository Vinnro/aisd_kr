#include <stdlib.h>
#include <string.h>
#include "kr2_structs(упорядоченная).h"

int table_find(const Table *table, const int key)
{
    int start = 0, end = table->csize - 1;
    while (start <= end)
    {
        int middle = (start + end) / 2;

        if (table->ks[middle].key == key)
            return middle;

        if (table->ks[middle].key > key)
            end = middle - 1;
        else
            start = middle + 1;
    }

    return -1;
}

int table_insert(Table *table, const int key, const char *info)
{
    if (table_find(table, key) >= 0)
        return 1;

    if (table->csize >= table->msize)
        return 1;

    int i = table->csize - 1;
    table->ks[i+1].data = malloc(sizeof(char));
    while (i >= 0 && table->ks[i].key > key)
    {
        table->ks[i+1].key = table->ks[i].key;
        table->ks[i+1].data = table->ks[i].data;

        --i;
    }

    table->ks[i+1].key = key;
    table->ks[i+1].data= strdup(info);

    ++table->csize;

    return 0;
}

int table_delete(Table *table, const int key)
{
    int i = table_find(table, key);
    if (i < 0)
        return 1;

    free(table->ks[i].data);
    while (i < table->csize - 1)
    {
        table->ks[i].key = table->ks[i+1].key;
        table->ks[i].data = table->ks[i+1].data;

        ++i;
    }
    free(table->ks[i].data);

    --table->csize;

    return 0;
}