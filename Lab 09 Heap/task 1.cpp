#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

class StudentNode {
public:
    string name;
    int rollNo;
    int marks;
    StudentNode* left;
    StudentNode* right;

    StudentNode(string n, int r, int m) {
        name = n;
        rollNo = r;
        marks = m;
        left = NULL;
        right = NULL;
    }
};

class MeritMaxHeap {
private:
    StudentNode* root;

    void swapData(StudentNode* a, StudentNode* b) {
        swap(a->name, b->name);
        swap(a->rollNo, b->rollNo);
        swap(a->marks, b->marks);
    }

    StudentNode* getParent(StudentNode* root, StudentNode* target) {
        if (!root || root == target) return NULL;
        queue<StudentNode*> q;
        q.push(root);
        while (!q.empty()) {
            StudentNode* curr = q.front();
            q.pop();
            if (curr->left == target || curr->right == target)
                return curr;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return NULL;
    }

    void heapifyUp(StudentNode* node) {
        StudentNode* parent = getParent(root, node);
        while (parent != NULL && node->marks > parent->marks) {
            swapData(node, parent);
            node = parent;
            parent = getParent(root, node);
        }
    }

    void heapifyDown(StudentNode* node) {
        while (node != NULL) {
            StudentNode* largest = node;
            if (node->left && node->left->marks > largest->marks) {
                largest = node->left;
            }
            if (node->right && node->right->marks > largest->marks) {
                largest = node->right;
            }
            if (largest != node) {
                swapData(node, largest);
                node = largest;
            } else {
                break;
            }
        }
    }

public:
    MeritMaxHeap() {
        root = NULL;
    }

    void insert(string name, int rollNo, int marks) {
        StudentNode* newNode = new StudentNode(name, rollNo, marks);
        if (root == NULL) {
            root = newNode;
            return;
        }

        queue<StudentNode*> q;
        q.push(root);
        while (!q.empty()) {
            StudentNode* curr = q.front();
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

    void deleteMax() {
        if (root == NULL) {
            cout << "Heap is empty!" << endl;
            return;
        }

        cout << "\nDeleting Top Merit Student: " << root->name 
             << " (Roll: " << root->rollNo << ", Marks: " << root->marks << ")" << endl;

        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
            return;
        }

        queue<StudentNode*> q;
        q.push(root);
        StudentNode* lastNode = NULL;
        while (!q.empty()) {
            lastNode = q.front();
            q.pop();
            if (lastNode->left) q.push(lastNode->left);
            if (lastNode->right) q.push(lastNode->right);
        }

        swapData(root, lastNode);
        StudentNode* parent = getParent(root, lastNode);
        if (parent->left == lastNode) parent->left = NULL;
        else parent->right = NULL;
        delete lastNode;

        heapifyDown(root);
    }

    void displayLevelOrder() {
        if (root == NULL) {
            cout << "Heap is empty!" << endl;
            return;
        }
        queue<StudentNode*> q;
        q.push(root);
        while (!q.empty()) {
            StudentNode* curr = q.front();
            q.pop();
            cout << "Name: " << curr->name << " | Roll: " << curr->rollNo 
                 << " | Marks: " << curr->marks << endl;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
};

int main() {
    MeritMaxHeap meritList;

    meritList.insert("Ali", 101, 78);
    meritList.insert("Sara", 102, 92);
    meritList.insert("Usman", 103, 85);
    meritList.insert("Ayesha", 104, 96);
    meritList.insert("Bilal", 105, 81);
    meritList.insert("Zainab", 106, 89);

    cout << "--- Student Merit Heap (Level Order) ---" << endl;
    meritList.displayLevelOrder();

    meritList.deleteMax();

    cout << "\n--- Updated Merit Heap After Deletion ---" << endl;
    meritList.displayLevelOrder();

    return 0;
}
