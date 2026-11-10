#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

int getHeight(Node* root) {
    if (root == NULL)
        return 0;

    return root->height;
}

int getBalance(Node* root) {
    if (root == NULL)
        return 0;

    return getHeight(root->left) - getHeight(root->right);
}

// Right Rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    return x;
}

// Left Rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    return y;
}

// AVL Insertion
Node* insert(Node* root, int value) {

    if (root == NULL)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else if (value > root->data)
        root->right = insert(root->right, value);

    else
        return root;

    root->height = 1 + max(getHeight(root->left),
                           getHeight(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order Traversal
void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Display Tree Structure
void display(Node* root, int space = 0) {
    if (root == NULL)
        return;

    space += 5;

    display(root->right, space);

    cout << endl;

    for (int i = 5; i < space; i++)
        cout << " ";

    cout << root->data << endl;

    display(root->left, space);
}

// Display Height and Balance Factor
void showDetails(Node* root) {
    if (root == NULL)
        return;

    cout << "Token: " << root->data
         << " | Height: " << root->height
         << " | Balance Factor: " << getBalance(root)
         << endl;

    showDetails(root->left);
    showDetails(root->right);
}

int main() {

    Node* root = NULL;

    int tokens[] = {15, 25, 35, 45, 55, 65, 75};

    for (int i = 0; i < 7; i++) {
        root = insert(root, tokens[i]);
    }

    cout << "In-order Traversal:\n";
    inorder(root);

    cout << "\n\nFinal Balanced AVL Tree:\n";
    display(root);

    cout << "\nNode Details:\n";
    showDetails(root);

    return 0;
}
