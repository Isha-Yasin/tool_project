#include <iostream>
#include "encryption.h"
#include <filesystem>
using namespace std;
int main() {
    do {
        string path;
        char mode;

        cout << "Enter the file or folder path: ";
        getline(cin >> ws, path);

        cout << "Encrypt (e) or decrypt (d)? ";
        cin >> mode;

        bool success = false;
        if (mode == 'e' || mode == 'E') {
            success = encryptFile(path, true) || processFolder(path, true);
        } else if (mode == 'd' || mode == 'D') {
            success = encryptFile(path, false) || processFolder(path, false);
        } else {
            cerr << "Invalid mode! Please enter 'e' for encryption or 'd' for decryption." << endl;
        }

        if (success) {
            cout << "Operation completed successfully!" << endl;
        } else {
            cerr << "Operation failed!" << endl;
        }

        // Ask if the user wants to run again
        char choice;
        do {
            cout << "Do you want to run again? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                break;
            } else if (choice == 'n' || choice == 'N') {
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            } else {
                cerr << "Invalid input! Please enter 'y' or 'n'." << endl;
            }
        } while (true);
    } while (true);

    return 0;
}
