#include <iostream>
#include <string>
using namespace std;

#define MAX 5

struct Patient {
    string id;
    int priority; // Lower value = higher urgency[cite: 4]
};

class PriorityQueue {
private:
    Patient arr[MAX];
    int count;

public:
    PriorityQueue() {
        count = 0;
    }

    bool isFull() {
        return count == MAX;
    }

    bool isEmpty() {
        return count == 0;
    }

    void enqueue(string id, int priority) {
        if (isFull()) {
            cout << "Queue is full! Cannot register patient " << id << ".\n";
            return;
        }

        Patient p = {id, priority};
        
        // Insert elements sorted by priority (Ascending order of priority number)
        int i;
        for (i = count - 1; i >= 0; i--) {
            if (arr[i].priority > priority) {
                arr[i + 1] = arr[i];
            } else {
                break;
            }
        }
        arr[i + 1] = p;
        count++;
        cout << "Patient " << id << " (Priority " << priority << ") registered.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Emergency Queue is empty! No patients to treat.\n";
            return;
        }
        cout << "Treating Patient " << arr[0].id << " (Priority " << arr[0].priority << ").\n";
        for (int i = 0; i < count - 1; i++) {
            arr[i] = arr[i + 1];
        }
        count--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No patients waiting in the queue.\n";
            return;
        }
        cout << "\nWaiting Patients List:\n";
        for (int i = 0; i < count; i++) {
            cout << "Patient ID: " << arr[i].id << " | Priority: " << arr[i].priority << endl;
        }
        cout << endl;
    }
};

int main() {
    PriorityQueue pq;

    pq.enqueue("P101", 3);
    pq.enqueue("P102", 1); // Highest priority[cite: 4]
    pq.enqueue("P103", 2);

    pq.display();

    // Highest priority patient P102 will be treated first[cite: 4]
    pq.dequeue();
    pq.display();

    return 0;
}
