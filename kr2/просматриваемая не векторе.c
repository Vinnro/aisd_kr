#include <stdlib.h>
#include <string.h>
#include "kr2_structs(просматриваемая).h"

//Просматриваемая на векторе

int table_find(const Table *table, const int key)
{
    for (int i = 0; i < table->csize; ++i)
        if (table->ks[i].busy && table->ks[i].key == key)
            return i;

    return -1;
}

int table_insert(Table *table, const int key, const char *info){
    if (table_find(table, key) >= 0)
        return 1;

    if (table->csize >= table->msize){
        table_garbage_collector(table);
        if (table->csize >= table->msize)
            return 1;
    }

    table->ks[table->csize].busy = 1;
    table->ks[table->csize].key = key;
    table->ks[table->csize].data = malloc(sizeof(char));
    table->ks[table->csize].data = strdup(info);

    ++table->csize;

    return 0;
}

int table_delete(Table *table, const int key){
    int i = table_find(table, key);
    if (i < 0)
        return 1;

    table->ks[i].busy = 0;

    return 0;
}

void table_garbage_collector(Table *table){
    int j = 0;
    for (int i = 0; i < table->csize; ++i){
        if (table->ks[i].busy){
            if (j == i){
                ++j;
                continue;
            }

            table->ks[j].busy = 1;
            table->ks[j].key = table->ks[i].key;
            table->ks[j].data = malloc(sizeof(char));
            table->ks[j].data = strdup(table->ks[i].data);

            ++j;
        }

        table->ks[i].busy = 0;
        free(table->ks[i].data);
    }

    table->csize = j;
}