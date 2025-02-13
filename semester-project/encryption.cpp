#include "encryption.h"
#include <fstream>
#include <cctype>
#include <string>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

bool performCeaserCipher(string& content, bool encrypt) {
    int shift = encrypt ? 3 : -3;
    for (char& ch : content) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = static_cast<char>((ch - base + shift + 26) % 26 + base);
        }
    }
    return true;
}

bool encryptFile(const string& filename, bool encrypt) {
    ifstream infile(filename, ios::binary);
    if (!infile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    string content((istreambuf_iterator<char>(infile)), {});
    infile.close();

    if (performCeaserCipher(content, encrypt)) {
        fs::path filePath(filename);
        string outputFile = encrypt ? (filePath.parent_path() / ("encrypted_" + filePath.filename().string())).string()
                                    : (filePath.parent_path() / ("decrypted_" + filePath.filename().string())).string();
        ofstream outfile(outputFile, ios::binary);
        if (!outfile) {
            cerr << "Error: Unable to create output file " << outputFile << endl;
            return false;
        }
        outfile << content;
        outfile.close();
        cout << (encrypt ? "Encrypted: " : "Decrypted: ") << outputFile << endl;
        return true;
    }

    return false;
}

bool processFolder(const string& folderPath, bool encrypt) {
    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                encryptFile(entry.path().string(), encrypt);
            } else if (entry.is_directory()) {
                processFolder(entry.path().string(), encrypt);
            }
        }
        return true;
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}
