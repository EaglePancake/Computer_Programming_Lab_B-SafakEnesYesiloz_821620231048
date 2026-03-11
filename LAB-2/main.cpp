#include <iostream>
#include <string>

using namespace std;

struct Node {
    string songTitle;
    Node* next;
};


void add_song(Node*& head, string name) {
    Node* newNode = new Node;
    newNode->songTitle = name;
    newNode->next = head;
    head = newNode;
    cout << "Song " << name << " added to the top of the list!" << endl;
}

void search_song(Node* head, string name) {
    if (head == nullptr) {
        cout << "The playlist is empty." << endl;
        return;
    }

    Node* current = head;
    int count = 1;

    while (current != nullptr) {
        if (current->songTitle == name) {
            cout << "The song " << name << " was found at index " << count << endl;
            return;
        }
        current = current->next;
        count++;
    }

    cout << "Couldn't find " << name << " in the playlist." << endl;
}

void listSongs(Node* head) {
    if (head == nullptr) {
        cout << "The playlist is empty." << endl;
        return;
    }

    cout << "Your playlist:" << endl;

    Node* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << count << "- " << current->songTitle << endl;
        current = current->next;
        count++;
    }
}

void clear(Node* head){
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* playlistStart = nullptr;
    int choice = 0;
    string songName;

    while (choice != 4) {
        cout << "\nMusic Playlist Menu:" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Search Song" << endl;
        cout << "3. List Songs" << endl;
        cout << "4. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                cout << "Enter song title: ";
                getline(cin, songName);
                add_song(playlistStart, songName);
                break;
            case 2:
                cout << "Enter song title: ";
                getline(cin, songName);
                search_song(playlistStart, songName);
                break;
            case 3:
                listSongs(playlistStart);
                break;
            case 4:
                cout << "Exiting..." << endl;
                clear(playlistStart);
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

    return 0;
}
