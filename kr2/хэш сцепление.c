#include <stdlib.h>
#include <string.h>
#include "limits.h"
#include "хэш сцепление.h"

int hash_int(const int key){
    int hash = INT_MAX;
    for (int i = 0; i < sizeof(key); ++i) {
        hash = 37 * hash + ((key >> i * 8) & 0xff);
    }
    return abs(hash);
}

KeySpace *table_find(const Table *table, const int key)
{
    int i = hash_int(key) % table->msize;
    for (KeySpace *p = table->ks[i]; p != NULL; p = p->next)
        if (p->key == key)
            return p;

    return NULL;
}

int table_insert(Table *table, const int key, const char *info)
{
    if (table_find(table, key) != NULL)
        return 1;

    KeySpace *new = (KeySpace *) malloc(sizeof(KeySpace));
    new->key = key;
    new->data = malloc(sizeof(char));
    new->data = strdup(info);

    int i = hash_int(key) % table->msize;
    new->next = table->ks[i];
    table->ks[i] = new;

    return 0;
}

int table_delete(Table *table, const int key)
{
    int i = hash_int(key) % table->msize;
    KeySpace *ptr = table->ks[i], *ptr_prev;
    while (ptr != NULL && ptr->key != key)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL)
        return 1;

    if (ptr == table->ks[i])
        table->ks[i] = table->ks[i]->next;
    else
        ptr_prev->next = ptr->next;

    free(ptr->data);
    free(ptr);

    return 0;
}