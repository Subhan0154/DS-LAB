#include <iostream>
#include <string>
#include <limits>
using namespace std;

// General binary tree node
class StaffNode {
public:
    string name;
    StaffNode *left, *right;

    StaffNode(string n) {
        name = n;
        left = NULL;
        right = NULL;
    }
};

void showStaff(StaffNode *node) {
    if (node == NULL) return;

    cout << node->name << " -> Left: ";
    if (node->left != NULL) cout << node->left->name;
    else cout << "NULL";

    cout << " | Right: ";
    if (node->right != NULL) cout << node->right->name;
    else cout << "NULL";
    cout << endl;

    showStaff(node->left);
    showStaff(node->right);
}

void showStaffInOrder(StaffNode *node) {
    if (node == NULL) return;
    showStaffInOrder(node->left);
    cout << node->name << " | ";
    showStaffInOrder(node->right);
}

void deleteStaff(StaffNode *node) {
    if (node == NULL) return;
    deleteStaff(node->left);
    deleteStaff(node->right);
    delete node;
}

// BST node
class BSTNode {
public:
    int id;
    BSTNode *left, *right;

    BSTNode(int value) {
        id = value;
        left = NULL;
        right = NULL;
    }
};

// Binary Search Tree class
class BST {
private:
    BSTNode *root;

    bool insertHelper(BSTNode *&node, int id) {
        if (node == NULL) {
            node = new BSTNode(id);
            return true;
        }
        if (id < node->id) return insertHelper(node->left, id);
        if (id > node->id) return insertHelper(node->right, id);
        return false; // Duplicate ID
    }

    BSTNode *smallest(BSTNode *node) {
        while (node != NULL && node->left != NULL)
            node = node->left;
        return node;
    }

    bool removeHelper(BSTNode *&node, int id) {
        if (node == NULL) return false;

        if (id < node->id) return removeHelper(node->left, id);
        if (id > node->id) return removeHelper(node->right, id);

        // Case 1: leaf node
        if (node->left == NULL && node->right == NULL) {
            delete node;
            node = NULL;
        }
        // Case 2: node has one child
        else if (node->left == NULL || node->right == NULL) {
            BSTNode *oldNode = node;
            if (node->left != NULL) node = node->left;
            else node = node->right;
            delete oldNode;
        }
        // Case 3: node has two children
        else {
            BSTNode *next = smallest(node->right);
            node->id = next->id;
            removeHelper(node->right, next->id);
        }
        return true;
    }

    void inOrderHelper(BSTNode *node) {
        if (node == NULL) return;
        inOrderHelper(node->left);
        cout << node->id << " ";
        inOrderHelper(node->right);
    }

    void destroy(BSTNode *node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() { root = NULL; }
    ~BST() { destroy(root); }

    bool insert(int id) { return insertHelper(root, id); }
    bool remove(int id) { return removeHelper(root, id); }

    bool search(int id, int &visits) {
        visits = 0;
        BSTNode *current = root;
        while (current != NULL) {
            visits++;
            if (id == current->id) return true;
            if (id < current->id) current = current->left;
            else current = current->right;
        }
        return false;
    }

    void display() {
        inOrderHelper(root);
        cout << endl;
    }
};

int readInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) return value;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}

void fillOriginal(BST &tree) {
    int ids[7] = {48, 28, 68, 18, 38, 58, 78};
    int i;
    for (i = 0; i < 7; i++) tree.insert(ids[i]);
}

void searchAndShow(BST &tree, int id) {
    int visits;
    bool found = tree.search(id, visits);
    cout << "Search " << id << ": " << (found ? "FOUND" : "NOT FOUND")
         << " | Node visits = " << visits << endl;
}

void testDeletion(string title, int removeFirst, int target) {
    BST tree;
    fillOriginal(tree);

    if (removeFirst != -1) tree.remove(removeFirst);

    cout << title << endl;
    cout << "Before: ";
    tree.display();

    if (tree.remove(target))
        cout << "Deleted " << target << ".\n";
    else
        cout << target << " was not found.\n";

    cout << "After:  ";
    tree.display();
    cout << endl;
}

int main() {
    cout << "===== PART A: GENERAL BINARY TREE =====\n";

    StaffNode *root = new StaffNode("Vice Chancellor");
    root->left = new StaffNode("Dean");
    root->right = new StaffNode("Registrar");
    root->left->left = new StaffNode("HOD Computer Science");
    root->left->right = new StaffNode("HOD Mathematics");
    root->right->left = new StaffNode("Accountant");
    root->right->right = new StaffNode("Librarian");

    showStaff(root);
    cout << "In-order of general tree: ";
    showStaffInOrder(root);
    cout << "\n\n";

    cout << "===== PART B: BST OF STAFF IDs =====\n";
    BST tree;
    fillOriginal(tree);

    cout << "Initial IDs: ";
    tree.display();

    cout << "\n--- Insert three additional positive staff IDs ---\n";
    int count = 0;
    while (count < 3) {
        int id = readInt("Enter a positive staff ID: ");
        if (id <= 0) {
            cout << "Staff ID must be positive. Try again.\n";
        } else if (tree.insert(id)) {
            cout << id << " inserted.\n";
            count++;
        } else {
            cout << id << " already exists. Duplicate rejected.\n";
        }
    }

    cout << "IDs after insertion: ";
    tree.display();

    cout << "\n--- Search tests (node visits included) ---\n";
    searchAndShow(tree, 58); // Existing: initial ID always remains here

    // Find a missing positive ID without assuming a particular user input.
    int missing = 1000000;
    int visits;
    while (tree.search(missing, visits)) missing++;
    searchAndShow(tree, missing);

    // All IDs must be positive, so 0 is smaller than every registered ID.
    searchAndShow(tree, 0);

    cout << "\n--- Deletion tests using fresh original BSTs ---\n";
    testDeletion("Test 1: Delete leaf node 18", -1, 18);
    testDeletion("Test 2: Delete node 28 with one child (remove 18 first)", 18, 28);
    testDeletion("Test 3: Delete node 28 with two children", -1, 28);
    testDeletion("Test 4: Delete root 48 with two children", -1, 48);

    cout << "--- Delete an ID from the main BST ---\n";
    int del = readInt("Enter a positive staff ID to delete: ");
    if (tree.remove(del)) cout << del << " deleted.\n";
    else cout << del << " not found. Nothing deleted.\n";

    cout << "Remaining staff IDs in ascending order: ";
    tree.display();

    cout << "\nA general binary tree has no sorting rule, so in-order traversal is not necessarily sorted.\n";
    cout << "A BST keeps smaller IDs on the left and larger IDs on the right, so in-order traversal is ascending.\n";

    deleteStaff(root);
    return 0;
}
