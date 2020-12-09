//
//  main.cpp
//  3-2
//
//  Created by 林昊晗 on 11/19/19.
//  Copyright © 2019 林昊晗. All rights reserved.
//

#include <iostream>
#include <algorithm>

using namespace std;
#define Maxtree 10

typedef int Tree;
struct Node {
    Tree Left;
    Tree Right;
}T[Maxtree];

struct LevelNode {
    int root;
    int level;
}SortedLeaf[Maxtree];

Tree BuildTree();
void PrintLeaf(Tree root, int level);
bool Cmpare(const struct LevelNode &node1, const struct LevelNode &node2);


int main(int argc, const char * argv[]) {
    Tree root;
    int level = 0;
    root = BuildTree();
    PrintLeaf(root, level);
    
    for(int i=0;i<Maxtree;i++) cout << SortedLeaf[i].level << SortedLeaf[i].root << " ";
    sort(SortedLeaf, SortedLeaf+Maxtree, Cmpare);
    for(int i=0;i<Maxtree;i++) cout << SortedLeaf[i].level << SortedLeaf[i].root << " ";
    for(int i=0;i<Maxtree;i++){
        if (SortedLeaf[i].root && i!=(Maxtree-1)) cout << SortedLeaf[i].root << " ";
        if (i==(Maxtree-1)) cout << SortedLeaf[i].root;
    }
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

void PrintLeaf(Tree root, int level){
    level+=1;
    if (T[root].Left >= 0) PrintLeaf(T[root].Left, level);
    if (T[root].Right >= 0) PrintLeaf(T[root].Right, level);
    if ((T[root].Left < 0) && (T[root].Right < 0))
    {
        SortedLeaf[root].root = root;
        SortedLeaf[root].level = level;
        cout << level << root << endl;
    }
}

bool Cmpare(const struct LevelNode &node1, const struct LevelNode &node2)
{
     return node1.level <= node2.level;
}


/*10
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

/*8
- -
- -
- -
0 -
3 -
4 6
1 7
2 -*/
