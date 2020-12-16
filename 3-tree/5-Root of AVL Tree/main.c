#include <stdio.h>
#include <stdlib.h>

typedef struct Node *AVLTree;

struct Node{
    int data;
    AVLTree right;
    AVLTree left;
    int height;
};

AVLTree NewNode(int data);
AVLTree Insert(AVLTree T, AVLTree newNode);
AVLTree BuildAVLTree(int N);

AVLTree SingleLeft(AVLTree T);
AVLTree SingleRight(AVLTree T);
AVLTree DoubleLeftRight(AVLTree T);
AVLTree DoubleRightLeft(AVLTree T);

int Max( int a, int b );
int GetHeight(AVLTree T);

int main(){
    int N, L;
    AVLTree T;
    scanf("%d", &N);
    T = BuildAVLTree(N);
    printf("%d", T->data);
    return 0;
}

AVLTree BuildAVLTree(int N){
    AVLTree T = NULL, node;
    int data;

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &data);
        node = NewNode(data);
        T = Insert(T, node);
    }
    return T;
}

AVLTree NewNode(int data){
    AVLTree newNode = (AVLTree)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->height = 0;

    return newNode;
}

AVLTree Insert(AVLTree T, AVLTree newNode){
    if (!T) T = newNode;
    else
    {
        if (T->data > newNode->data) {
            T->left = Insert(T->left, newNode);
            if ((GetHeight(T->left) - GetHeight(T->right)) > 1) {
                if (T->left->data > newNode->data) T = SingleLeft(T);
                else T = DoubleLeftRight(T);
            }
        }
        else if (T->data < newNode->data) {
            T->right = Insert(T->right, newNode);
            if ((GetHeight(T->right) - GetHeight(T->left)) > 1) {
                if (T->right->data < newNode->data) T = SingleRight(T);
                else T = DoubleRightLeft(T);
            }
        }
        
    }
    T->height = Max( GetHeight(T->left), GetHeight(T->right) ) + 1;
    return T;
}

int Max(int a, int b){
    return a > b ? a : b;
}

int GetHeight(AVLTree T){
    if (!T) return 0;
    else return T->height;
    
}

AVLTree SingleLeft(AVLTree A){
    /* 注意：A必须有一个左子结点B */
  /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */     

    AVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    A->height = Max( GetHeight(A->left), GetHeight(A->right) ) + 1;
    B->height = Max( GetHeight(B->left), A->height ) + 1;
 
    return B;
}

AVLTree SingleRight(AVLTree A){
    /* 注意：A必须有一个左子结点B */
  /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */     

    AVLTree B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = Max( GetHeight(A->right), GetHeight(A->left) ) + 1;
    B->height = Max( GetHeight(B->right), A->height ) + 1;
 
    return B;
}

AVLTree DoubleLeftRight(AVLTree A){
    /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */
    
    /* 将B与C做右单旋，C被返回 */
    A->left = SingleRight(A->left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeft(A);
}

AVLTree DoubleRightLeft(AVLTree A){
    /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */
    
    /* 将B与C做右单旋，C被返回 */
    A->right = SingleLeft(A->right);
    /* 将A与C做左单旋，C被返回 */
    return SingleRight(A);
}