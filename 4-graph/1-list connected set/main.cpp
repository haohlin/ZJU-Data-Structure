//
//  main.cpp
//  6-1_列出连通集
//
//  Created by Haohan Lin on 5/2/20.
//  Copyright © 2020 Haohan Lin. All rights reserved.
//

#include <iostream>
#include <queue>

typedef struct gNode *gLinkNode;
typedef struct graph *graphPtr;

struct graph {
    int eNum;
    int vNum;
    gLinkNode *nodePtr;
};

struct gNode {
    int idx;
    int weight;
    gLinkNode nextNode;
};

graphPtr initGraph(int eNum, int vNum);
void insertEdge(graphPtr newGraph);
void DFS(graphPtr newGraph, gLinkNode node);
void BFS(graphPtr newGraph, gLinkNode node);

int *visited;

int main(int argc, const char * argv[]) {
    int eNum, vNum;
    graphPtr newGraph;
    std::cin >> vNum >> eNum;
    newGraph = initGraph(eNum, vNum);
    
    for(int i = 0; i < eNum; i++){
        insertEdge(newGraph);
    }
    /*print graph*/
    gLinkNode nodePtr;
    for(int i = 0; i < vNum; i++){
        nodePtr = newGraph->nodePtr[i];
        while (nodePtr != nullptr) {
            std::cout << nodePtr->idx << "    ";
            nodePtr = nodePtr->nextNode;
        }
        std::cout << std::endl;
    }
    
    //find scc
    visited = (int*)malloc(vNum * sizeof(int));
    for(int i = 0; i < vNum; i++) visited[i] = 0;
    for (int i = 0; i < vNum ; i++) {
        if (visited[i] == 0){
            std::cout << "{ ";
            DFS(newGraph, newGraph->nodePtr[i]);
            std::cout << "}" << std::endl;
        }
    }
    
    for(int i = 0; i < vNum; i++) visited[i] = 0;
    for (int i = 0; i < vNum ; i++) {
        if (visited[i] == 0){
            std::cout << "{ ";
            BFS(newGraph, newGraph->nodePtr[i]);
            std::cout << "}" << std::endl;
        }
    }
    
    free(newGraph);
    return 0;
}

graphPtr initGraph(int eNum, int vNum){
    graphPtr newGraph = (graph*)malloc(sizeof(struct graph));
    
    newGraph->eNum = eNum;
    newGraph->vNum = vNum;
    newGraph->nodePtr = (gLinkNode*)malloc(vNum * sizeof(gLinkNode));
    
    for(int i = 0; i < vNum; i++){
        newGraph->nodePtr[i] = (gLinkNode)malloc(sizeof(gNode));//init 2 stage pointer
        newGraph->nodePtr[i]->idx = i;
        newGraph->nodePtr[i]->weight = 0;
        newGraph->nodePtr[i]->nextNode = nullptr;
    }
    
    return newGraph;
}

void insertEdge(graphPtr newGraph){
    int v1, v2;
    
    std::cin >> v1 >> v2;
    
    gLinkNode newNodeV1 = (gLinkNode)malloc(sizeof(gNode));
    gLinkNode newNodeV2 = (gLinkNode)malloc(sizeof(gNode));
    gLinkNode tempPtrv1, tempPtrv2, prePtrV1 = newGraph->nodePtr[v1], prePtrV2 = newGraph->nodePtr[v2];
    
    newNodeV1->idx = v1;
    newNodeV1->weight = 1;
    newNodeV1->nextNode = nullptr;
    newNodeV2->idx = v2;
    newNodeV2->weight = 1;
    newNodeV2->nextNode = nullptr;
    
    //insert sort
    tempPtrv1 = newGraph->nodePtr[v1]->nextNode;
    while (tempPtrv1 != nullptr) {
        if (tempPtrv1->idx <= v2) {
            prePtrV1 = tempPtrv1;
            tempPtrv1 = tempPtrv1->nextNode;
            continue;
        }
        else{
            prePtrV1->nextNode = newNodeV2;
            newNodeV2->nextNode = tempPtrv1;
            break;
        }
    }
    if (tempPtrv1 == nullptr) {
        prePtrV1->nextNode = newNodeV2;
    }
    
    prePtrV2 = newGraph->nodePtr[v2];
    tempPtrv2 = newGraph->nodePtr[v2]->nextNode;
    while (tempPtrv2 != nullptr) {
        if (tempPtrv2->idx <= v1) {
            prePtrV2 = tempPtrv2;
            tempPtrv2 = tempPtrv2->nextNode;
        }
        else{
            prePtrV2->nextNode = newNodeV1;
            newNodeV1->nextNode = tempPtrv2;
            break;
        }
    }
    if (tempPtrv2 == nullptr) {
        prePtrV2->nextNode = newNodeV1;
    }
    
    //no sort insert
    /*tempPtr = newGraph->nodePtr[v1]->nextNode;
    newGraph->nodePtr[v1]->nextNode = newNodeV2;
    newNodeV2->idx = v2;
    newNodeV2->weight = 1;
    newNodeV2->nextNode = tempPtr;
    
    tempPtr = newGraph->nodePtr[v2]->nextNode;
    newGraph->nodePtr[v2]->nextNode = newNodeV1;
    newNodeV1->idx = v1;
    newNodeV1->weight = 1;
    newNodeV1->nextNode = tempPtr;*/
}

void DFS(graphPtr newGraph, gLinkNode node){
    visited[node->idx] = 1;
    std::cout << node->idx << " " ;
    
    while (node != nullptr) {
        if(!visited[node->idx])
            DFS(newGraph, newGraph->nodePtr[node->idx]);
        node = node->nextNode;
    }
}

void BFS(graphPtr newGraph, gLinkNode node){
    std::cout << node->idx << " " ;
    
    std::queue<gLinkNode> Q;
    Q.push(node);
    visited[node->idx] = 1;
    
    while ((int)Q.size() != 0) {
        node = Q.front();
        Q.pop();
        node = newGraph->nodePtr[node->idx];
        while (node != nullptr) {
            if(visited[node->idx] == 0){
                visited[node->idx] = 1;
                std::cout << node->idx << " " ;
                Q.push(node);
            }
            node = node->nextNode;
        }
    }
}
