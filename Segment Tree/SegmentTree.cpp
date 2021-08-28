#include<bits/stdc++.h>
using namespace std;

// Tính tổng giá trị của cây trong đoạn query
int getSumUntil(int *st, int start, int end, int l, int r, int current){
    // Chỉ số của cây nằm trong đoạn query
    // l <= start && end <= r
    if(l <= start && end <= r){
        return st[current];
    }

    // Đoạn query nằm ngoài đoạn chỉ số của cây
    // l <= r < start || end < l <= r
    if(r < start || end < l){
        return 0;
    }

    // Đoạn query nằm trong chỉ số của cây
    // start < l <= r < end
    int mid = start + (end - start)/2;
    return getSumUntil(st, start, mid, l, r, 2*current + 1) + getSumUntil(st, mid + 1, end, l, r, 2*current + 2);
}

int getSum(int *st, int n, int l, int r) {
    return (l < 0 || r > n-1 || l > r) ? cout << "Invalid query range\n", -1 : getSumUntil(st, 0, n-1, l, r, 0);
}

// Cập nhật giá trị của phần tử có chỉ số i dẫn đến các nút cha chứa phần tử này sẽ bị thay đổi giá trị
// diff là chênh lệch giữa giá trị cũ và giá trị mới
void updateValueUntil(int *st, int start, int end, int i, int diff, int current){
    // Nếu chỉ số i không nằm trong cây thì kết thúc hàm luôn
    if(i < start || i > end){
        return;
    }

    // Ngược lại nếu i nằm trong cây thì cập nhật từ nút cha xuống nút con
    st[current] += diff;
    if(start != end){
        int mid = start + (end - start)/2;
        updateValueUntil(st, start, mid, i, diff, 2*current + 1);
        updateValueUntil(st, mid + 1, end, i, diff, 2*current + 2); 
    }
}

int updateValue(int arr[], int *st, int n, int i, int value){
    if(i < 0 || i > n-1){
        return cout << "Invalid index\n", 0;
    }
    // Tính chênh lệch giữa giá trị cũ và mới
    int diff = value - arr[i];
    arr[i] = value;

    // Cập nhật các nút bị ảnh hưởng
    updateValueUntil(st, 0, n-1, i, diff, 0);
}

// Truyền vào 1 mảng, chỉ số bắt đầu và kết thúc của đoạn cần xây dựng thành cây, 1 con trỏ cây (mảng), chỉ số của nút hiện tại.
// Mỗi bước sẽ chia đôi mảng ra thành 2 phần cho đến khi phần bị chia đôi chỉ còn lại 1 phần tử.
int constructSTUntil(int arr[], int start, int end, int *st, int current){
    // Nếu vị trí bắt đầu bằng vị trí kết thúc nghĩa là chỉ có 1 phần tử nên sẽ gán luôn vào nút hiện tại.
    if(start == end){
        st[current] = arr[start];
        return arr[start];
    }

    // Lấy ra vị trí phần tử ở giữa.
    int mid = start + (end - start)/2;

    // Nếu có nhiều hơn 1 phần tử thì chia đôi ra làm 2 nửa trái phải, và đệ quy các bước cho đến khi gặp điểm dừng (còn lại 1 phần tử).
    // Nút hiện tại sẽ có giá trị bằng tổng của 2 nút con trái phải.
    // Nút con trái có chỉ số là 2*i + 1, nút con phải có chỉ số là 2*i + 2;
    st[current] = constructSTUntil(arr, start, mid, st, current*2 + 1) + constructSTUntil(arr, mid+1, end, st, current*2 + 2);
    return st[current];
}

int *constructST(int arr[], int n){
    // Tính chiều cao của cây
    int x = (int)(ceil(log2(n)));

    // Tính kích thước vùng nhớ cần cấp phát 
    int max_size = 2*(int)pow(2,x) - 1;

    // Cấp phát bộ nhớ cho cây
    int *st = new int[max_size];

    // Xây dựng cây phân đoạn
    constructSTUntil(arr, 0, n-1, st, 0);
    return st;
}

int main(){
    int n = 6;
    int arr[] = {1, 3, 5, 7, 9, 11};
    int *st = constructST(arr, n);

    cout << "Sum of value in [1:3] = " << getSum(st, n, 1, 3) << endl;

    updateValue(arr, st, n, 1, 10);
    cout << "Sum of value in [1:3] after updating = " << getSum(st, n, 1, 3) << endl;
    return 0;
}