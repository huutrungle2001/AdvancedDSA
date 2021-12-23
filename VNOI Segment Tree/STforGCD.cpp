/*
Accepted.
Problem Link: https://oj.vnoi.info/problem/olp_kc19_seq
Solved: Lê Hữu Trung
Instructor: Ph.D. Vũ Đức Minh
Note: Change int to long long to get Accepted
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

    st[current] = __gcd(st[current*2 + 1], st[current*2 + 2]);
}

int *constructST(int arr[], int n){
    int height = (int)ceil(log2(n));
    int max_size = 2*(int)pow(2, height) - 1;
    int *st = new int[max_size];
    constructSTUntil(st, arr, 0, n - 1, 0);
    return st;
}

int getGCDUntil(int *st, int start, int end, int l, int r, int current){
    if(l <= start && r >= end){
        return st[current];
    }

    int mid = getMid(start, end);

    // Điều hướng đệ quy để giảm số phép tính, hoặc cứ return 0 ở đoạn nằm ngoài [l,r] cũng được
    // TH1: mid + 1 > r ==> Đệ quy bên trái
    if(mid + 1 > r){
        return getGCDUntil(st, start, mid, l, r, current*2 + 1);
    }
    // TH2: mid < l ==> Đệ quy bên phải
    if(mid < l){
        return getGCDUntil(st, mid + 1, end, l, r, current*2 + 2);
    }

    return __gcd(getGCDUntil(st, start, mid, l, r, current*2 + 1), getGCDUntil(st, mid + 1, end, l, r, current*2 + 2));
}

int getGCD(int *st, int n, int l, int r){
    return getGCDUntil(st, 0, n - 1, l, r, 0);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        arr[i] = abs(arr[i] - temp);
    }

    int *st = constructST(arr, n);
    for(int i = 0; i < k; i++){
        int l, r;
        cin >> l >> r;
        cout << getGCD(st, n, l - 1, r - 1) << endl;
    }
}



// 1 3 10 8 6 9 4 2
// 10 15 2 9 6 4 2 7

// n = 8
// 9 12 8 1 0 5 2 5 
//                             1[0,7]
//                   /                         \  
//             1[0,3]                          1[4,7]
//         /           \                   /           \
//     3[0,1]         1[2,3]          5[4,5]         1[6,7]
//    /    \           /  \           /  \            / \
// 9[0,0] 12[1,1]  8[2,2] 1[3,3]  0[4,4] 5[5,5]  2[6,6] 5[7,7]