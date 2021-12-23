// Problem Link: https://oj.vnoi.info/problem/segtree_itez1

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int value;

    Node() {
        value = INT_MIN;
    }

    void set(int other) {
        value = other;
    }

    void merge(Node left, Node right) {
        value = max(left.value, right.value);
    }

    void display() {
        cout << value << "\n";
    }
};

struct SegmentTree {
    vector<int> arr;
    vector<Node> ST;
    int n, size;

    void init(vector<int> input, int inputSize) {
        arr = input;
        n = inputSize;
        int height = (int)ceil(log2(n));
        size = 2 * pow(2, height) - 1;
        ST.resize(size);
    }

    void construct(int start, int end, int current) {
        if (start == end) {
            ST[current].set(arr[start]);
            return;
        }

        int mid = start + (end - start) / 2;

        construct(start, mid, current * 2 + 1);
        construct(mid + 1, end, current * 2 + 2);

        ST[current].merge(ST[current * 2 + 1], ST[current * 2 + 2]);
    }

    SegmentTree(vector<int> input, int inputSise) {
        init(input, inputSise);
        construct(0, n - 1, 0);
    }

    Node Query(int l, int r, int start, int end, int current) {
        if (l <= start && r >= end) {
            return ST[current];
        }

        Node answer;

        if (l > end || r < start) {
            return answer;
        }

        int mid = start + (end - start) / 2;

        Node left = Query(l, r, start, mid, current * 2 + 1);
        Node right = Query(l, r, mid + 1, end, current * 2 + 2);
        answer.merge(left, right);

        return answer;
    }

    Node Query(int l, int r) {
        return Query(l, r, 0, n - 1, 0);
    }

    void update(int value, int position, int start, int end, int current) {
        if (position < start || position > end) {
            return;
        }

        if (start == end) {
            ST[current].set(value);
            return;
        }

        int mid = start + (end - start) / 2;

        if (position <= mid) {
            update(value, position, start, mid, current * 2 + 1);
        } else {
            update(value, position, mid + 1, end, current * 2 + 2);
        }

        Node left = ST[current * 2 + 1];
        Node right = ST[current * 2 + 2];
        ST[current].merge(left, right);
    }

    void update(int value, int postion) {
        update(value, postion, 0, n - 1, 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> noodles(n);

    for (int &it : noodles) {
        cin >> it;
    }

    SegmentTree tree(noodles, n);

    int q;
    cin >> q;

    while (q-- > 0) {
        int operation;
        cin >> operation;

        if (operation == 1) {
            int position, value;
            cin >> position >> value;
            tree.update(value, position - 1);
        } else {
            int l, r;
            cin >> l >> r;
            tree.Query(l - 1, r - 1).display();
        }
    }
}