// Wrong answer on test 14 (no matter long long or int)

#include<bits/stdc++.h>
using namespace std;

// Mỗi nút sẽ chứa 2 thông tin là giá trị của nút và số lần xuất hiện của nút trong đoạn mà nút này quản lý
struct Node{
    // Mặc định mỗi nút sẽ xuất hiện 1 lần
    long long value, count = 1;

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

long long getMid(long long start, long long end){
    return start + (end - start)/2;
}

// Xây dựng cây bằng đệ quy
void constructSTUntil(Node arr[], long long start, long long end, Node *st, long long current){
    if(start == end){
        st[current].copy(arr[start]);
        return;
    }

    long long mid = getMid(start, end);

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

Node *constructST(Node arr[], long long n){
    long long x = (long long)ceil(log2(n));
    long long max_size = 2*(long long)pow(2, x) - 1;
    Node *st = new Node[max_size];
    constructSTUntil(arr, 0, n - 1, st, 0);
    return st;
}

Node getMinUntil(Node *st, long long start, long long end, long long l, long long r, long long current){
    if(l <= start && r >= end){
        return st[current];
    }

    if(r < start || l > end){
        Node other = {INT_MAX, INT_MAX};
        return other;
    }

    long long mid = getMid(start, end);
    // Hàm min này được nạp chồng bởi hàm min đã tạo bên trên
    return min(getMinUntil(st, start, mid, l , r, current*2 + 1), getMinUntil(st, mid + 1, end, l, r, current*2 + 2));
}

Node getMin(Node *st, long long n, long long l, long long r){
    Node error = {-1, -1};
    return (l < 0 || r > n - 1 || l > r) ? error : getMinUntil(st, 0, n - 1, l, r, 0);
}

void updateValue(Node arr[], Node *st, long long start, long long end, long long index, Node other, long long current){
    if(index < start || index > end){
        return;
    }

    if(start == end){
        arr[index].copy(other);
        st[current].copy(other);
    }else{
        long long mid = getMid(start, end);
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
}

// Hàm show để in thông tin 1 nút cho tiện
void show(Node n){
    cout << n.value << " " << n.count << endl;
}

int main(){
    long long n, m, option, index, value, left, right;
    cin >> n >> m;
    Node arr[n];
    for(long long i = 0; i < n; i++){
        cin >> arr[i].value;
    }
    Node *st = constructST(arr, n);
    Node other;
    for(long long i = 0; i < m; i++){
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