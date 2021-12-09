/*
Problem Link: https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
Author: Lê Hữu Trung
Instructor: Dr. Vũ Đức Minh
*/

#include <bits/stdc++.h>
using namespace std;

// A data structure for each node in the Segment Tree.
struct Node {
    // Each node contain sum and max_sum on a segment
    long long maxPrefixSum;
    long long maxSuffixSum;
    long long totalSum;
    long long maxSubArraySum;

    // Constructor of an empty node.
    Node() {
        maxPrefixSum = maxSuffixSum = totalSum = maxSubArraySum = INT_MIN;
    }

    // A method for setting the leaf node.
    void set(long long value) {
        maxPrefixSum = maxSuffixSum = maxSubArraySum = totalSum = value;
    }

    // A method for setting the internal node.
    void merge(Node left, Node right) {
        maxPrefixSum = max(left.maxPrefixSum, left.totalSum + right.maxPrefixSum);
        maxSuffixSum = max(right.maxSuffixSum, right.totalSum + left.maxSuffixSum);
        totalSum = left.totalSum + right.totalSum;
        maxSubArraySum = max(max(left.maxSubArraySum, right.maxSubArraySum), left.maxSuffixSum + right.maxPrefixSum);
    }

    void display() {
        maxSubArraySum = maxSubArraySum > 0 ? maxSubArraySum : 0;
        cout << maxSubArraySum << "\n";
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
    void Construct(long long arr[], int n, int start, int end, int current) {
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
    void Construct(long long arr[], int n) {
        Construct(arr, n, 0, n - 1, 0);
    }

    // A recursive method for range query on the Segment Tree.
    Node Query(int l, int r, int start, int end, int current) {
        // Declare an empty node with initial value of zero to store the query answer.
        Node answer;

        // If the current segment is a part of the query range,
        // assign the current node to answer and return.
        if (l <= start && r >= end) {
            answer = ST[current];
            return answer;
        }

        // If the current segment is completely outside the query range, just return the empty node.
        if (l > end || r < start || l > r) {
            return answer;
        }

        // If the current segment overlaps with the query range,
        // divide it into two halves and call the same procedure for each half.
        int mid = getMid(start, end);

        Node left = Query(l, r, start, mid, current * 2 + 1);
        Node right = Query(l, r, mid + 1, end, current * 2 + 2);

        // Merge the query answer on the left and right halves and return.
        answer.merge(left, right);

        return answer;
    }

    // Overloading method for range query on the Segment Tree.
    Node Query(int l, int r, int n) {
        return Query(l, r, 0, n - 1, 0);
    }

    // Recursive method for updating the Segment Tree.
    void Update(int position, long long value, int start, int end, int current) {
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

    void Update(int position, long long value, int n) {
        Update(position, value, 0, n - 1, 0);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    long long nums[n];

    for (long long &num : nums) {
        cin >> num;
    }
    SegmentTree tree(n);
    tree.Construct(nums, n);

    tree.Query(0, n - 1, n).display();

    int index;
    long long value;
    for (int i = 0; i < m; i++) {
        cin >> index >> value;
        tree.Update(index, value, n);
        tree.Query(0, n - 1, n).display();
    }
}