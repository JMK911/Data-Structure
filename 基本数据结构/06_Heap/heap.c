#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define parent(idx) (idx-1)>>1
#define lson(idx) idx<<1|1
#define rson(idx) (idx+1)<<1
#define root 0

//定义堆存放的数据结构
typedef struct{
    int val;
    int times;
} DataType;

//定义堆的数据结构
typedef struct{
    DataType *data;
    int size;
    int capacity;
} Heap;

//选定存放数据结构中的某一项进行比较排序，将该函数中返回的数值取反即可得到相反排序的堆，当前为大顶堆
int compareData(DataType *a,DataType *b)
{
    if(a->times>b->times)
    {
        return  1;
    }else if(a->times<b->times)
    {
        return -1;
    }else{
        return  0;
    }
}

void swap(DataType *a,DataType *b)
{
    DataType tmp = *a;
    *a = *b;
    *b = tmp;
}

//下沉操作
void heapShiftDown(Heap *heap,int curr)
{
    int son = lson(curr);
    while(son<heap->size)
    {
        if(compareData(&heap->data[son],&heap->data[rson(curr)])<0)
        {
            son = rson(curr);//当前默认为大顶堆，所以需要找到子节点中的最大值与curr进行替换
        }
        if(compareData(&heap->data[son],&heap->data[curr])>0)
        {
            swap(&heap->data[son], &heap->data[curr]);
            curr = son;
            son = lson(curr);
        }else{
            break;
        }
    }
}

//上浮操作
void heapShiftUp(Heap *heap,int curr)
{
    int par = parent(curr);
    while(par>=root){
        if(compareData(&heap->data[curr],&heap->data[par])>0)       //  大于其父节点则二人互换
        {
            swap(&heap->data[curr], &heap->data[par]);
            curr = par;
            par = parent(curr);
        }else{
            break;
        }
    }
}

bool heapIsFull(Heap *heap)
{
    return heap->size == heap->capacity;
}

//判断堆是否为空
bool heapIsEmpety(Heap *heap)
{
    return heap->size == 0;
}

//push操作是将数据塞入堆底进行上浮
bool HeapPush(Heap *heap,DataType dt)
{
    if(heapIsFull(heap))
    {
        return false;
    }
    heap->data[heap->size++]=dt;
    heapShiftUp(heap,heap->size-1);
    return true;
}

//pop操作是删除堆顶元素，该处的实现是将堆底元素替换堆顶元素，然后下沉
bool HeapPop(Heap *heap)
{
    if (heapIsEmpety(heap)) {
        return false;
    }
    heap->data[root] = heap->data[--heap->size];
    heapShiftDown(heap, root);
    return true;
}

//堆的创建
Heap *HeapCreate(DataType *d,int arrSize,int maxSize)
{
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data= (DataType *)malloc(sizeof(DataType) *maxSize);
    h->size = 0;
    h->capacity = maxSize;
    for (int i = 0; i < arrSize;++i)
    {
        HeapPush(h, d[i]);
    }
    return h;
}

//获取堆顶元素
DataType HeapTop(Heap *heap)
{
    return heap->data[root];
}

//销毁
void HeapFree(Heap *heap)
{
    free(heap->data);
    free(heap);
}
