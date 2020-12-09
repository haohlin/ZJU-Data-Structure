//
//  main.cpp
//  1-1
//
//  Created by 林昊晗 on 8/16/19.
//  Copyright © 2019 林昊晗. All rights reserved.
//

#include <iostream>

using namespace std;

int Max(int A, int B, int C){
    return A > B ? (A > C ? A : C) : B > C ? B : C;
}


int MaxSeqSum_n2(int List[], int N){
    int MaxSum = List[0], CurrentSum = 0;
    
    for (int i = 0; i < N; i++){
        CurrentSum = 0;
        for(int j = i; j < N; j++){
            CurrentSum += List[j];
            if(CurrentSum > MaxSum) MaxSum = CurrentSum;
        }
    }
    
    return MaxSum;
}


int MaxSeqSum_nlogn(int List[], int start, int end){
    int maxLeft, maxRight, maxCross;
    int center = (start + end) / 2;
    int maxLeftScan = List[center], maxRightScan = List[center + 1], nowSum = 0;
    
    if(start == end) return List[start];
    
    maxLeft = MaxSeqSum_nlogn(List, start, center);
    maxRight = MaxSeqSum_nlogn(List, center + 1, end);
    
    for(int i = center; i >= start; i--){
        nowSum += List[i];
        if(nowSum > maxLeftScan) maxLeftScan = nowSum;
    }
    
    nowSum = 0;
    for(int i = center + 1; i <= end; i++){
        nowSum += List[i];
        if(nowSum > maxRightScan) maxRightScan = nowSum;
    }
    
    maxCross = maxLeftScan + maxRightScan;
    
    return Max(maxCross, maxLeft, maxRight);
}

int MaxSeqSum_nlogn_inter(int List[], int N){
    return MaxSeqSum_nlogn(List, 0, N - 1);
}


int MaxSeqSum_n(int List[], int N){
    int MaxSum = 0, NowSum = 0;

    for(int i = 0; i < N; i++)
    {
        NowSum += List[i];
        if(NowSum > MaxSum)
            MaxSum = NowSum;
        if(NowSum < 0)
            NowSum = 0;
    }
    
    return MaxSum;
}


int main(int argc, const char * argv[]) {
    int N, MaxSeqSum;
    cin >> N;
    int List[N];
    for (int i = 0; i < N; i++){
        cin >> List[i];
    }
    
    //MaxSeqSum = MaxSeqSum_n2(List, N);
    //MaxSeqSum = MaxSeqSum_nlogn_inter(List, N);
    MaxSeqSum = MaxSeqSum_n(List, N);
    
    cout << MaxSeqSum;
    return 0;
}
