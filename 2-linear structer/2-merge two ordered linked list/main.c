//
//  main.c
//  2-1
//
//  Created by 林昊晗 on 10/20/19.
//  Copyright © 2019 林昊晗. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */
List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read(){
    int N;
    List L, head;
    //List temp;
    head = (List)malloc(sizeof(struct Node));
    L = head;
    scanf("%d", &N);
    while (N) {
        L->Next = (List)malloc(sizeof(struct Node));
        L = L->Next;
        scanf("%d", &L->Data);
        N--;
    }
    L->Next = NULL;
    //temp = head;
    //head = head->Next;
    //free(temp);
    return head;
}

void Print( List L ){
    L = L->Next;
    if (!L) printf("%d    ", 99999);
    while (L) {
        printf("%d ", L->Data);
        L = L->Next;
    }
}


List Merge( List L1, List L2 ){
    List L, head, tempL1, tempL2;
    L = head = (List)malloc(sizeof(struct Node));
    tempL1 = L1->Next;
    tempL2 = L2->Next;
    
    while (tempL1 && tempL2) {
        L->Next = (List)malloc(sizeof(struct Node));
        L = L->Next;
        
        if (tempL1->Data > tempL2->Data){
            L->Data = tempL2->Data;
            tempL2 = tempL2->Next;
        }
        
        else if (tempL1->Data == tempL2->Data){
            int a = tempL2->Data;
            L->Data = a;
            L->Next = (List)malloc(sizeof(struct Node));
            L = L->Next;
            L->Data = a;
            tempL2 = tempL2->Next;
            tempL1 = tempL1->Next;
        }
        
        else{
            L->Data = tempL1->Data;
            tempL1 = tempL1->Next;
        }
    }
    if (tempL1) L->Next = tempL1;
    if (tempL2) L->Next = tempL2;
    L1->Next = NULL;
    L2->Next = NULL;
    

    return head;
}
