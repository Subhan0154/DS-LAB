#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

class OrderNode {
public:
    int orderID;
    string customerName;
    double amount;
    OrderNode* left;
    OrderNode* right;

    OrderNode(int id, string name, double amt) {
        orderID = id;
        customerName = name;
        amount = amt;
        left = NULL;
        right = NULL;
    }
};

class OrderMaxHeap {
private:
    OrderNode* root;

    void swapData(OrderNode* a, OrderNode* b) {
        swap(a->orderID, b->orderID);
        swap(a->customerName, b->customerName);
        swap(a->amount, b->amount);
    }

    OrderNode* getParent(OrderNode* root, OrderNode* target) {
        if (!root || root == target) return NULL;
        queue<OrderNode*> q;
        q.push(root);
        while (!q.empty()) {
            OrderNode* curr = q.front();
            q.pop();
            if (curr->left == target || curr->right == target)
                return curr;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return NULL;
    }

    void heapifyUp(OrderNode* node) {
        OrderNode* parent = getParent(root, node);
        while (parent != NULL && node->amount > parent->amount) {
            swapData(node, parent);
            node = parent;
            parent = getParent(root, node);
        }
    }

    void heapifyDown(OrderNode* node) {
        while (node != NULL) {
            OrderNode* largest = node;
            if (node->left && node->left->amount > largest->amount) {
                largest = node->left;
            }
            if (node->right && node->right->amount > largest->amount) {
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
    OrderMaxHeap() {
        root = NULL;
    }

    void insert(int id, string name, double amt) {
        OrderNode* newNode = new OrderNode(id, name, amt);
        if (root == NULL) {
            root = newNode;
            return;
        }

        queue<OrderNode*> q;
        q.push(root);
        while (!q.empty()) {
            OrderNode* curr = q.front();
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

    double deleteMax() {
        if (root == NULL) return -1;

        double maxAmt = root->amount;

        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
            return maxAmt;
        }

        queue<OrderNode*> q;
        q.push(root);
        OrderNode* lastNode = NULL;
        while (!q.empty()) {
            lastNode = q.front();
            q.pop();
            if (lastNode->left) q.push(lastNode->left);
            if (lastNode->right) q.push(lastNode->right);
        }

        swapData(root, lastNode);
        OrderNode* parent = getParent(root, lastNode);
        if (parent->left == lastNode) parent->left = NULL;
        else parent->right = NULL;
        delete lastNode;

        heapifyDown(root);
        return maxAmt;
    }

    bool isEmpty() {
        return root == NULL;
    }
};

int main() {
    OrderMaxHeap orderHeap;

    orderHeap.insert(501, "Hamza", 4500.50);
    orderHeap.insert(502, "Sana", 1200.00);
    orderHeap.insert(503, "Omar", 8900.75);
    orderHeap.insert(504, "Maha", 3100.25);
    orderHeap.insert(505, "Raza", 6750.00);
    orderHeap.insert(506, "Kiran", 2400.00);

    vector<double> deletedAmounts;
    while (!orderHeap.isEmpty()) {
        deletedAmounts.push_back(orderHeap.deleteMax());
    }

    cout << "--- Sales Report: Order Amounts (Lowest to Highest) ---" << endl;
    for (int i = deletedAmounts.size() - 1; i >= 0; i--) {
        cout << "Rs. " << deletedAmounts[i] << endl;
    }

    return 0;
}
