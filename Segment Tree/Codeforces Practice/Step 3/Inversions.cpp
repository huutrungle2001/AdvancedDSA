/**
    Problem Link: https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A
    Author: Lê Hữu Trung
    Instructor: Ph.D. Vũ Đức Minh
**/

#include<bits/stdc++.h> 
#define inf 1000000
using namespace std;

// Inititate an empty Segment Tree
int st[inf];
 
int getMid(int start, int end){
    return start + (end - start)/2;
}
 
int getSumUntil(int *st, int start, int end, int current, int l, int r){
    if(l <= start && r >= end){
        return st[current];
    }
 
    if(start > end || l > r || l > end || r < start){
        return 0;
    }
 
    int mid = getMid(start, end);
 
    return getSumUntil(st, start, mid, current*2 + 1, l, r) + getSumUntil(st, mid + 1, end, current*2 + 2, l, r);
}
 
int getSum(int *st, int n, int l, int r){
    return getSumUntil(st, 0, n - 1, 0, l, r);
}
 
void updateValueUntil(int *st, int start, int end, int current, int position, int value){
    if(position < start || position > end){
        return;
    }
 
    if(start == end){
        st[current] = value;
        return;
    }
 
    int mid = getMid(start, end);
 
    updateValueUntil(st, start, mid, current*2 + 1, position, value);
    updateValueUntil(st, mid + 1, end, current*2 + 2, position, value);
 
    st[current] = st[current*2 + 1] + st[current*2 + 2];
}
 
void updateValue(int *st, int n, int position, int value){
    updateValueUntil(st, 0, n - 1, 0, position, value);
}


 
int main() {
    int n;
    cin >> n;
    
    // A: inputted array
    int A[n];
    // B: output array, initiated with 0
    int B[n];

    for(int i = 0; i < n; i++){
        cin >> A[i];
    }
 
    for(int i = 0; i < n; i++){
        // For each element visitted in A, update the corresponding leaf in the ST to 1.
        // Elements in A vary from 1 to n, position start from 0 to n - 1. 
        // Therefore, the leaf need updating is at position A[i] - 1. 
        updateValue(st, n, A[i] - 1, 1);
        
        // The sum on the segment [A[i], n] is the number of elements larger than A[i].
        B[i] = getSum(st, n, A[i], n);
    }
 
    for(int i : B){
        cout << i << " ";
    }
    cout << "\n";
}