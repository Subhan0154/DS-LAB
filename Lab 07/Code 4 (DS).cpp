#include <iostream>
using namespace std;

#define MAX 5

class Deque {
private:
    int arr[MAX];
    int front;
    int rear;
    int size;

public:
    Deque() {
        front = -1;
        rear = -1;
        size = 0;
    }

    bool isFull() {
        return size == MAX;
    }

    bool isEmpty() {
        return size == 0;
    }

    void insertFront(int val) {
        if (isFull()) {
            cout << "Deque Overflow!\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            front = (front - 1 + MAX) % MAX;
        }
        arr[front] = val;
        size++;
        cout << "Inserted " << val << " at Front.\n";
    }

    void insertRear(int val) {
        if (isFull()) {
            cout << "Deque Overflow!\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX;
        }
        arr[rear] = val;
        size++;
        cout << "Inserted " << val << " at Rear.\n";
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque Underflow!\n";
            return;
        }
        cout << "Removed " << arr[front] << " from Front.\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX;
        }
        size--;
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque Underflow!\n";
            return;
        }
        cout << "Removed " << arr[rear] << " from Rear.\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            rear = (rear - 1 + MAX) % MAX;
        }
        size--;
    }

    void display() {
        if (isEmpty()) {
            cout << "Deque is empty.\n";
            return;
        }
        cout << "Deque elements (Front to Rear): ";
        int i = front;
        for (int count = 0; count < size; count++) {
            cout << arr[i] << " ";
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    Deque dq;

    // Example sequence from task description[cite: 5]:
    // Insert 301 at rear, 302 at rear, 300 at front
    dq.insertRear(301);
    dq.insertRear(302);
    dq.insertFront(300);

    dq.display(); // Output order: Front 300 301 302 Rear[cite: 5]

    dq.deleteFront();
    dq.display();

    dq.deleteRear();
    dq.display();

    return 0;
}
