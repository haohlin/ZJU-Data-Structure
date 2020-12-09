//
//  main.cpp
//  1-2
//
//  Created by 林昊晗 on 8/16/19.
//  Copyright © 2019 林昊晗. All rights reserved.
//

#include <iostream>
#include <tuple>

using namespace std;

int Max(int A, int B, int C){
    return A > B ? (A > C ? A : C) : B > C ? B : C;
}

tuple<int, int, int> MaxSeqSum_n(int List[], int N){
    int MaxSum = List[0], NowSum = 0;
    int start = 0, end = 0;

    for(int i = N - 1; i >= 0; i--)
    {
        NowSum += List[i];
        if(NowSum >= MaxSum)
        {
            MaxSum = NowSum;
            start = i;
        }
        else if(NowSum < 0)
        {
            NowSum = 0;
            if(i != N - 1) end = i - 1;
        }
        
    }
    
    if (MaxSum < 0)
    {
        MaxSum = 0; //MaxSum can't be negative as long as there is one positive/zero figure.
        end = N-1;
        start = 0;
    }
    
    return make_tuple(MaxSum, List[start], List[end]);
}


int main(int argc, const char * argv[]) {
    int N, MaxSeqSum, start, end;
    cin >> N;
    int List[N];
    for (int i = 0; i < N; i++){
        cin >> List[i];
    }
    
    //MaxSeqSum = MaxSeqSum_n2(List, N);
    //MaxSeqSum = MaxSeqSum_nlogn_inter(List, N);
    tie(MaxSeqSum, start, end) = MaxSeqSum_n(List, N);
    
    cout << MaxSeqSum << ' ' << start << ' ' << end;
    return 0;
}
