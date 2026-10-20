#include <iostream>
using namespace std;

#define SIZE 4

class CircularQueue {
private:
    int arr[SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int packetID) {
        if (isFull()) {
            cout << "Buffer Full! Cannot accept packet " << packetID << ".\n";
            return;
        }
        if (front == -1) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }
        arr[rear] = packetID;
        cout << "Packet " << packetID << " added to buffer.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Buffer Empty! No packets to transmit.\n";
            return;
        }
        cout << "Transmitting packet: " << arr[front] << endl;
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "No packets waiting in buffer.\n";
            return;
        }
        cout << "Waiting Packets: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

int main() {
    CircularQueue cq;

    cq.enqueue(201);
    cq.enqueue(202);
    cq.enqueue(203);
    cq.display();

    // Transmit oldest packet[cite: 3]
    cq.dequeue();
    cq.display();

    // Reuse slot
    cq.enqueue(204);
    cq.enqueue(205);
    cq.display();

    return 0;
}
