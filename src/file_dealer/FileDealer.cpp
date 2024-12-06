#include "FileDealer.h"

#include <string.h>

#include <cstdint>
#include <fstream>

#include <bcrypt.h>
// #include "../../external/bcrypt/include/bcrypt.h"

FileDealer::FileDealer(): decodedOriginFilePath("decodedInput.txt"),
                          encodedDestinationFilePath("encodedOutput.hfz"),
                          encodedOriginFilePath("encodedInput.hfz"),
                          decodedDestinationFilePath("decodedOutput.txt") {
}

FileDealer::FileDealer(string DecodedOriginFilePath,
                       string EncodedDestinationFilePath,
                       string EncodedOriginFilePath,
                       string DecodedDestinationFilePath):
    decodedOriginFilePath(std::move(DecodedOriginFilePath)),
    encodedDestinationFilePath(std::move(EncodedDestinationFilePath)),
    encodedOriginFilePath(std::move(EncodedOriginFilePath)),
    decodedDestinationFilePath(std::move(DecodedDestinationFilePath)) {
}

HuffmanTree* FileDealer::readOriginalDataText() {
    ifstream inFile(decodedOriginFilePath);
    if (!inFile.is_open()) {
        return nullptr;
    }

    string originalDecodedString;
    unordered_map<char, int> charFreqs;
    char c;

    while (inFile.get(c)) {
        charFreqs[c]++;
        originalDecodedString += c;
    }

    inFile.close();

    HuffmanTree* huffTree = new HuffmanTree(charFreqs, originalDecodedString);

    return huffTree;
}

bool FileDealer::writeEncodedDataBinary(const string& encodedString,
                                        const unordered_map<char, string>&
                                        codewords, string password) {
    ofstream outFile(encodedDestinationFilePath, ios::binary);
    if (!outFile.is_open()) {
        return false;
    }

    // Writing the hash of the password of the file
    char isPasswordProtected = '0';
    if (password.empty()) {
        outFile.write(&isPasswordProtected, sizeof(char));
    } else {
        isPasswordProtected = '1';
        outFile.write(&isPasswordProtected, sizeof(char));

        string passwordHash = bcrypt::generateHash(password);

        // Writing the length of the hash
        size_t passwordHashLength = passwordHash.size();
        outFile.write(reinterpret_cast<const char*>(&passwordHashLength),
                      sizeof(passwordHashLength));

        // Writing the hash of the password
        for (size_t i = 0; i < passwordHash.size(); i++) {
            outFile.write(&passwordHash[i], sizeof(char));
        }
    }

    // Writing size of codewords map
    size_t codewordsSize = codewords.size();
    outFile.write(reinterpret_cast<const char*>(&codewordsSize),
                  sizeof(codewordsSize));

    // Writing the characters, their codewordLength, and their codewords
    for (auto it = codewords.begin(); it != codewords.end(); it++) {
        outFile.write(&(it->first), sizeof(it->first)); // The character

        uint8_t codewordLength = it->second.length();
        outFile.write(reinterpret_cast<const char*>(&codewordLength),
                      sizeof(codewordLength)); // The length of the codeword

        // The codeword (the bits of the codeword of the character)
        for (int i = 0; i < codewordLength; i++) {
            outFile.write(&(it->second[i]), sizeof(it->second[i]));
        }
    }

    // Writing the length of the encoded string
    uint64_t encodedStringLength = encodedString.length();
    outFile.write(reinterpret_cast<const char*>(&encodedStringLength),
                  sizeof(encodedStringLength));

    // Writing the encoded string (the bits of the encoded string consisting of codewords)
    // Writing the encoded string (bit by bit)
    char currentByte = 0;
    int bitIndex = 0;
    for (int i = 0; i < encodedStringLength; i++) {
        currentByte |= (encodedString[i] - '0') << (7 - bitIndex);
        bitIndex++;

        if (bitIndex == 8) {
            outFile.write(&currentByte, sizeof(currentByte));
            currentByte = 0;
            bitIndex = 0;
        }
    }

    // Write any remaining bits with padding of 0s to fill the remaining bits
    if (bitIndex > 0) {
        for (int i = bitIndex; i < 8; i++) {
            currentByte |= 0 << (7 - i);
        }
        outFile.write(&currentByte, sizeof(currentByte));
    }

    outFile.close();
    return true;
}

