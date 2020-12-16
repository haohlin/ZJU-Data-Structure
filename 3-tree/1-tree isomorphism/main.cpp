//
//  main.cpp
//  3-1
//
//  Created by Haohan Lin on 10/28/19.
//  Copyright © 2019 Haohan Lin. All rights reserved.
//

#include <iostream>
#include <string>

#define MaxTree 10
#define Null -3
typedef int Tree;
typedef char ElementType;

struct TreeNode {
    ElementType Data;
    Tree Left;
    Tree Right;
}T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[]);
int IsOmorphic(Tree R1, Tree R2);


int main(int argc, const char * argv[]) {
    Tree R1, R2;
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    
    if (IsOmorphic(R1, R2)) std::cout << "Yes";
    else std::cout<<"No";
    return 0;
}

Tree BuildTree(struct TreeNode T[]){
    int N, root=0;
    char Left, Right;
    std::cin >> N;
    if (!N) return Null;
    int check[N];
    
    for (int i = 0;i<N;i++) check[i] = 0;
    for (int i = 0;i < N;i++){
        std::cin >> T[i].Data >> Left >> Right;
        T[i].Left = Left-'0';
        T[i].Right = Right-'0';
        if (T[i].Left) check[T[i].Left] = 1;
        if (T[i].Right) check[T[i].Right] = 1;
    }
    for (int i = 0;i<N;i++){
        if (!check[i]) root = i;
    }
    
    return root;
}
int IsOmorphic(Tree R1, Tree R2){
    if ((R1==Null) && (R2==Null)) return 1;
    else if (((R1!=Null) && (R2==Null)) || ((R1==Null) && (R2!=Null))) return 0;
    else if (T1[R1].Data!=T2[R2].Data) return 0;
    else if ((T1[R1].Left==Null) && (T2[R2].Left==Null))
        return IsOmorphic(T1[R1].Right, T2[R2].Right);
    else if ((T1[R1].Left!=Null) && (T2[R2].Left!=Null) && (T1[T1[R1].Left].Data==T2[T2[R2].Left].Data))
        return (IsOmorphic(T1[R1].Left, T2[R2].Left) && IsOmorphic(T1[R1].Right, T2[R2].Right));
    else return (IsOmorphic(T1[R1].Left, T2[R2].Right) && IsOmorphic(T1[R1].Right, T2[R2].Left));
}

