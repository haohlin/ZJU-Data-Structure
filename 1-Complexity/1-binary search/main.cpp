//
//  main.cpp
//  1-3
//
//  Created by Haohan Lin on 9/22/19.
//  Copyright © 2019 Haohan Lin. All rights reserved.
//

#include <iostream>

using namespace std;

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;

struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}



Position BinarySearch( List L, ElementType X ){
    Position start = 1;
    Position end = L->Last;
    
    while (start <= end) {
        Position center = (start + end) / 2;
        if (L->Data[center] == X) {
            return center;
        }else if (L->Data[center] < X){
            start = center + 1;
        }else if (L->Data[center] > X){
            end = center - 1;
        }
    }
    return NotFound;
    
}

