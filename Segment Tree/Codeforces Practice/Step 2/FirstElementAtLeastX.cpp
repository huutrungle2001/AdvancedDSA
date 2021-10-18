/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/C
Author: Lê Hữu Trung
Supervisor: Dr. Vũ Đức Minh
*/

#include<bits/stdc++.h>
using namespace std;

int getMid(int start, int end){
    return start + (end - start) / 2;
}

void constructSTUntil(int arr[], int *st, int start, int end, int current){
    if(start == end){
        st[current] = arr[start];
        return;
    }

    int mid = getMid(start, end);

    constructSTUntil(arr, st, start, mid, current*2 + 1);
    constructSTUntil(arr, st, mid + 1, end, current*2 + 2);
    st[current] = max(st[current*2 + 1], st[current*2 + 2]);
}

int *constructST(int arr[], int n){
    int height = (int)ceil(log2(n));
    int max_size = 2*pow(2, height) - 1;
    int *st = new int[max_size];

    constructSTUntil(arr, st, 0, n - 1, 0);
    return st;
}

int firstAtLeastXUntil(int *st, int start, int end, int X, int current){
    if(start == end && st[current] >= X){
        return start;
    }else if(start > end || start == end && st[current] < X){
        return -1;
    }

    int mid = getMid(start, end);

    if(st[current*2 + 1] >= X){
        return firstAtLeastXUntil(st, start, mid, X, current*2 + 1);
    }else{
        return firstAtLeastXUntil(st, mid + 1, end, X, current*2 + 2);
    }
}

int firstAtLeastX(int *st, int n, int X){
    return firstAtLeastXUntil(st, 0, n - 1, X, 0);
}

void updateValueUntil(int *st, int start, int end, int position, int value, int current){
    if(position < start || position > end){
        return;
    }

    if(start == end){
        st[current] = value;
        return;
    }

    int mid = getMid(start, end);
    updateValueUntil(st, start, mid, position, value, current*2 + 1);
    updateValueUntil(st, mid + 1, end, position, value, current*2 + 2);
    st[current] = max(st[current*2 + 1], st[current*2 + 2]);
}

void updateValue(int *st, int n, int position, int value){
    updateValueUntil(st, 0, n - 1, position, value, 0);
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
            updateValue(st, n, position, value);
        }else{
            int X;
            cin >> X;
            cout << firstAtLeastX(st, n, X) << "\n";
        }
    }
}