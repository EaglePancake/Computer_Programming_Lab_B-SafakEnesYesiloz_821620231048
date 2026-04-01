#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

MoneyBundle* start = nullptr;

struct Customer {
    string customerName;
    string transactionType;
};

Customer customerQueue[5];
int front = -1;
int rear = -1;
int queueCount = 0;

void receive_money() {
    MoneyBundle* newBundle = new MoneyBundle;

    cout << "Enter Serial Number: ";
    getline(cin, newBundle->serialNumber);

    cout << "Enter Currency Type (TL, USD): ";
    getline(cin, newBundle->currencyType);

    cout << "Enter count of 100s bills: ";
    cin >> newBundle->billCounts[0];
    cout << "Enter count of 50s bills: ";
    cin >> newBundle->billCounts[1];
    cout << "Enter count of 20s bills: ";
    cin >> newBundle->billCounts[2];
    cin.ignore();

    newBundle->next = start;
    start = newBundle;

    cout << "[SUCCESS] Money bundle added to the top of the safe.\n";
}

void new_customer() {
    if (queueCount == 5) {
        cout << "[ERROR] The queue is full! Wait for transactions to process.\n";
        return;
    }

    if (front == -1)
        front = 0;

    rear = (rear + 1) % 5;

    cout << "Enter Customer Name: ";
    getline(cin, customerQueue[rear].customerName);

    cout << "Enter Transaction Type (Withdraw, Deposit): ";
    getline(cin, customerQueue[rear].transactionType);

    queueCount++;
    cout << "[SUCCESS] Customer added to the queue.\n";
}

void process_transaction() {
    if (queueCount == 0) {
        cout << "[ERROR] No customers in line to process.\n";
        return;
    }

    if (start == nullptr) {
        cout << "[ERROR] The safe is empty! Receive money bundles first.\n";
        return;
    }

    cout << "\n--- Processing Transaction ---" << endl;
    cout << "Serving Customer: " << customerQueue[front].customerName << " (" << customerQueue[front].transactionType << ")" << endl;
    cout << "Using Money Bundle: Serial " << start->serialNumber << " | " << start->currencyType << endl;

    front = (front + 1) % 5;
    queueCount--;
    if (queueCount == 0) {
        front = -1;
        rear = -1;
    }

    MoneyBundle* temp = start;
    start = start->next;
    delete temp;

    cout << "[SUCCESS] Transaction complete.\n";
}

void display_system() {
    cout << "\n--- SAFE (Money Bundles Stack) ---" << endl;
    MoneyBundle* tempStack = start;
    if (!tempStack) {
        cout << "  (Safe is currently empty)" << endl;
    } else {
        while (tempStack != nullptr) {
            cout << "  -> Serial: " << tempStack->serialNumber
                 << " | Currency: " << tempStack->currencyType
                 << " | 100s: " << tempStack->billCounts[0]
                 << ", 50s: " << tempStack->billCounts[1]
                 << ", 20s: " << tempStack->billCounts[2] << endl;
            tempStack = tempStack->next;
        }
    }

    cout << "\n--- WAITING LINE (Customer Queue) ---" << endl;
    if (queueCount == 0) {
        cout << "  (No customers waiting)" << endl;
    } else {
        int i = front;
        for (int count = 0; count < queueCount; count++) {
            cout << "  " << count + 1 << ". " << customerQueue[i].customerName
                 << " - " << customerQueue[i].transactionType << endl;
            i = (i + 1) % 5;
        }
    }
}

void clear() {
    MoneyBundle* current = start;

    while (current != nullptr) {
        MoneyBundle* temp = current;
        current = current->next;
        delete temp;
    }

    start = nullptr;
}

int main() {
    int choice = 0;

    while (choice != 5) {
        cout << "\n=== Bank Branch Management Menu ===" << endl;
        cout << "1. Receive Money (Push to Safe)" << endl;
        cout << "2. New Customer (Enqueue to Line)" << endl;
        cout << "3. Process Transaction (Pop and Dequeue)" << endl;
        cout << "4. Display Safe and Queue" << endl;
        cout << "5. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                receive_money();
                break;
            case 2:
                new_customer();
                break;
            case 3:
                process_transaction();
                break;
            case 4:
                display_system();
                break;
            case 5:
                clear();
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

    return 0;
}
