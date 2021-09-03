#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *left;
    Node *right;
};

// Tạo ra 1 nút độc lập không nối với nút nào
Node *CreateNode(int x){
    Node *p = new Node();
    p->data = x;
    p->left = p->right = NULL;
    return p;
}

// Tìm vị trí trên cây để Insert nút
Node *FindInsert(Node *root, int x){
    if(root == NULL){
        return NULL;
    }

    Node *p = root;
    Node *f = p;
    while(p != NULL){
        f = p;
        p = p->data > x ? p->left : p->right;
    }

    return f;
}

// Insert nút vào dùng hàm FindInsert để tìm vị trí cần insert
void InsertNode(Node *&root, int x){
    Node *n = CreateNode(x);
    if(root == NULL){
        root = n;
        return;
    }else{
        Node *f = FindInsert(root, x);
        if(f != NULL){
            if(f->data > x){
                f->left = n;
            }else{
                f->right = n;
            }
        }
    }
}

// Tạo ra 1 cây từ mảng 
void CreateTree(Node *&root, int a[], int n){
    for (int i = 0; i < n; i++){
        InsertNode(root, a[i]);
    }
}

// Tìm kiếm vị trí của một phần tử trong cây
Node *RecursiveSearch(Node *root, int x){
    if(root == NULL){
        return NULL;
    }

    if(root->data == x){
        return root;
    }

    if(root->data > x){
        RecursiveSearch(root->left, x);
    }else{
        RecursiveSearch(root->right, x);
    }
}

// Duyệt từ nút cha sang nút con trái rồi đến nút con phải
void NodeLeftRight(Node *root){
    if(root == NULL){
        return;
    }
    cout << root->data << " ";
    NodeLeftRight(root->left);
    NodeLeftRight(root->right);
}

// Duyệt từ nút con trái đến nút cha đến nút con phải để có thứ tự tăng dần
void LeftNodeRight(Node *root) {
    if(root != NULL) {
        LeftNodeRight(root->left);
        cout << root->data << " ";
        LeftNodeRight(root->right);
    }
}

int main()
{
    Node *root = NULL;
    int a[] = {40, 5, 35, 45, 15, 56, 48, 13, 16, 49, 47};
    int n = 11;
    CreateTree(root, a, n);
    LeftNodeRight(root);
    return 0;
}