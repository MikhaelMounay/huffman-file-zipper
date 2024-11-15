#include "FileDealer.h"

#include <cstdint>
#include <fstream>
#include <sstream>

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
                                        codewords) {
    ofstream outFile(encodedDestinationFilePath, ios::binary);
    if (!outFile.is_open()) {
        return false;
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
    for (int i = 0; i < encodedStringLength; i++) {
        outFile.write(&(encodedString[i]), sizeof(encodedString[i]));
    }

    outFile.close();
    return true;
}

HuffmanTree* FileDealer::readEncodedDataBinary() {
    ifstream inFile(encodedOriginFilePath, ios::binary);
    if (!inFile.is_open()) {
        return nullptr;
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
    for (uint64_t i = 0; i < encodedStringLength; i++) {
        char bit;
        inFile.read(&bit, sizeof(bit));
        encodedString += bit;
    }

    HuffmanTree* huffTree = new HuffmanTree(codewords, encodedString);

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

    int codewordsSize = stoi(inputWord);
    inputWord = "";

    // Reading the characters, their codewordLength, and their codewords
    unordered_map<char, string> codewords;
    char character;

    int position = 0;
    while (inFile.get(c)) {
        if (c == ',' || c == ';') {
            if (!inputWord.empty()) {
                codewords[character] = inputWord;
            }

            inputWord = "";
            position = 0;

            if (c == ',') {
                continue;
            } else {
                break;
            }
        }

        if (c == '|') {
            inputWord = "";
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

    inputWord = "";

    // Reading the length of the encoded string
    while (inFile.get(c)) {
        if (c == ',') {
            break;
        }

        inputWord += c;
    }

    // int encodedStringLength = stoi(inputWord);
    inputWord = "";

    // Reading the encoded string (the bits of the encoded string consisting of codewords)
    string encodedString;
    getline(inFile, encodedString);

    HuffmanTree* huffTree = new HuffmanTree(codewords, encodedString);

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
