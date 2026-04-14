#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include<cstring>
#include <algorithm>

using namespace std;

// COLORS
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"

// UTIL
void clearScreen() {
    system("cls");
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// LOGIN
bool login() {
    string user, pass;

    cout << CYAN << "====== LOGIN SYSTEM ======\n" << RESET;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "1234") {
        cout << GREEN << "Login successful!\n" << RESET;
        return true;
    } else {
        cout << RED << "Invalid credentials!\n" << RESET;
        return false;
    }
}

// TIME
string getTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt)-1] = '\0'; // remove newline
    return string(dt);
}

// MENU
void showMenu() {
    cout << CYAN;
    cout << "=====================================\n";
    cout << "       NOTES MANAGER SYSTEM           \n";
    cout << "=====================================\n";
    cout << RESET;

    cout << YELLOW;
    cout << " 1. Add Note\n";
    cout << " 2. View Notes\n";
    cout << " 3. Search Note\n";
    cout << " 4. Delete Note\n";
    cout << " 5. Dashboard\n";
    cout << " 6. Exit\n";
    cout << RESET;

    cout << "=====================================\n";
    cout << "Enter your choice: ";
}

// ADD NOTE
void addNote() {
    ofstream file("notes.txt", ios::app);
    string note, category;

    cout << "Enter category (Work/Personal/Study): ";
    cin >> category;

    cout << "Enter your note: ";
    cin.ignore();
    getline(cin, note);

    file << "[" << category << "] [" << getTime() << "] " << note << endl;
    file.close();

    cout << GREEN << "\nNote saved!\n" << RESET;
}

// VIEW NOTES
void viewNotes() {
    ifstream file("notes.txt");
    string note;
    int count = 1;

    cout << CYAN << "========== ALL NOTES ==========\n" << RESET;

    while (getline(file, note)) {
        cout << count++ << ". " << note << endl;
    }

    if (count == 1) {
        cout << RED << "No notes found.\n" << RESET;
    }

    file.close();
}

// SEARCH
void searchNote() {
    ifstream file("notes.txt");
    string note, keyword;
    bool found = false;

    cout << "Enter keyword or category: ";
    cin >> keyword;

    cout << CYAN << "\n========== SEARCH RESULTS ==========\n" << RESET;

    while (getline(file, note)) {
        if (note.find(keyword) != string::npos) {
            cout << GREEN << note << RESET << endl;
            found = true;
        }
    }

    if (!found) {
        cout << RED << "No match found.\n" << RESET;
    }

    file.close();
}

// DELETE NOTE
void deleteNote() {
    ifstream file("notes.txt");
    vector<string> notes;
    string note;
    int index;

    while (getline(file, note)) {
        notes.push_back(note);
    }
    file.close();

    if (notes.empty()) {
        cout << RED << "No notes to delete.\n" << RESET;
        return;
    }

    cout << CYAN << "========== NOTES ==========\n" << RESET;

    for (int i = 0; i < notes.size(); i++) {
        cout << i + 1 << ". " << notes[i] << endl;
    }

    cout << "\nEnter note number to delete: ";
    cin >> index;

    if (index < 1 || index > notes.size()) {
        cout << RED << "Invalid choice!\n" << RESET;
        return;
    }

    ofstream outFile("notes.txt");

    for (int i = 0; i < notes.size(); i++) {
        if (i != index - 1) {
            outFile << notes[i] << endl;
        }
    }

    outFile.close();

    cout << GREEN << "\nNote deleted!\n" << RESET;
}

// DASHBOARD
void viewStats() {
    ifstream file("notes.txt");
    vector<string> notes;
    string note;

    int total = 0;
    int work = 0, personal = 0, study = 0;

    while (getline(file, note)) {
        notes.push_back(note);
        total++;

        if (note.find("[Work]") != string::npos) work++;
        else if (note.find("[Personal]") != string::npos) personal++;
        else if (note.find("[Study]") != string::npos) study++;
    }

    file.close();

    cout << CYAN;
    cout << "========================================\n";
    cout << "         SYSTEM DASHBOARD                \n";
    cout << "========================================\n";
    cout << RESET;

    cout << "\nSTATISTICS\n";
    cout << "----------------------------------------\n";
    cout << "Total Notes     : " << total << endl;
    cout << "Work Notes      : " << work << endl;
    cout << "Personal Notes  : " << personal << endl;
    cout << "Study Notes     : " << study << endl;

    cout << "\nNOTE DISTRIBUTION\n";
    cout << "----------------------------------------\n";

    cout << "Work     : ";
    for (int i = 0; i < work; i++) cout << "#";
    cout << endl;

    cout << "Personal : ";
    for (int i = 0; i < personal; i++) cout << "#";
    cout << endl;

    cout << "Study    : ";
    for (int i = 0; i < study; i++) cout << "#";
    cout << endl;

    cout << "\nRECENT ACTIVITY\n";
    cout << "----------------------------------------\n";

    int start = max(0, (int)notes.size() - 3);
    for (int i = start; i < notes.size(); i++) {
        cout << "- " << notes[i] << endl;
    }

    if (notes.empty()) {
        cout << "No recent activity.\n";
    }

    cout << "\nSYSTEM STATUS\n";
    cout << "----------------------------------------\n";
    cout << "System Running   : OK\n";
    cout << "Database File    : Connected\n";
    cout << "Notes Loaded     : " << total << endl;

    cout << "\n========================================\n";
}

// MAIN
int main() {

    while (!login()) {
        cout << "Try again...\n\n";
    }

    int choice;

    while (true) {
        clearScreen();
        showMenu();

        cin >> choice;
        clearScreen();

        switch (choice) {
            case 1: addNote(); break;
            case 2: viewNotes(); break;
            case 3: searchNote(); break;
            case 4: deleteNote(); break;
            case 5: viewStats(); break;
            case 6:
                cout << GREEN << "Exiting...\n" << RESET;
                return 0;
            default:
                cout << RED << "Invalid choice!\n" << RESET;
        }

        pauseScreen();
    }

    return 0;
}
// g++ notes.cpp -o notes
// ./notes.exe