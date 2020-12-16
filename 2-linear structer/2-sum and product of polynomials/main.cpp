//
//  main.cpp
//  2-2
//
//  Created by Haohan Lin on 10/26/19.
//  Copyright © 2019 Haohan Lin. All rights reserved.
//

#include <iostream>

typedef int ElementType;
typedef struct PolyNode *NodePtr;

struct PolyNode {
    ElementType coef;
    ElementType exp;
    NodePtr NextNode;
};

typedef NodePtr PolyList;

PolyList Read();
void Attach(PolyList *L, int coef, int exp);
PolyList Add(PolyList L1, PolyList L2);
PolyList Multiply(PolyList L1, PolyList L2);
void PrintPoly(PolyList L1);

int main()
{
    PolyList L1, L2;
    PolyList sum, multi;
    
    L1 = Read();
    L2 = Read();
    sum = Add(L1, L2);
    multi = Multiply(L1, L2);
    PrintPoly(multi);
    std::cout << "\n";
    PrintPoly(sum);
    
    
    return 0;
}

PolyList Read(){
    int coef, exp;
    PolyList L, head;
    head = (PolyList)malloc(sizeof(struct PolyNode));
    L = head;
    L->NextNode = NULL;
    
    int N;
    std::cin >> N;
    
    while (N) {
        std::cin >> coef;
        std::cin >> exp;
        Attach(&L,coef,exp);
        N--;
    }
    
    return head;
}

void Attach(PolyList *L, int coef, int exp){
    PolyList P = (PolyList)malloc(sizeof(struct PolyNode));
    P->coef = coef;
    P->exp = exp;
    P->NextNode = NULL;
    
    (*L)->NextNode = P;
    *L = (*L)->NextNode;
}

PolyList Add(PolyList L1, PolyList L2){
    PolyList sum, head;
    int sumCoef;
    head = (PolyList)malloc(sizeof(struct PolyNode));
    sum = head;
    sum->NextNode = NULL;
    L1 = L1->NextNode;
    L2 = L2->NextNode;
    
    if (!L1 && !L2){
        Attach(&sum, 0, 0);
        return head;
    }
    
    while (L1 && L2) {
        if (L1->exp == L2->exp) {
            sumCoef = L1->coef + L2->coef;
            if (sumCoef) Attach(&sum, sumCoef, L1->exp);
            L1 = L1->NextNode;
            L2 = L2->NextNode;
        }
        else if (L1->exp > L2->exp) {
            Attach(&sum, L1->coef, L1->exp);
            L1 = L1->NextNode;
        }
        else {
            Attach(&sum, L2->coef, L2->exp);
            L2 = L2->NextNode;
        }
    }
    
    if (L1) {
        sum->NextNode = L1;
    }
    if (L2) {
        sum->NextNode = L2;
    }
    
    return head;
}

PolyList Multiply(PolyList L1, PolyList L2){
    int coef, exp;
    PolyList multi, headAdd, head2, addList;
    multi = (PolyList)malloc(sizeof(struct PolyNode));
    head2 = L2;
    multi->NextNode = NULL;
    L1 = L1->NextNode;
    L2 = L2->NextNode;
    
    while (L1) {
        headAdd = (PolyList)malloc(sizeof(struct PolyNode));
        addList = headAdd;
        addList->NextNode = NULL;
        
        while (L2) {
            coef = L1->coef * L2->coef;
            exp = L1->exp + L2->exp;
            Attach(&addList, coef, exp);
            L2 = L2->NextNode;
        }
        multi = Add(multi, headAdd);
        L1 = L1->NextNode;
        L2 = head2;
        L2 = L2->NextNode;
    }
    
    return multi;
}

void PrintPoly(PolyList L1){
    
    L1 = L1->NextNode;
    if (!L1) std::cout << 0 << " " << 0;
    while (L1) {
        std::cout << L1->coef << " ";
        
        if (L1->NextNode == NULL) std::cout << L1->exp;
        else std::cout << L1->exp << " ";
        
        L1 = L1->NextNode;
    }
}
