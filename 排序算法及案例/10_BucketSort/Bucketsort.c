#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#define maxn (1<<17)
#define mask (maxn-1)
#define NULLKEY (1<<30)
#define DataType int

// 哈希表
typedef struct{
    DataType data[maxn];
} HashTable;

void HashInit(HashTable *ht)
{
    for (int i = 0; i < maxn;++i)
    {
        ht->data[i] = NULLKEY;
    }
}

int HashGetaddr(DataType key)
{
    return key & mask;
}

bool HashSearchKey(HashTable *ht,DataType key,int *addr)
{
    int startaddr = HashGetaddr(key);
    *addr = startaddr;
    while(ht->data[*addr]!=key)
    {
        *addr = HashGetaddr(*addr + 1);
        if(ht->data[*addr]==NULLKEY)
        {
            return false;
        }
        if(*addr==startaddr)
        {
            return false;
        }
    }
    return true;
}

int HashInsert(HashTable *ht,DataType key)
{
    int addr, retaddr;
    if(HashSearchKey(ht,key,&retaddr))
    {
        return retaddr;
    }
    addr = HashGetaddr(key);
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

//桶排序
struct Node{
    DataType data;
    struct Node *next;
};

struct Node *Bucket[maxn];

void addBucket(struct Node **Bucket,DataType dt,int pos)//桶排序的pos即桶数组的下标，对按次数排序的题目而言，是次数，数组上对应的内容为值或者值的hash
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = dt;
    node->next = Bucket[pos];
    Bucket[pos] = node;//头插法在Bucket[pos]的位置插入同样频率的结点，
                        //pos为出现的次数
}

//K个频率最高的函数题目
HashTable ht;
int Hash[maxn];//HashTable存数组出现的数，Hash存映射地址后的数字出现的次数
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize)
{
    int i,Hashaddr;
    struct Node *head;
    *returnSize = 0;
    HashInit(&ht);
    memset(Bucket, NULL, sizeof(Bucket));
    memset(Hash, 0, sizeof(Hash));
    for (i = 0; i < numsSize;++i)
    {
        Hashaddr = HashInsert(&ht, nums[i]);
        ++Hash[Hashaddr];
    }
    for (i = 0; i < maxn;++i)
    {
        if(Hash[i])
        {
            addBucket(Bucket, i, Hash[i]);//i即是Hashaddr，桶数组的内容即是hashaddr(值的hash)
        }
    }
    for (i = maxn-1; i>=0;--i)
    {
        if(!k)
        {
            break;
        }
        if(Bucket[i])
        {
            head = Bucket[i];
            while(head)
            {
                nums[(*returnSize)++] = ht.data[head->data];
                head = head->next;
                --k;
            }
        }
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
    int returnSize;
    int nums[10] = {1, 3, 1, 2, 3, 2, 1, 2, 1, 4};
    int *numss = topKFrequent(nums, 10, 3, &returnSize);
    numsPrint(numss, returnSize);
    return 0;
}
//总结，HashTable进行数组的数值映射，Hash的下标即为映射后的地址，存放的是
// 数组中这个数字出现的次数；Bucket的下标即为次数，存放映射后的地址，再通过HashTable[addr]
// 获得次数对应的数值；获取前K个高频元素，则从Bucket尾部倒序遍历，低频则反之；