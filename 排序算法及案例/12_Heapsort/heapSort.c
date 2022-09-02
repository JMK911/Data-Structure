#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "heap.h"



//哈希表
#define maxn (1<<17)
#define mask (maxn-1)
#define NULLKEY (1<<30)

typedef struct{
    int data[maxn];
}HashTable;

void HashInit(HashTable *ht)
{
    int i;
    for (i = 0; i < maxn;++i)
    {
        ht->data[i] = NULLKEY;
    }
}

int HashGetaddr(int key)
{
    return key & mask;
}

int HashSearchKey(HashTable *ht,int key,int *addr)
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

int HashInsertKey(HashTable *ht,int key)
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

int HashRemove(HashTable *ht,int key)
{
    int addr;
    if(!HashSearchKey(ht,key,&addr))
    {
        return NULLKEY;
    }
    ht->data[addr] = NULLKEY;
    return addr;
}

//K个频率最高的函数题目
HashTable ht;
int Hash[maxn];//HashTable存数组出现的数，Hash存映射地址后的数字出现的次数
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize)
{
    int i,hashval;
    *returnSize=0;
    Heap *h = HeapCreate(NULL, 0, numsSize);
    HashInit(&ht);
    memset(Hash, 0, sizeof(Hash));
    DataType dt;
    for (i = 0; i < numsSize;++i)
    {
        hashval = HashInsertKey(&ht, nums[i]);
        ++Hash[hashval];
    }
    for (i = 0; i < maxn;++i)
    {
        if(Hash[i]!=0)
        {
            dt.times = Hash[i];
            dt.val = ht.data[i];
            HeapPush(h, dt);
        }
    }
    while(k--)
    {
        nums[(*returnSize)++]=HeapTop(h).val;
        HeapPop(h);
    }
    return nums;
}
//数组打印
void numsPrint(int *nums,int n)
{
    for (int i = 0; i < n;++i)
    {
        printf("%d ", nums[i]);
    }
}
//测试案例
int main()
{
    int nums[20] = {6, 0, 1, 4, 9, 7, -3, 1, -4, -8, 4, -7, -3, 3, 2, -3, 9, 5, -4, 0};
    int k = 6;
    int returnSize;
    int *nnums = topKFrequent(nums, 20, k, &returnSize);
    numsPrint(nnums, returnSize);
    return 0;//排序结果应为[-3,1,9,4,0,-4]
}