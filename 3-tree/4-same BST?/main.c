#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Tree;

typedef struct Node{
    int data;
    Tree right;
    Tree left;
    int visited;
};

Tree NewNode(int data);
Tree Insert(Tree T, Tree newNode);
Tree BuildTree(int N);

int Check(Tree T, int input);
int Judge(Tree T, int N);

void ResetTree(Tree T);
void DelTree(Tree T);

int main(){
    int N, L;
    Tree T;
    scanf("%d", &N);

    while (N)
    {
        scanf("%d", &L);
        T = BuildTree(N);
        for (int i = 0; i < L; i++)
        {
            if (Judge(T, N)) printf("Yes\n");
            else printf("No\n");

            ResetTree(T);
        }
        DelTree(T);
        scanf("%d", &N);
    }
    
    return 0;
}

Tree BuildTree(int N){
    Tree T = NULL, node;
    int data;

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &data);
        node = NewNode(data);
        T = Insert(T, node);
    }
    return T;
}

Tree NewNode(int data){
    Tree newNode = (Tree)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->visited = 0;

    return newNode;
}

Tree Insert(Tree T, Tree newNode){
    if (!T) return newNode;
    else
    {
        if (T->data > newNode->data) T->left = Insert(T->left, newNode);
        else if (T->data < newNode->data) T->right = Insert(T->right, newNode);
        else return 0;
        
    }
    return T;
}

int Check(Tree T, int input){
    if (!T) return 0;
    if (T->visited)
    {
        if (T->data > input) Check(T->left, input);
        else if (T->data < input) Check(T->right, input);
        else return 0;
    }
    else
    {
        if (T->data == input) {
            T->visited = 1;
            return 1;
        }
        else return 0;
    }
}

int Judge(Tree T, int N){
    int input, found = 1;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &input);
        if (found) found = Check(T, input);
    }
    return found;
}

void ResetTree(Tree T){
    if (!T) return;
    else
    {
        T->visited = 0;
        ResetTree(T->left);
        ResetTree(T->right);
    }
}
void DelTree(Tree T){
    if (!T) return;
    else
    {
        DelTree(T->left);
        DelTree(T->right);
        free(T);
    }
}