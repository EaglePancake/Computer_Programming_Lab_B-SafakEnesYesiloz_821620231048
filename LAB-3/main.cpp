#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* prev;
    Page* next;
};

Page* head = nullptr;
Page* current = nullptr;

void visit_page(string siteUrl, string siteTitle, int hour, int min, int sec) {
    Page* newPage = new Page;
    newPage->url = siteUrl;
    newPage->title = siteTitle;

    newPage->accessTime[0] = hour;
    newPage->accessTime[1] = min;
    newPage->accessTime[2] = sec;

    newPage->next = nullptr;
    newPage->prev = nullptr;

    if (current == nullptr) {
        head = newPage;
        current = newPage;
    } else {
        Page* temp = current->next;
        while (temp != nullptr) {
            Page* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }

        current->next = newPage;
        newPage->prev = current;
        current = newPage;
    }

    cout << "Visited: " << current->title << endl;
}

void go_back() {
    if (current != nullptr && current->prev != nullptr) {
        current = current->prev;
        cout << "Went back to: " << current->title << endl;
    } else {
        cout << "Can't go back. No previous history." << endl;
    }
}

void go_forward() {
    if (current != nullptr && current->next != nullptr) {
        current = current->next;
        cout << "Went forward to: " << current->title << endl;
    } else {
        cout << "Can't go forward. No next history." << endl;
    }
}

void show_history() {
    cout << "\n--- Browser History ---" << endl;
    if (head == nullptr) {
        cout << "History is empty." << endl;
    } else {
        Page* temp = head;
        while (temp != nullptr) {

            if (temp == current) {
                cout << "-> ";
            } else {
                cout << "   ";
            }

            cout << temp->title << " [" << temp->url << "] - Visited at: ";

            for (int i = 0; i < 3; i++) {
                if (temp->accessTime[i] < 10) {
                    cout << "0";
                }

                cout << temp->accessTime[i];

                if (i < 2) {
                    cout << ":";
                }
            }
            cout << endl;

            temp = temp->next;
        }
    }
    cout << "-----------------------" << endl;
}

void delete_current() {
    if (current != nullptr) {
        Page* toDelete = current;
        Page* prevPage = current->prev;
        Page* nextPage = current->next;

        if (prevPage != nullptr) {
            prevPage->next = nextPage;
        } else {
            head = nextPage;
        }

        if (nextPage != nullptr) {
            nextPage->prev = prevPage;
        }

        if (prevPage != nullptr) {
            current = prevPage;
        } else {
            current = nextPage;
        }

        cout << "Deleted page: " << toDelete->title << endl;
        delete toDelete;
    } else {
        cout << "Nothing to delete. History is empty." << endl;
    }
}

void clear() {
    Page* temp = head;
    while (temp != nullptr) {
        Page* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
    head = nullptr;
    current = nullptr;
}

int main() {
    string choiceString;
    bool isRunning = true;

    string siteUrl;
    string siteTitle;
    int hour, min, sec = 0;

    while (isRunning) {
        cout << "\nWeb Browser:" << endl;
        cout << "1. Visit Site" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. History" << endl;
        cout << "5. Delete Current From History" << endl;
        cout << "Type EXIT to exit." << endl;
        cout << "Your choice: ";
        getline(cin, choiceString);

        if (choiceString == "EXIT") {
            isRunning = false;

            cout << "Exiting..." << endl;
            clear();

            continue;
        }

        int choice = 0;
        choice = stoi(choiceString);

        switch (choice)
        {
            case 1:
                cout << "Enter site url: ";
                getline(cin, siteUrl);

                cout << "Enter site title: ";
                getline(cin, siteTitle);

                cout << "Enter hour: ";
                cin >> hour;
                cin.ignore();
                cout << "Enter minute: ";
                cin >> min;
                cin.ignore();
                cout << "Enter second: ";
                cin >> sec;
                cin.ignore();

                visit_page(siteUrl, siteTitle, hour, min, sec);
                break;
            case 2:
                go_back();
                break;
            case 3:
                go_forward();
                break;
            case 4:
                show_history();
                break;
            case 5:
                delete_current();
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

    return 0;
}
