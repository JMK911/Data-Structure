#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define DataType int
#define maxn 100005
struct Queue{
    DataType data[maxn<<1];
    int head, tail;
};

//初始化
void QueueClear(struct Queue *que)
{
    que->head = maxn;
    que->tail = maxn - 1;
}

//队列前方插入数据
void QueueFrontEn(struct Queue *que,DataType dt)
{
    que->data[--que->head] = dt;
}

//队列后方插入数据
void QueueRearEn(struct Queue *que,DataType dt)
{
    que->data[++que->tail] = dt;
}

//删除队列头部数据
void QueueFrontDel(struct Queue *que)
{
    ++que->head;//注意删除并不是真正意义上的删除，而是通过改变指针让其不可取，以及可覆盖。
}

//删除队列尾部数据
void QueueRearDel(struct Queue *que)
{
    --que->tail;
}

//获取头部数据
DataType QueueGetFront(struct Queue *que)
{
    return que->data[que->head];
}

//获取尾部数据
DataType QueueGetRear(struct Queue *que)
{
    return que->data[que->tail];
}

//获取队列大小
int QueueGetSize(struct Queue *que)
{
    return que->tail - que->head + 1;
}

//判断队列是否为空
bool QueueIsEmpty(struct Queue *que)
{
    return !QueueGetSize(que);
}
