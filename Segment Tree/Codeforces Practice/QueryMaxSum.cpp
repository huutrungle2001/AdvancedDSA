/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
Author: Lê Hữu Trung
Supervisor: Dr. Vũ Đức Minh
*/

#include<bits/stdc++.h>
using namespace std;

// Each node contain sum and max_sum on a segment
struct Node{
    long long maxPrefixSum;
    long long maxSuffixSum;
    long long totalSum;
    long long maxSubArraySum;
    
    // Constructor
    Node(){
        maxPrefixSum = maxSuffixSum = totalSum = maxSubArraySum = INT_MIN;
    }

    // Set leaft node
    void setLeaf(long long n){
        maxPrefixSum = maxSuffixSum = maxSubArraySum = totalSum = n;
    }

    // Set internal node
    void setInternal(Node left, Node right){
        maxPrefixSum = max(left.maxPrefixSum, left.totalSum + right.maxPrefixSum);
        maxSuffixSum = max(right.maxSuffixSum, right.totalSum + left.maxSuffixSum);
        totalSum = left.totalSum + right.totalSum;
        maxSubArraySum = max(max(left.maxSubArraySum, right.maxSubArraySum), left.maxSuffixSum + right.maxPrefixSum);
    }
};

long long getMid(long long start, long long end){
    return start + (end - start)/2;
}

void constructSTUntil(Node *st, long long arr[], long long start, long long end, long long current){
    if(start == end){
        st[current].setLeaf(arr[start]);
        return;
    }

    long long mid = getMid(start, end);

    constructSTUntil(st, arr, start, mid, current*2 + 1);
    constructSTUntil(st, arr, mid + 1, end, current*2 + 2);

    st[current].setInternal(st[current*2 + 1], st[current*2 + 2]);
}

Node *constructST(long long arr[], long long n){
    long long height = (int)ceil(log2(n));
    long long max_size = 2*(int)pow(2, height) - 1;
    Node *st = new Node[max_size];
    constructSTUntil(st, arr, 0, n - 1, 0);
    return st;
}

Node getMaxSumUntil(Node *st, long long start, long long end, long long current, long long l, long long r){
    if(r > end || r < start || l > r){
        Node null;
        return null;
    }

    if(l <= start && r >= end){
        return st[current];
    }

    long long mid = getMid(start, end);

    Node left = getMaxSumUntil(st, start, mid, current*2 + 1, l, r);
    Node right = getMaxSumUntil(st, mid + 1, end, current*2 + 2, l, r);
    Node answer;
    answer.setInternal(left, right);
    return answer;
}

long long getMaxSum(Node *st, long long l, long long r, long long n){
    Node answer = getMaxSumUntil(st, 0, n - 1, 0, l, r);
    return answer.maxSubArraySum > 0 ? answer.maxSubArraySum : 0;
}

void updateValueUntil(Node *st, long long arr[], long long start, long long end, long long current, long long index, long long value){
    if(index < start || index > end){
        return;
    }

    if(start == end){
        arr[start] = value;
        st[current].setLeaf(value);
        return;
    }

    long long mid = getMid(start, end);
    updateValueUntil(st, arr, start, mid, current*2 + 1, index, value);
    updateValueUntil(st, arr, mid + 1, end, current*2 + 2, index, value);
    st[current].setInternal(st[current*2 + 1], st[current*2 + 2]);
}

void updateValue(Node *st, long long arr[], long long index, long long value, long long n){
    updateValueUntil(st, arr, 0, n - 1, 0, index, value);   
}

int main(){
    long long n, m;
    cin >> n >> m;
    long long arr[n];
    for(long long i = 0; i < n; i++){
        cin >> arr[i];
    }

    Node *st = constructST(arr, n);
    cout << getMaxSum(st, 0, n - 1, n) << "\n";
    long long index, value;
    for(long long i = 0; i < m; i++){
        cin >> index >> value;
        updateValue(st, arr, index, value, n);
        cout << getMaxSum(st, 0, n - 1, n) << "\n";
    }
}