HuffmanTree* FileDealer::readEncodedDataBinary(string password) {
    ifstream inFile(encodedOriginFilePath, ios::binary);
    if (!inFile.is_open()) {
        return nullptr;
    }

    // Reading the hash of the password of the file
    char isPasswordProtected;
    inFile.read(&isPasswordProtected, sizeof(char));

    if (isPasswordProtected == '1') {
        // Reading the length of the hash
        size_t passwordHashLength;
        inFile.read(reinterpret_cast<char*>(&passwordHashLength),
                    sizeof(passwordHashLength));

        // Reading the hash of the password
        string passwordHash;
        for (size_t i = 0; i < passwordHashLength; i++) {
            char bit;
            inFile.read(&bit, sizeof(bit));
            passwordHash += bit;
        }

        if (!bcrypt::validatePassword(password, passwordHash)) {
            return nullptr;
        }
    }

    // Reading the size of codewords map
    size_t codewordsSize;
    inFile.read(reinterpret_cast<char*>(&codewordsSize), sizeof(codewordsSize));

    // Reading the characters, their codewordLength, and their codewords
    unordered_map<char, string> codewords;
    for (size_t i = 0; i < codewordsSize; i++) {
        char character;
        inFile.read(&character, sizeof(character)); // The character

        uint8_t codewordLength;
        inFile.read(reinterpret_cast<char*>(&codewordLength),
                    sizeof(codewordLength)); // The length of the codeword

        // The codeword (the bits of the codeword of the character)
        string codeword;
        for (uint8_t j = 0; j < codewordLength; j++) {
            char bit;
            inFile.read(&bit, sizeof(bit));
            codeword += bit;
        }

        codewords[character] = codeword;
    }

    // Reading the length of the encoded string
    uint64_t encodedStringLength;
    inFile.read(reinterpret_cast<char*>(&encodedStringLength),
                sizeof(encodedStringLength));

    // Reading the encoded string (the bits of the encoded string consisting of codewords)
    string encodedString;
    char currentByte;

    int totalBitsRead = 0;
    uint64_t numberOfBytes = (encodedStringLength / 8) + (
                                 encodedStringLength % 8 ? 1 : 0);
    for (int i = 0; i < numberOfBytes; i++) {
        inFile.read(&currentByte, sizeof(currentByte));

        for (int j = 7; j >= 0; j--) {
            if (totalBitsRead < encodedStringLength) {
                // To avoid including the padding in the encodedString
                char bit = (currentByte >> j) & 1;
                encodedString += bit + '0';
                totalBitsRead++;
            }
        }
    }

    HuffmanTree* huffTree = new HuffmanTree(codewords, encodedString);

    inFile.close();
    return huffTree;
}

bool FileDealer::writeEncodedDataText(const string& encodedString,
                                      const unordered_map<char, string>&
                                      codewords) {
    ofstream outFile(encodedDestinationFilePath);
    if (!outFile.is_open()) {
        return false;
    }

    // Writing size of codewords map
    size_t codewordsSize = codewords.size();
    outFile << codewordsSize << ";";

    // Writing the characters, their codewordLength, and their codewords
    for (auto it = codewords.begin(); it != codewords.end(); it++) {
        outFile << it->first << "|" << it->second.length() << "|" << it->second
            << ",";
    }
    outFile << ";";

    // Writing the length of the encoded string
    outFile << encodedString.length() << ",";

    // Writing the encoded string (the bits of the encoded string consisting of codewords)
    outFile << encodedString << "\n";

    outFile.close();
    return true;
}

HuffmanTree* FileDealer::readEncodedDataText() {
    ifstream inFile(encodedOriginFilePath);
    if (!inFile.is_open()) {
        return nullptr;
    }

    char c;
    string inputWord;

    // Reading the size of codewords map
    while (inFile.get(c)) {
        if (c != ';') {
            inputWord += c;
        } else {
            break;
        }
    }

    // int codewordsSize = stoi(inputWord);
    inputWord = string("");

    // Reading the characters, their codewordLength, and their codewords
    unordered_map<char, string> codewords;
    char character;

    int position = 0;
    while (inFile.get(c)) {
        if (c == ',' || c == ';') {
            if (!inputWord.empty()) {
                codewords[character] = inputWord;
            }

            inputWord = string("");
            position = 0;

            if (c == ',') {
                continue;
            } else {
                break;
            }
        }

        if (c == '|') {
            inputWord = string("");
            position++;
            continue;
        }

        if (position == 0) {
            character = c;
        } else if (position == 1) {
            continue;
        } else if (position == 2) {
            inputWord += c;
        }
    }

    inputWord = string("");

    // Reading the length of the encoded string
    while (inFile.get(c)) {
        if (c == ',') {
            break;
        }

        inputWord += c;
    }

    // int encodedStringLength = stoi(inputWord);

    // Reading the encoded string (the bits of the encoded string consisting of codewords)
    string encodedString;
    getline(inFile, encodedString);

    HuffmanTree* huffTree = new HuffmanTree(codewords, encodedString);

    inFile.close();
    return huffTree;
}


bool FileDealer::writeDecodedDataText(const string& decodedString) {
    ofstream outFile(decodedDestinationFilePath);
    if (!outFile.is_open()) {
        return false;
    }

    outFile << decodedString;

    outFile.close();
    return true;
}

void FileDealer::setDecodedOriginFilePath(string filePath) {
    decodedOriginFilePath = std::move(filePath);
}

void FileDealer::setEncodedDestinationFilePath(string filePath) {
    encodedDestinationFilePath = std::move(filePath);
}

void FileDealer::setEncodedOriginFilePath(string filePath) {
    encodedOriginFilePath = std::move(filePath);
}

void FileDealer::setDecodedDestinationFilePath(string filePath) {
    decodedDestinationFilePath = std::move(filePath);
}

string FileDealer::getDecodedOriginFilePath() {
    return decodedOriginFilePath;
}

string FileDealer::getEncodedDestinationFilePath() {
    return encodedDestinationFilePath;
}

string FileDealer::getEncodedOriginFilePath() {
    return encodedOriginFilePath;
}

string FileDealer::getDecodedDestinationFilePath() {
    return decodedDestinationFilePath;
}
