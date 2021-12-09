/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/D
Author: Lê Hữu Trung
Instructor: Dr. Vũ Đức Minh
*/

#include<bits/stdc++.h>
using namespace std;

int getMid(int start, int end){
    return start + (end - start)/2;
}

void constructSTUntil(int *st, int arr[], int start, int end, int current){
    if(start == end){
        st[current] = arr[start];
        return;
    }

    int mid = getMid(start, end);

    constructSTUntil(st, arr, start, mid, current*2 + 1);
    constructSTUntil(st, arr, mid + 1, end, current*2 + 2);
    st[current] = max(st[current*2 + 1], st[current*2 + 2]);
}

int *constructST(int arr[], int n){
    int height = (int)ceil(log2(n));
    int max_size = 2*pow(2, height) - 1;
    int *st = new int[max_size];

    constructSTUntil(st, arr, 0, n - 1, 0);
    return st;
}

int firstAtLeastXFromLUntil(int *st, int start, int end, int current, int X, int L){
    if(st[current] < X || end < L){
        return -1;
    }
    if(start == end){
        return start;
    }

    int mid = getMid(start, end);

    int answer = firstAtLeastXFromLUntil(st, start, mid, current*2 + 1, X, L);
    if(answer == -1){
        answer = firstAtLeastXFromLUntil(st, mid + 1, end, current*2 + 2, X, L);
    }

    return answer;
}

int firstAtLeastXFromL(int *st, int n, int L, int X){
    return firstAtLeastXFromLUntil(st, 0, n - 1, 0, X, L);
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
    st[current] = max(st[current*2 + 1], st[current*2 + 2]);
}

void updateValue(int *st, int n, int position, int value){
    updateValueUntil(st, 0, n - 1, 0, position, value);
}

int main(){
    int n, m;
    cin >> n >> m;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int *st = constructST(arr, n);

    for(int i = 0; i < m; i++){
        int op;
        cin >> op;
        if(op == 1){
            int position, value;
            cin >> position >> value;
            updateValue(st, n , position, value);
        }else{
            int X, L;
            cin >> X >> L;
            cout << firstAtLeastXFromL(st, n, L, X) << "\n";
        }
    }   
}