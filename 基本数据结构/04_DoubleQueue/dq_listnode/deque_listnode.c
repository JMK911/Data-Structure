#include <stdio.h>
#include <stdlib.h>

//链表实现双端队列

#define maxn 100005
#define Datatype int

struct QueueNode;
struct QueueNode{
    Datatype data;
    struct QueueNode *pre, *next;
};

struct Queue{
    struct QueueNode *head, *tail;
    int size;
};

struct QueueNode* QueueNodeCreate(Datatype dt)
{
    struct QueueNode *vtx = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    vtx->data = dt;
    vtx->pre = vtx->next = NULL;
    return vtx;
}

void QueueClear(struct Queue*que)
{
    que->head = que->tail = NULL;
}

//插入，可以尾插可以头插，用isFrontOrRear决定，1为头插，0为尾插
void _QueueEn(struct Queue *que,Datatype dt,int isFrontOrRear)
{
    struct QueueNode *vtx = QueueNodeCreate(dt);
    if(isFrontOrRear)
    {
        vtx->next = que->head;//注意等号左边是对变量自身所在的地址进行操作
        que->head->pre = vtx;//等号右边则是取变量地址上保存的值
        que->head = vtx;
    }else{
        vtx->pre = que->tail;
        que->tail->next = vtx;
        que->tail = vtx;
    }
    ++que->size;
}

//删除，可以删除尾部可以删除头部，用isFrontOrRear决定，1为删除头部，0为删除尾部
void _QueueDel(struct Queue *que,struct QueueNode *tmp,int isFrontOrRear)
{
    if(que->size==1)
    {
        que->head = que->tail = NULL;
    }
    if(isFrontOrRear)
    {
        que->head = tmp->next;
        que->head->pre = NULL;
    }else{
        que->tail = tmp->pre;
        que->tail->next = NULL;
    }
    --que->size;
}

//头插
void QueueFrontEn(struct Queue *que,Datatype dt)
{
    _QueueEn(que, dt, 1);
}

void QueueRearEn(struct Queue *que,Datatype dt)
{
    _QueueEn(que, dt, 0);
}

//删除头部数据
void QueueFrontDel(struct Queue *que)
{
    _QueueDel(que, que->head, 1);
}

void QueueRearDel(struct Queue *que)
{
    _QueueDel(que, que->tail, 0);
}

int QueueGetSize(struct Queue*que)
{
    return que->size;
}

//获取头部数据
Datatype QueueGetFront(struct Queue *que)
{
    return que->head->data;
}

Datatype QueueGetRear(struct Queue *que)
{
    return que->tail->data;
}