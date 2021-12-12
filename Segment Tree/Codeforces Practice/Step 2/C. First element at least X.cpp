/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/C
Author: Lê Hữu Trung
Instructor: Ph.D. Vũ Đức Minh
*/

#include <bits/stdc++.h>
using namespace std;

// A data structure for each node in the Segment Tree.
struct Node {
    int value;

    // Constructor of an empty node.
    Node() {
        value = INT_MIN;
    }

    // A method for setting the leaf node.
    void set(int value_) {
        value = value_;
    }

    // A method for setting the internal node.
    void merge(Node left, Node right) {
        value = max(left.value, right.value);
    }

    void display() {
        cout << value << "\n";
    }
};

int getMid(int start, int end) {
    return start + (end - start) / 2;
}

// A data structure for the Segment Tree.
struct SegmentTree {
    // Maximum size of the segment tree.
    int size;

    // A vector for storing the nodes of the Segment Tree.
    vector<Node> ST;

    // Constructor of the Segment Tree.
    SegmentTree(int n) {
        // Calculate the height.
        int height = (int)ceil(log2(n));
        // Calculate the maxsize.
        size = 2 * pow(2, height) - 1;
        // Allocate memory for Segment Tree.
        ST.resize(size);
    }

    // A recursive method for constructing the Segment Tree.
    void Construct(int arr[], int n, int start, int end, int current) {
        // If there is only one element in the array, store its information in the current node and stop recurring.
        if (start == end) {
            ST[current].set(arr[start]);
            return;
        }

        int mid = getMid(start, end);

        // If there are more than one element in the array,
        // divide the array into two halves and call the same procedure on each half.
        Construct(arr, n, start, mid, current * 2 + 1);
        Construct(arr, n, mid + 1, end, current * 2 + 2);

        // Store the information of the left and right child in the internal node.
        ST[current].merge(ST[current * 2 + 1], ST[current * 2 + 2]);
    }

    // Overloading method for constructing the Segment Tree.
    void Construct(int arr[], int n) {
        Construct(arr, n, 0, n - 1, 0);
    }

    // A recursive method for range query on the Segment Tree.
    Node Query(int start, int end, int current, int X) {
        // Declare an empty node with initial value of zero to store the query answer.
        Node answer;

        // Not finding the element at least X
        if (start > end || (start == end && ST[current].value < X)) {
            answer.set(-1);
            return answer;
        }

        // On reaching the segment with the length of 1 and the value is at least X, return the array index
        if (start == end) {
            answer.set(start);
            return answer;
        }

        int mid = getMid(start, end);

        // If max on the left subtree is greater than X, find the answer on this subtree
        if (ST[current * 2 + 1].value >= X) {
            answer = Query(start, mid, current * 2 + 1, X);
        }
        // Else the answer is on the right subtree
        else {
            answer = Query(mid + 1, end, current * 2 + 2, X);
        }

        return answer;
    }

    // Overloading method for range query on the Segment Tree.
    Node Query(int n, int X) {
        return Query(0, n - 1, 0, X);
    }

    // Recursive method for updating the Segment Tree.
    void Update(int position, int value, int start, int end, int current) {
        // If the position is completely outside the current segment, just stop recurring.
        if (position < start || position > end) {
            return;
        }

        if (start == end) {
            ST[current].set(value);
            return;
        }

        int mid = getMid(start, end);

        if (position <= mid) {
            Update(position, value, start, mid, current * 2 + 1);
        } else {
            Update(position, value, mid + 1, end, current * 2 + 2);
        }

        ST[current].merge(ST[current * 2 + 1], ST[current * 2 + 2]);
    }

    void Update(int position, int value, int n) {
        Update(position, value, 0, n - 1, 0);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    int nums[n];

    for (int &num : nums) {
        cin >> num;
    }
    SegmentTree tree(n);
    tree.Construct(nums, n);

    for (int i = 0; i < m; i++) {
        int operation;
        cin >> operation;
        if (operation == 1) {
            int position, value;
            cin >> position >> value;
            tree.Update(position, value, n);
        } else {
            int X;
            cin >> X;
            tree.Query(n, X).display();
        }
    }
}