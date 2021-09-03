/*
Problem link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B

Sovled by: Le Huu Trung
Guided by: Dr. Vu Duc Minh
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

    st[current] = min(constructSTUntil(arr, start, mid, st, current*2 + 1), constructSTUntil(arr, mid + 1, end, st, current*2 + 2));
    return st[current];
}

int *constructST(int arr[], int n){
    int x = (int)ceil(log2(n));
    int max_size = 2*(int)pow(2, x) - 1;
    int *st = new int[max_size];
    constructSTUntil(arr, 0, n - 1, st, 0);
    return st;
}

int getMinUntil(int *st, int start, int end, int l, int r, int current){
    if(l <= start && end <= r){
        return st[current];
    }

    if(r < start || l > end){
        return INT_MAX;
    }

    int mid = getMid(start, end);

    return min(getMinUntil(st, start, mid, l, r, current*2 + 1), getMinUntil(st, mid + 1, end, l, r, current*2 + 2));
}

int getMin(int *st, int n, int l, int r){
    return (l < 0 || r > n - 1 || l > r) ? -1 : getMinUntil(st, 0, n - 1, l, r, 0);
}

void updateValue(int arr[], int* st, int start, int end, int index, int value, int current){
    if (index < start || index > end){
        return;
    }
    
    if (start == end){  
        arr[index] = value;
        st[current] = value;
    }
    else {
        int mid = getMid(start, end);
        if (index >= start && index <= mid)
            updateValue(arr, st, start, mid, index, value, 2*current + 1);
        else
            updateValue(arr, st, mid + 1, end, index, value, 2*current + 2);
        st[current] = min(st[2*current + 1], st[2*current + 2]);
    }
    return;
}

int main(){
    int n = 6;
    int arr[] = {1, 3, 5, 7, 9, 11};
    int *st = constructST(arr, n);

    cout << "Minimum value in [0:3] = " << getMin(st, n, 0, 3) << endl;

    updateValue(arr, st, 0, n - 1, 0, 8, 0);
    cout << "Minimum value in [0:3] after updating = " << getMin(st, n, 0, 3) << endl;
    return 0;
}    