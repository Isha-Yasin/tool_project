#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
using namespace std;

// Encrypts or decrypts a file
bool encryptFile(const string& filename, bool encrypt);

// Processes a folder and applies encryption or decryption recursively
bool processFolder(const string& folderPath, bool encrypt);

#endif  // ENCRYPTION_H