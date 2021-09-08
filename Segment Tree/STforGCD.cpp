/*
Accepted.
Problem Link: https://oj.vnoi.info/problem/olp_kc19_seq
Solved: Lê Hữu Trung
Supervisor: Dr. Vũ Đức Minh
Note: Change int to long long to get Accepted
*/

#include<bits/stdc++.h>
using namespace std;

int getMid(int start, int end){
    return start + (end - start)/2;
}

int constructSTUntil(int *st, int arr[], int start, int end, int current){
    if(start == end){
        st[current] = arr[start];
        return arr[start];
    }

    int mid = getMid(start, end);

    st[current] = __gcd(constructSTUntil(st, arr, start, mid, current*2 + 1), constructSTUntil(st, arr, mid + 1, end, current*2 + 2));
    return st[current];
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

    // Khi đệ quy đến đoạn nằm ngoài [l,r] thì phải dừng 
    // Để dừng hàm phải return 1 giá trị cùng kiểu hàm
    // Tuy nhiên rất khó để tìm được giá trị phù hợp để return và dừng đệ quy ở đoạn ngoài [l,r]
    // Cụ thể thì giá trị này phải thỏa mãn điều kiện là không làm ảnh hưởng đến kết quả khi truyền vào hàm __gcd
    // Giá trị này phải chính xác bằng giá trị cần tìm (gcd(a,a) = a, vô lý vì chưa tìm được giá trị cần tìm)
    // Vậy nên không có cách nào để dừng đệ quy ở đoạn nằm ngoài [l,r] mà không ảnh hưởng đến kq
    // ==> Phải điều hướng đệ quy, chỉ đệ quy trong đoạn [l,r]
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
