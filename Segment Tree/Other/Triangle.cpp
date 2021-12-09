/*
Accepted.
Problem Link: https://oj.vnoi.info/problem/olp_kc19_tri
Solved: Lê Hữu Trung
Instructor: Dr. Vũ Đức Minh
Note: Change int to long long to get Accepted
*/

#include<bits/stdc++.h>
using namespace std;

// Mỗi node sẽ chứa 2 thông tin là tổng giá trị của các node và giá trị lớn nhất của node nằm trong đoạn node này quản lý

struct Node{
    long long sum, max_;

    // Khởi tạo từng phần tử cho mảng Node
    void init(){
        cin >> sum;
        max_ = sum;
    }

    // Khởi tạo 1 Node từ nốt khác
    void setLeaf(Node other){
        sum = other.sum;
        max_ = other.max_;
    }

    // Xử lý node cha
    void setInternal(Node left, Node right){
        sum = left.sum + right.sum;
        max_ = max(left.max_, right.max_);
    }
    
    // Phương thức để kiểm tra xem đoạn mà node này quản lý có tạo thành tam giác được không
    bool isTriangle(){
        if(sum > 2*max_){
            return true;
        }
        return false;
    }
};

long long getMid(long long start, long long end){
    return start + (end - start)/2;
}

void constructSTUntil(Node *st, Node arr[], long long start, long long end, long long current){
    if(start == end){
        st[current].setLeaf(arr[start]);
        return;
    }

    long long mid = getMid(start, end);

    constructSTUntil(st, arr, start, mid, current*2 + 1);
    constructSTUntil(st, arr, mid + 1, end, current*2 + 2);
    st[current].setInternal(st[current*2 + 1], st[current*2 + 2]);
}

Node *constructST(Node arr[], long long n){
    long long height = (long long)ceil(log2(n));
    long long max_size = 2*(long long)pow(2, height) - 1;
    Node *st = new Node[max_size];
    constructSTUntil(st, arr, 0, n - 1, 0);
    return st;
}

Node queryUntil(Node *st, long long start, long long end, long long l, long long r, long long current){
    if(l <= start && r >= end){
        return st[current];
    }

    long long mid = getMid(start, end);

    if(mid + 1 > r){
        return queryUntil(st, start, mid, l, r, current*2 + 1);
    }

    if(mid < l){
        return queryUntil(st, mid + 1, end, l, r, current*2 + 2);
    }

    Node answer;
    answer.setInternal(queryUntil(st, start, mid, l, r, current*2 + 1), queryUntil(st, mid + 1, end, l, r, current*2 + 2));
    return answer;
}

Node query(Node *st, long long n, long long l, long long r){
    return queryUntil(st, 0, n - 1, l, r, 0);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, k;
    cin >> n >> k;
    Node arr[n];
    for(long long i = 0; i < n; i++){
        arr[i].init();
    }

    Node *st = constructST(arr, n);
    
    long long count = 0;
    for(long long i = 0; i <= n - k; i++){
        Node temp = query(st, n, i, i + k - 1);
        if(temp.isTriangle()){
            // printf("l = %d, r = %d, sum = %d, max = %d\n", i, i + k - 1, temp.sum, temp.max_);
            count ++;
        }
    }

    cout << count << endl;
}



// 6 3
// 1 3 4 2 5 9
//            24,9
//          /     \    
//       8,4       16,9
//       /\         /\
//     4,3 4,4    7,5 9,9
//     /\         /\ 
//  1,1 3,3     2,2 5,5   