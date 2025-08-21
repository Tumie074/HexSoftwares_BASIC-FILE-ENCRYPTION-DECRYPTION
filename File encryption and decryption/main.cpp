#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to encrypt text using Caesar cipher
string encryptText(const string& text, int shift) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
        result += c;
    }

    return result;
}

// Function to decrypt text using Caesar cipher
string decryptText(const string& text, int shift) {
    return encryptText(text, 26 - (shift % 26));
}

// Function to process file (encrypt or decrypt)
void processFile(const string& inputFile, const string& outputFile, int shift, bool encrypt) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile) {
        cout << "Error: Cannot open input file '" << inputFile << "'" << endl;
        return;
    }

    if (!outFile) {
        cout << "Error: Cannot create output file '" << outputFile << "'" << endl;
        inFile.close();
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (encrypt) {
            outFile << encryptText(line, shift) << endl;
        } else {
            outFile << decryptText(line, shift) << endl;
        }
    }

    inFile.close();
    outFile.close();

    cout << "File processed successfully!" << endl;
    cout << (encrypt ? "Encrypted" : "Decrypted") << " file saved as: " << outputFile << endl;
}

int main() {
    int choice;
    string inputFile, outputFile;
    int shift;

    cout << "=== FILE ENCRYPTION/DECRYPTION TOOL ===" << endl;
    cout << "Using Caesar Cipher Algorithm" << endl;
    cout << "=======================================" << endl;

    while (true) {
        cout << "\nOptions:" << endl;
        cout << "1. Encrypt a file" << endl;
        cout << "2. Decrypt a file" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        }

        if (choice != 1 && choice != 2) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        cout << "Enter input filename: ";
        getline(cin, inputFile);

        cout << "Enter output filename: ";
        getline(cin, outputFile);

        cout << "Enter shift value (1-25): ";
        cin >> shift;
        cin.ignore();

        // Validate shift value
        if (shift < 1 || shift > 25) {
            cout << "Invalid shift value. Please enter a value between 1 and 25." << endl;
            continue;
        }

        if (choice == 1) {
            processFile(inputFile, outputFile, shift, true);
        } else {
            processFile(inputFile, outputFile, shift, false);
        }
    }

    return 0;
}
