#include <iostream>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string n) {
        name = n;
        left = NULL;
        right = NULL;
    }
};

void display(Node* root) {
    if (root == NULL)
        return;

    cout << "Member: " << root->name;

    cout << " | Left Child: ";
    if (root->left != NULL)
        cout << root->left->name;
    else
        cout << "None";

    cout << " | Right Child: ";
    if (root->right != NULL)
        cout << root->right->name;
    else
        cout << "None";

    cout << endl;

    display(root->left);
    display(root->right);
}

int main() {
    Node* root = new Node("HOD");

    root->left = new Node("Coordinator CS");
    root->right = new Node("Coordinator DS");

    root->left->left = new Node("Faculty 1");
    root->left->right = new Node("Faculty 2");

    root->right->left = new Node("Faculty 3");
    root->right->right = new Node("Faculty 4");

    cout << "University Department Hierarchy\n\n";

    display(root);

    return 0;
}
