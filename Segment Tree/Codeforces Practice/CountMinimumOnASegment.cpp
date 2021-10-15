/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C
Author: Lê Hữu Trung
Supervisor: Dr. Vũ Đức Minh
*/

#include<bits/stdc++.h>
using namespace std;

// Mỗi nút sẽ chứa 2 thông tin là giá trị của nút và số lần xuất hiện của nút trong đoạn mà nút này quản lý
struct Node{
    // Mặc định mỗi nút sẽ xuất hiện 1 lần
    int value, count = 1;

    // Khởi tạo nút từ 1 nút khác
    void copy(Node other){
        value = other.value;
        count = other.count;
    }

    // Cộng số lần xuất hiện của 2 nút lại khi giá trị của 2 nút này bằng nhau
    void addCount(Node n1, Node n2){
        value = n1.value;
        count = n1.count + n2.count;
    }
};

// Hàm trả về nút có value nhỏ nhất
Node min(Node n1, Node n2){
    return n1.value < n2.value ? n1 : n2;
}

int getMid(int start, int end){
    return start + (end - start)/2;
}

// Xây dựng cây bằng đệ quy
void constructSTUntil(Node arr[], int start, int end, Node *st, int current){
    if(start == end){
        st[current].copy(arr[start]);
        return;
    }

    int mid = getMid(start, end);

    constructSTUntil(arr, start, mid, st, current*2 + 1);
    constructSTUntil(arr, mid + 1, end, st, current*2 + 2);
    if(st[current*2 + 1].value == st[current*2 + 2].value){
        // Nếu 2 nút trái phải có value bằng nhau thì nút cha sẽ có count bằng tổng count của 2 nút trái phải
        st[current].addCount(st[current*2 + 1], st[current*2 + 2]);
    }else{
        // Nếu không thì lấy nút có value bé hơn
        st[current].copy(min(st[current*2 + 1], st[current*2 + 2]));
    }
    return;
}

Node *constructST(Node arr[], int n){
    int x = (int)ceil(log2(n));
    int max_size = 2*(int)pow(2, x) - 1;
    Node *st = new Node[max_size];
    constructSTUntil(arr, 0, n - 1, st, 0);
    return st;
}

Node getMinUntil(Node *st, int start, int end, int l, int r, int current){
    if(l <= start && r >= end){
        return st[current];
    }

    if(r < start || l > end){
        Node other = {INT_MAX, INT_MAX};
        return other;
    }

    int mid = getMid(start, end);
    Node left = getMinUntil(st, start, mid, l , r, current*2 + 1);
    Node right = getMinUntil(st, mid + 1, end, l , r, current*2 + 2);
    Node answer;
    if(left.value == right.value){
        answer.addCount(left, right);
    }else{
        answer.copy(min(left, right));
    }
    return answer;
}

Node getMin(Node *st, int n, int l, int r){
    Node error = {-1, -1};
    return (l < 0 || r > n - 1 || l > r) ? error : getMinUntil(st, 0, n - 1, l, r, 0);
}

void updateValue(Node arr[], Node *st, int start, int end, int index, Node other, int current){
    if(index < start || index > end){
        return;
    }

    if(start == end){
        arr[index].copy(other);
        st[current].copy(other);
        return;
    }
    
    int mid = getMid(start, end);
    if(index >= start && index <= mid){
        updateValue(arr, st, start, mid, index, other, current*2 + 1);
    }else{
        updateValue(arr, st, mid + 1, end, index, other, current*2 + 2);
    }

    if(st[current*2 + 1].value == st[current*2 + 2].value){
        // Nếu sau khi update value mà 2 nút con trái phải có cùng value thì nút cha sẽ có count bằng tổng count của 2 nút con
        st[current].addCount(st[current*2 + 1], st[current*2 + 2]);
    }else{
        // Nếu 2 nút con trái phải có value khác nhau thì nút cha sẽ được copy từ nút con có value nhỏ hơn
        st[current].copy(min(st[current*2 + 1], st[current*2 + 2]));
    }
}

// Hàm show để in thông tin 1 nút cho tiện
void show(Node n){
    cout << n.value << " " << n.count << endl;
}

int main(){
    int n, m, option, index, value, left, right;
    cin >> n >> m;
    Node arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i].value;
    }
    Node *st = constructST(arr, n);
    Node other;
    for(int i = 0; i < m; i++){
        cin >> option;
        switch(option){
            case 1:
                cin >> index >> value;
                other = {value, 1};
                updateValue(arr, st, 0, n - 1, index, other, 0);
                break;
            case 2:
                cin >> left >> right;
                show(getMin(st, n, left, right - 1));
                break;
        }
    }
}

// Minh họa cây
// 3 4 3 5 2
//            2,1 
//         /      \
//      3,2       2,1
//     /  \      /  \
//   3,1  3,1  5,1  2,1
//  /   \
// 3,1  4,1

// 1 1 1 1 1
//            1,5 
//         /      \
//      1,3       1,2
//     /  \      /  \
//   1,2  1,1  1,1  1,1
//  /   \
// 1,1  1,1