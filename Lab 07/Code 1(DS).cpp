#include <iostream>
using namespace std;

#define MAX_SIZE 5

class BankQueue {
private:
    int arr[MAX_SIZE];
    int front;
    int rear;

public:
    BankQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return rear == MAX_SIZE - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot add customer token " << token << ".\n";
            return;
        }
        if (front == -1) front = 0;
        rear++;
        arr[rear] = token;
        cout << "Customer token " << token << " added to the queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! No waiting customers to serve.\n";
            return;
        }
        cout << "Serving customer with token: " << arr[front] << endl;
        front++;
        if (front > rear) {
            front = -1;
            rear = -1;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "No waiting customers in the queue.\n";
            return;
        }
        cout << "Waiting Customers: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void countWaiting() {
        if (isEmpty()) {
            cout << "Number of waiting customers: 0\n";
        } else {
            cout << "Number of waiting customers: " << (rear - front + 1) << endl;
        }
    }
};

int main() {
    BankQueue bQueue;

    // Insert customer tokens[cite: 3]
    bQueue.enqueue(101);
    bQueue.enqueue(102);
    bQueue.enqueue(103);

    bQueue.display();
    bQueue.countWaiting();

    // Serve customer[cite: 3]
    bQueue.dequeue();

    bQueue.display();
    bQueue.countWaiting();

    return 0;
}
