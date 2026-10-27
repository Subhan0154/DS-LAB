#include <iostream>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;

    Node(int value) {
        id = value;
        left = NULL;
        right = NULL;
    }
};

class BST {
private:
    Node* root;

    Node* insertHelper(Node* node, int id, bool& added) {
        if (node == NULL) {
            added = true;
            return new Node(id);
        }
        if (id < node->id)
            node->left = insertHelper(node->left, id, added);
        else if (id > node->id)
            node->right = insertHelper(node->right, id, added);
        return node;
    }

    Node* smallest(Node* node) {
        while (node->left != NULL) node = node->left;
        return node;
    }

    Node* removeHelper(Node* node, int id, bool& removed) {
        if (node == NULL) return NULL;
        if (id < node->id) {
            node->left = removeHelper(node->left, id, removed);
        } else if (id > node->id) {
            node->right = removeHelper(node->right, id, removed);
        } else {
            removed = true;
            if (node->left == NULL) {
                Node* child = node->right;
                delete node;
                return child;
            }
            if (node->right == NULL) {
                Node* child = node->left;
                delete node;
                return child;
            }
            Node* next = smallest(node->right);
            node->id = next->id;
            bool temp = false;
            node->right = removeHelper(node->right, next->id, temp);
        }
        return node;
    }

    void inOrderHelper(Node* node) {
        if (node == NULL) return;
        inOrderHelper(node->left);
        cout << node->id << " ";
        inOrderHelper(node->right);
    }

    void preOrderHelper(Node* node) {
        if (node == NULL) return;
        cout << node->id << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }

    void postOrderHelper(Node* node) {
        if (node == NULL) return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->id << " ";
    }

    int countHelper(Node* node) {
        if (node == NULL) return 0;
        return 1 + countHelper(node->left) + countHelper(node->right);
    }

    int heightHelper(Node* node) {
        if (node == NULL) return 0;
        int l = heightHelper(node->left);
        int r = heightHelper(node->right);
        return 1 + (l > r ? l : r);
    }

    void destroy(Node* node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        destroy(root);
    }

    bool insert(int id) {
        bool added = false;
        root = insertHelper(root, id, added);
        return added;
    }

    bool search(int id) {
        Node* current = root;
        while (current != NULL) {
            if (id == current->id) return true;
            if (id < current->id) current = current->left;
            else current = current->right;
        }
        return false;
    }

    bool remove(int id) {
        bool removed = false;
        root = removeHelper(root, id, removed);
        return removed;
    }

    bool isEmpty() {
        return root == NULL;
    }

    void inOrder() {
        inOrderHelper(root);
        cout << endl;
    }

    void preOrder() {
        preOrderHelper(root);
        cout << endl;
    }

    void postOrder() {
        postOrderHelper(root);
        cout << endl;
    }

    int count() {
        return countHelper(root);
    }

    int height() {
        return heightHelper(root);
    }
};

void predictionTest() {
    BST tree;
    int ids[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int i = 0; i < 9; i++) tree.insert(ids[i]);

    cout << "--- Prediction Test ---" << endl;
    cout << "Operations: insert 60, 30, 90 then delete 55, 25, 40" << endl;
    cout << "Predicted in-order: 30 35 45 50 60 65 75 85 90" << endl;
    cout << "Predicted height: 4" << endl;

    tree.insert(60);
    tree.insert(30);
    tree.insert(90);
    tree.remove(55);
    tree.remove(25);
    tree.remove(40);

    cout << "Actual in-order: ";
    tree.inOrder();
    cout << "Actual height: " << tree.height() << endl;

    cout << "Deleting 65 twice:" << endl;
    cout << "First time: " << (tree.remove(65) ? "deleted" : "not found") << endl;
    cout << "Second time: " << (tree.remove(65) ? "deleted" : "not found, tree unchanged") << endl;

    cout << "Two-child deletion: the node is replaced by the smallest value of its right subtree." << endl;
    cout << "That value is larger than everything on the left and smaller than the rest on the right," << endl;
    cout << "so the BST property is preserved." << endl << endl;
}

int main() {
    predictionTest();

    BST tree;
    int ids[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int i = 0; i < 9; i++) tree.insert(ids[i]);

    int choice = 0;
    while (choice != 9) {
        cout << "\n1. Insert an ID" << endl;
        cout << "2. Search for an ID" << endl;
        cout << "3. Delete an ID" << endl;
        cout << "4. Display in-order" << endl;
        cout << "5. Display pre-order" << endl;
        cout << "6. Display post-order" << endl;
        cout << "7. Count nodes" << endl;
        cout << "8. Height of BST" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number from 1 to 9." << endl;
            choice = 0;
            continue;
        }

        int id;
        switch (choice) {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                if (tree.insert(id)) cout << id << " inserted." << endl;
                else cout << id << " already exists. Duplicate rejected." << endl;
                break;
            case 2:
                if (tree.isEmpty()) {
                    cout << "Tree is empty." << endl;
                } else {
                    cout << "Enter ID: ";
                    cin >> id;
                    cout << id << (tree.search(id) ? " found." : " not found.") << endl;
                }
                break;
            case 3:
                if (tree.isEmpty()) {
                    cout << "Tree is empty." << endl;
                } else {
                    cout << "Enter ID: ";
                    cin >> id;
                    if (tree.remove(id)) {
                        cout << id << " deleted. Updated IDs: ";
                        tree.inOrder();
                    } else {
                        cout << id << " does not exist." << endl;
                    }
                }
                break;
            case 4:
                cout << "In-order: ";
                tree.inOrder();
                break;
            case 5:
                cout << "Pre-order: ";
                tree.preOrder();
                break;
            case 6:
                cout << "Post-order: ";
                tree.postOrder();
                break;
            case 7:
                cout << "Total nodes: " << tree.count() << endl;
                break;
            case 8:
                cout << "Height: " << tree.height() << endl;
                break;
            case 9:
                cout << "Goodbye." << endl;
                break;
            default:
                cout << "Invalid choice. Enter a number from 1 to 9." << endl;
        }
    }
    return 0;
}
