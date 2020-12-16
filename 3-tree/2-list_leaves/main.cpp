//
//  main.cpp
//  3-2
//
//  Created by Haohan Lin on 11/19/19.
//  Copyright © 2019 Haohan Lin. All rights reserved.
//

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define Maxtree 10

typedef int Tree;
struct Node {
    int idx;
    Tree Left;
    Tree Right;
}T[Maxtree];


Tree BuildTree();
void PrintLeaf(Tree root);

int main(int argc, const char * argv[]) {
    Tree root;
    int level = 0;
    root = BuildTree();
    PrintLeaf(root);
    
    return 0;
}

Tree BuildTree(){
    int N, i=0;
    cin >> N;
    char left, right;
    Tree root;
    int check[N];
    for(i = 0;i<N;i++) check[i] = 1;
    
    for(i = 0;i<N;i++){
        cin >> left >> right;
        T[i].idx = i;
        T[i].Left = left-'0';
        T[i].Right = right-'0';
        if (T[i].Left) check[T[i].Left]=0;
        if (T[i].Right) check[T[i].Right]=0;
    }
    for(i = 0;i<N;i++){
        if (check[i]) root = i;
    }
    return root;
}

void PrintLeaf(Tree root){
    queue<Node> treeQ;
    treeQ.push(T[root]);
    while (!treeQ.empty())
    {
        Node firstItem = treeQ.front();
        treeQ.pop();

        if (firstItem.Left >= 0) treeQ.push(T[firstItem.Left]);
        if (firstItem.Right >= 0) treeQ.push(T[firstItem.Right]);
        if ((firstItem.Left < 0) && (firstItem.Right < 0))
        {
            if (treeQ.empty())cout << firstItem.idx;
            else cout << firstItem.idx << ' ';
        }
    }
    
}


/*
Input:
10
1 2
3 -
4 5
6 -
- -
- 7
- -
- 8
- 9
- -*/

/*Output:
4 1 5
*/
