//
//  main.cpp
//  5-1_堆中的路径
//
//  Created by 林昊晗 on 4/26/20.
//  Copyright © 2020 林昊晗. All rights reserved.
//

#include <iostream>

//#define MaxSize 1001
#define MinData -10001

typedef int ElementType;

typedef struct {
    ElementType *heapArray;
    int heapSize;
    int minData;
} MinHeap;

typedef MinHeap * HeapPtr;

HeapPtr CreateHeap(int heapSize);
void insertHeap(HeapPtr heap);
void printPath(HeapPtr heap);

int main(int argc, const char * argv[]) {
    int heapSize, numPath;

    std::cin >> heapSize >> numPath;
    HeapPtr MinHeapPtr = CreateHeap(heapSize);
    for(int i = 1; i < heapSize + 1; i++){
        insertHeap(MinHeapPtr);
    }
    for(int i = 0; i < numPath; i++){
        printPath(MinHeapPtr);
    }
    return 0;
}

HeapPtr CreateHeap(int heapSize){
    HeapPtr MinHeapPtr = (HeapPtr)malloc(sizeof(MinHeap));

    MinHeapPtr->heapSize = 0;
    MinHeapPtr->minData = MinData;

    MinHeapPtr->heapArray = (ElementType *)malloc((heapSize+1)*sizeof(ElementType));
    MinHeapPtr->heapArray[0] = MinData;
    return MinHeapPtr;
}

void insertHeap(HeapPtr heap){
    int data;
    std::cin >> data;

    
    int i = ++heap->heapSize;
    for(; heap->heapArray[i/2] > data; i/=2){
        heap->heapArray[i] = heap->heapArray[i/2];
    }
    heap->heapArray[i] = data;
}

void printPath(HeapPtr heap){
    int idx;
    std::cin >> idx;

    //printf("%d  \n", heap->heapArray[idx]);
    //std::cout << heap->heapArray[idx] << " ";
    while (heap->heapArray[idx/2] != MinData)
    {
        std::cout << heap->heapArray[idx] << " ";
        idx/=2;
    } 
    std::cout << heap->heapArray[idx] << std::endl;
}