#include <iostream>
#include <queue>
#include <string>
using namespace std;

class PatientNode {
public:
    string name;
    int patientID;
    int priority;
    PatientNode* left;
    PatientNode* right;

    PatientNode(string n, int id, int p) {
        name = n;
        patientID = id;
        priority = p;
        left = NULL;
        right = NULL;
    }
};

class EmergencyMaxHeap {
private:
    PatientNode* root;

    void swapData(PatientNode* a, PatientNode* b) {
        swap(a->name, b->name);
        swap(a->patientID, b->patientID);
        swap(a->priority, b->priority);
    }

    PatientNode* getParent(PatientNode* root, PatientNode* target) {
        if (!root || root == target) return NULL;
        queue<PatientNode*> q;
        q.push(root);
        while (!q.empty()) {
            PatientNode* curr = q.front();
            q.pop();
            if (curr->left == target || curr->right == target)
                return curr;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return NULL;
    }

    void heapifyUp(PatientNode* node) {
        PatientNode* parent = getParent(root, node);
        while (parent != NULL && node->priority > parent->priority) {
            swapData(node, parent);
            node = parent;
            parent = getParent(root, node);
        }
    }

    void heapifyDown(PatientNode* node) {
        while (node != NULL) {
            PatientNode* largest = node;
            if (node->left && node->left->priority > largest->priority) {
                largest = node->left;
            }
            if (node->right && node->right->priority > largest->priority) {
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
    EmergencyMaxHeap() {
        root = NULL;
    }

    void insert(string name, int id, int priority) {
        PatientNode* newNode = new PatientNode(name, id, priority);
        if (root == NULL) {
            root = newNode;
            return;
        }

        queue<PatientNode*> q;
        q.push(root);
        while (!q.empty()) {
            PatientNode* curr = q.front();
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

    void displayTopPatient() {
        if (root == NULL) {
            cout << "No patients in queue." << endl;
            return;
        }
        cout << "Highest Priority Patient: " << root->name 
             << " | ID: " << root->patientID 
             << " | Priority: " << root->priority << endl;
    }

    void treatTopPatient() {
        if (root == NULL) {
            cout << "No patients to treat." << endl;
            return;
        }

        cout << "\nTreating and removing patient: " << root->name 
             << " (ID: " << root->patientID << ")" << endl;

        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
            return;
        }

        queue<PatientNode*> q;
        q.push(root);
        PatientNode* lastNode = NULL;
        while (!q.empty()) {
            lastNode = q.front();
            q.pop();
            if (lastNode->left) q.push(lastNode->left);
            if (lastNode->right) q.push(lastNode->right);
        }

        swapData(root, lastNode);
        PatientNode* parent = getParent(root, lastNode);
        if (parent->left == lastNode) parent->left = NULL;
        else parent->right = NULL;
        delete lastNode;

        heapifyDown(root);
    }

    void displayLevelOrder() {
        if (root == NULL) {
            cout << "Queue is empty." << endl;
            return;
        }
        queue<PatientNode*> q;
        q.push(root);
        while (!q.empty()) {
            PatientNode* curr = q.front();
            q.pop();
            cout << "Name: " << curr->name << " | ID: " << curr->patientID 
                 << " | Priority: " << curr->priority << endl;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
};

int main() {
    EmergencyMaxHeap er;

    er.insert("Ahmed", 201, 4);
    er.insert("Fatima", 202, 9);
    er.insert("Kamran", 203, 6);
    er.insert("Hina", 204, 10);
    er.insert("Tariq", 205, 3);
    er.insert("Nadia", 206, 8);

    cout << "--- All Emergency Patients (Level Order) ---" << endl;
    er.displayLevelOrder();

    cout << endl;
    er.displayTopPatient();

    er.treatTopPatient();

    cout << "\n--- Next Patient For Treatment ---" << endl;
    er.displayTopPatient();

    return 0;
}
