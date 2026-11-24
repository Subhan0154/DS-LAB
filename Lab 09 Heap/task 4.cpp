#include <iostream>
#include <queue>
#include <string>
using namespace std;

class MedicineNode {
public:
    string name;
    int medID;
    int expiryDate;
    MedicineNode* left;
    MedicineNode* right;

    MedicineNode(string n, int id, int exp) {
        name = n;
        medID = id;
        expiryDate = exp;
        left = NULL;
        right = NULL;
    }
};

class MedicineMinHeap {
private:
    MedicineNode* root;

    void swapData(MedicineNode* a, MedicineNode* b) {
        swap(a->name, b->name);
        swap(a->medID, b->medID);
        swap(a->expiryDate, b->expiryDate);
    }

    MedicineNode* getParent(MedicineNode* root, MedicineNode* target) {
        if (!root || root == target) return NULL;
        queue<MedicineNode*> q;
        q.push(root);
        while (!q.empty()) {
            MedicineNode* curr = q.front();
            q.pop();
            if (curr->left == target || curr->right == target)
                return curr;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return NULL;
    }

    void heapifyUp(MedicineNode* node) {
        MedicineNode* parent = getParent(root, node);
        while (parent != NULL && node->expiryDate < parent->expiryDate) {
            swapData(node, parent);
            node = parent;
            parent = getParent(root, node);
        }
    }

    void heapifyDown(MedicineNode* node) {
        while (node != NULL) {
            MedicineNode* smallest = node;
            if (node->left && node->left->expiryDate < smallest->expiryDate) {
                smallest = node->left;
            }
            if (node->right && node->right->expiryDate < smallest->expiryDate) {
                smallest = node->right;
            }
            if (smallest != node) {
                swapData(node, smallest);
                node = smallest;
            } else {
                break;
            }
        }
    }

public:
    MedicineMinHeap() {
        root = NULL;
    }

    void insert(string name, int id, int expDate) {
        MedicineNode* newNode = new MedicineNode(name, id, expDate);
        if (root == NULL) {
            root = newNode;
            return;
        }

        queue<MedicineNode*> q;
        q.push(root);
        while (!q.empty()) {
            MedicineNode* curr = q.front();
            q.pop();

            if (curr->left == NULL) {
                curr->left = newNode;
                break;
            } else {
                q.push(curr->left);
            }

            if (curr->right == NULL) {
                curr->right = newNode;
                break;
            } else {
                q.push(curr->right);
            }
        }
        heapifyUp(newNode);
    }

    void deleteMin() {
        if (root == NULL) {
            cout << "Medicine stock is empty!" << endl;
            return;
        }

        cout << "\nRemoving Medicine Nearest to Expiry: " << root->name 
             << " (ID: " << root->medID << ", Expiry: " << root->expiryDate << ")" << endl;

        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
            return;
        }

        queue<MedicineNode*> q;
        q.push(root);
        MedicineNode* lastNode = NULL;
        while (!q.empty()) {
            lastNode = q.front();
            q.pop();
            if (lastNode->left) q.push(lastNode->left);
            if (lastNode->right) q.push(lastNode->right);
        }

        swapData(root, lastNode);
        MedicineNode* parent = getParent(root, lastNode);
        if (parent->left == lastNode) parent->left = NULL;
        else parent->right = NULL;
        delete lastNode;

        heapifyDown(root);
    }

    void displayLevelOrder() {
        if (root == NULL) {
            cout << "No medicines available." << endl;
            return;
        }
        queue<MedicineNode*> q;
        q.push(root);
        while (!q.empty()) {
            MedicineNode* curr = q.front();
            q.pop();
            cout << "Medicine: " << curr->name << " | ID: " << curr->medID 
                 << " | Expiry: " << curr->expiryDate << endl;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
};

int main() {
    MedicineMinHeap store;

    store.insert("Panadol", 301, 20270515);
    store.insert("Augmentin", 302, 20261201);
    store.insert("Brufen", 303, 20280120);
    store.insert("Flagyl", 304, 20261130);
    store.insert("Disprin", 305, 20270810);
    store.insert("Calpol", 306, 20270214);

    cout << "--- Medicine Stock Min Heap (Level Order) ---" << endl;
    store.displayLevelOrder();

    store.deleteMin();

    cout << "\n--- Updated Medicine Heap After Deletion ---" << endl;
    store.displayLevelOrder();

    return 0;
}
