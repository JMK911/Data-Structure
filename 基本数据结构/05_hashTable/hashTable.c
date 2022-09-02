#include <stdio.h>
#include <stdlib.h>

#define maxn (1<<17)
#define mask (maxn-1)
#define NULLKEY (1<<30)
#define DataType int

typedef struct{
    DataType data[maxn];
}HashTable;

void HashInit(HashTable *ht)
{
    int i;
    for (i = 0; i < maxn;++i)
    {
        ht->data[i] = NULLKEY;
    }
}

int HashGetaddr(DataType key)
{
    return key & mask;
}

int HashSearchKey(HashTable *ht,DataType key,int *addr)
{
    int startaddr = HashGetaddr(key);
    *addr = startaddr;
    while(ht->data[*addr]!=key)
    {
        *addr = HashGetaddr(*addr + 1);
        if(ht->data[*addr]==NULLKEY)
        {
            return 0;
        }
        if(*addr==startaddr)
        {
            return 0;
        }
    }
    return 1;
}

int HashInsertKey(HashTable *ht,DataType key)
{
    int addr = HashGetaddr(key);
    int retaddr;
    if(HashSearchKey(ht,key,&retaddr))
    {
        return retaddr;
    }
    while(ht->data[addr]!=NULLKEY)
    {
        addr = HashGetaddr(addr + 1);
    }
    ht->data[addr] = key;
    return addr;
}

int HashRemove(HashTable *ht,DataType key)
{
    int addr;
    if(!HashSearchKey(ht,key,&addr))
    {
        return NULLKEY;
    }
    ht->data[addr] = NULLKEY;
    return addr;
}