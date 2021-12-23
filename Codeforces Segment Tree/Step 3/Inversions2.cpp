/*
Problem Link:   https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/B
Author:         Lê Hữu Trung
Instructor:     Ph.D. Vũ Đức Minh
*/

#include<bits/stdc++.h>
using namespace std;

int getMid(int start, int end){
    return start + (end - start)/2;
}

void constructSTUntil(vector<int> &st, vector<int> &arr, int start, int end, int current){
    if(start == end){
        st[current] = arr[start];
        return;
    }

    int mid = getMid(start, end);

    constructSTUntil(st, arr, start, mid, current*2 + 1);
    constructSTUntil(st, arr, mid + 1, end, current*2 + 2);

    st[current] = st[current*2 + 1] + st[current*2 + 2];
}

vector<int> constructST(vector<int> &arr, int n){
    int height = (int)ceil(log2(n));
    int max_size = 2*pow(2, height) - 1;
    vector<int> st(max_size);
    constructSTUntil(st, arr, 0, n - 1, 0);
    return st;
}

int getKthUntil(vector<int> &st, int start, int end, int current, int k){
    if(start == end){
        return start;
    }

    int mid = getMid(start, end);

    if(k < st[current*2 + 1]){
        return getKthUntil(st, start, mid, current*2 + 1, k);
    }else{
        return getKthUntil(st, mid + 1, end, current*2 + 2, k - st[current*2 + 1]);
    }
}

int getKth(vector<int> &st, int k, int n){
    return getKthUntil(st, 0, n - 1, 0, k);
}

void updateValueUntil(vector<int> &st, int start, int end, int position, int current){
    if(start == end){
        st[current] = 1 - st[current];
        return;
    }
    
    int mid = getMid(start, end);
    
    if(position <= mid){
        updateValueUntil(st, start, mid, position, current*2 + 1);
    }else{
        updateValueUntil(st, mid + 1, end, position, current*2 + 2);
    }

    st[current] = st[current*2 + 1] + st[current*2 + 2];
}

void updateValue(vector<int> &st, int n, int position){
    updateValueUntil(st, 0, n - 1, position, 0);
}

int main(){
    int n;
    cin >> n;

    int A[n];
    for(int i = 0; i < n; i++){
        cin >> A[i];
    }

    vector<int> B(n, 1);
    vector<int> st = constructST(B, n);

    for(int i = n - 1; i >= 0; i--){
        B[i] = getKth(st, i - A[i], n);
        updateValue(st, n, B[i]);
    }

    for(int i : B){
        cout << i + 1 << " ";
    }
}