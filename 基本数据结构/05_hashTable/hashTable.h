#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#define maxn (1<<17)

#define DataType int

typedef struct{
    DataType data[maxn];
}HashTable;

void HashInit(HashTable *ht);

int HashGetaddr(DataType key);

int HashSearchKey(HashTable *ht, DataType key, int *addr);

int HashInsertKey(HashTable *ht, DataType key);

int HashRemove(HashTable *ht, DataType key);

#endif