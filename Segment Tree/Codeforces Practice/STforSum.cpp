#include<bits/stdc++.h>
using namespace std;

long long getMid(long long start, long long end){
    return start + (end - start)/2;
}

long long constructSTUntil(long long arr[], long long start, long long end, long long *st, long long current){
    if(start == end){
        st[current] = arr[start];
        return arr[start];
    }

    long long mid = getMid(start, end);
    
    st[current] = constructSTUntil(arr, start, mid, st, current*2 + 1) 
                + constructSTUntil(arr, mid + 1, end, st, current*2 + 2);
    return st[current];
}

long long *constructST(long long arr[], long long n){
    long long x = (long long)(ceil(log2(n)));
    long long max_size = 2*(long long)pow(2, x) - 1;
    long long *st = new long long[max_size];
    constructSTUntil(arr, 0, n - 1, st, 0);
    return st;
}

long long getSumUntil(long long *st, long long start, long long end, long long l, long long r, long long current){
    if(l <= start && r >= end){
        return st[current];
    }

    if(r < start || l > end){
        return 0;
    }

    long long mid = getMid(start, end);
    return getSumUntil(st, start, mid, l, r, current*2 + 1) + getSumUntil(st, mid + 1, end, l, r, current*2 + 2);
}

long long getSum(long long *st, long long n, long long l, long long r){
    return (l < 0 || r > n - 1 || l > r) ? -1 : getSumUntil(st, 0, n - 1, l, r, 0);
}

void updateValueUntil(long long *st, long long start, long long end, long long i, long long diff, long long current){
    if(i < start || i > end){
        return;
    }
    st[current] += diff;

    if(start != end) {
        long long mid = getMid(start, end);
        updateValueUntil(st, start, mid, i, diff, current*2 + 1);
        updateValueUntil(st, mid + 1, end, i, diff, current*2 + 2);
    }
}

void updateValue(long long arr[], long long *st, long long n, long long i, long long value){
    if(i < 0 || i > n) {
        return;
    }

    long long diff = value - arr[i];
    arr[i] = value;

    updateValueUntil(st, 0, n - 1, i, diff, 0);
}


int main(){
    long long n, m, option, index, value, left, right;
    cin >> n >> m;
    long long arr[n];
    for(long long i = 0; i < n; i++){
        cin >> arr[i];
    }

    long long *st = constructST(arr, n);

    for(long long i = 0; i < m; i++){
        cin >> option;
        switch(option){
            case 1: 
                cin >> index >> value;
                updateValue(arr, st, n, index, value);
                break;
            case 2: 
                cin >> left >> right;
                cout << getSum(st, n, left, right - left - 1) << endl;
                break;
        }
    }
}