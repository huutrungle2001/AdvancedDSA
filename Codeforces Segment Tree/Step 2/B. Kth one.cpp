/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B
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
        value = 0;
    }

    // A method for setting the leaf node.
    void set(int value_) {
        value = value_;
    }

    // A method for setting the internal node.
    void merge(Node left, Node right) {
        value = left.value + right.value;
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
    Node Query(int start, int end, int current, int k) {
        // Declare an empty node with initial value of zero to store the query answer.
        Node answer;

        // On reaching the segment with the length of 1, just return the array index
        if (start == end) {
            answer.set(start);
            return answer;
        }

        int mid = getMid(start, end);

        // If sum on the left subtree is larger than k, the answer is on this subtree
        if (k < ST[current * 2 + 1].value) {
            answer = Query(start, mid, current * 2 + 1, k);
        } 
        // Else find the answer on the right subtree
        else {
            answer = Query(mid + 1, end, current * 2 + 2, k - ST[current * 2 + 1].value);
        }

        return answer;
    }

    // Overloading method for range query on the Segment Tree.
    Node Query(int n, int k) {
        return Query(0, n - 1, 0, k);
    }

    // Recursive method for updating the Segment Tree.
    void Update(int position, int start, int end, int current) {
        // If the position is completely outside the current segment, just stop recurring.
        if (position < start || position > end) {
            return;
        }

        if (start == end) {
            ST[current].value = 1 - ST[current].value;
            return;
        }

        int mid = getMid(start, end);

        if (position <= mid) {
            Update(position, start, mid, current * 2 + 1);
        } else {
            Update(position, mid + 1, end, current * 2 + 2);
        }

        ST[current].merge(ST[current * 2 + 1], ST[current * 2 + 2]);
    }

    void Update(int position, int n) {
        Update(position, 0, n - 1, 0);
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
            int position;
            cin >> position;
            tree.Update(position, n);
        } else {
            int k;
            cin >> k;
            tree.Query(n, k).display();
        }
    }
}