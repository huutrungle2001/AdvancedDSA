/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A
Author: Lê Hữu Trung
Supervisor: Dr. Vũ Đức Minh
*/

#include<bits/stdc++.h>
using namespace std;

int getMid(int start, int end){
    return start + (end - start)/2;
}

int constructSTUntil(int arr[], int start, int end, int *st, int current){
    if(start == end){
        st[current] = arr[start];
        return arr[start];
    }

    int mid = getMid(start, end);
    
    st[current] = constructSTUntil(arr, start, mid, st, current*2 + 1) 
                + constructSTUntil(arr, mid + 1, end, st, current*2 + 2);
    return st[current];
}

int *constructST(int arr[], int n){
    int x = (int)(ceil(log2(n)));
    int max_size = 2*(int)pow(2, x) - 1;
    int *st = new int[max_size];
    constructSTUntil(arr, 0, n - 1, st, 0);
    return st;
}

int getSumUntil(int *st, int start, int end, int l, int r, int current){
    if(l <= start && r >= end){
        return st[current];
    }

    if(r < start || l > end){
        return 0;
    }

    int mid = getMid(start, end);
    return getSumUntil(st, start, mid, l, r, current*2 + 1) + getSumUntil(st, mid + 1, end, l, r, current*2 + 2);
}

int getSum(int *st, int n, int l, int r){
    return (l < 0 || r > n - 1 || l > r) ? -1 : getSumUntil(st, 0, n - 1, l, r, 0);
}

void updateValueUntil(int *st, int start, int end, int i, int diff, int current){
    if(i < start || i > end){
        return;
    }
    st[current] += diff;

    if(start != end) {
        int mid = getMid(start, end);
        updateValueUntil(st, start, mid, i, diff, current*2 + 1);
        updateValueUntil(st, mid + 1, end, i, diff, current*2 + 2);
    }
}

void updateValue(int arr[], int *st, int n, int i, int value){
    if(i < 0 || i > n) {
        return;
    }

    int diff = value - arr[i];
    arr[i] = value;

    updateValueUntil(st, 0, n - 1, i, diff, 0);
}


int main(){
    int n, m, option, index, value, left, right;
    cin >> n >> m;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int *st = constructST(arr, n);

    for(int i = 0; i < m; i++){
        cin >> option;
        switch(option){ 
            case 1: 
                cin >> index >> value;
                updateValue(arr, st, n, index, value);
                break;
            case 2: 
                cin >> left >> right;
                cout << getSum(st, n, left, right - 1) << endl;
                break;
        }
    }
}