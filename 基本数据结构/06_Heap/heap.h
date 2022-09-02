#ifndef _HEAP_H
#define _HEAP_H

typedef struct{
    int val;
    int times;
} DataType;

typedef struct{
    DataType *data;
    int size;
    int capacity;
} Heap;

int compareData(DataType *a, DataType *b);

void swap(DataType *a, DataType *b);

void heapShiftDown(Heap *heap, int curr);

void heapShiftUp(Heap *heap, int curr);

bool heapIsFull(Heap *heap);

bool heapIsEmpety(Heap *heap);

bool HeapPush(Heap *heap, DataType dt);

bool HeapPop(Heap *heap);

Heap *HeapCreate(DataType *d, int arrSize, int maxSize);

DataType HeapTop(Heap *heap);

void HeapFree(Heap *heap);

#endif