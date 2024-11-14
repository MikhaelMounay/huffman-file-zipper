#ifndef FILEDEALER_H
#define FILEDEALER_H

#include "../huffman_tree/HuffmanTree.h"

class FileDealer {
private:
    string decodedFilePath;
    string encodedFilePath;

public:
    // Default constructor
    FileDealer();

    // Parameterized constructor that takes the paths of the encoded and decoded files
    FileDealer(string DecodedFilePath, string EncodedFilePath);

    // TODO: void readOriginalData();
    // TODO: void writeDecodedData();

    bool writeEncodedDataBinary(string encodedString,
                                unordered_map<char, string> codewords);

    HuffmanTree* readEncodedDataBinary();

    // Setters
    void setDecodedFilePath(string filePath);
    void setEncodedFilePath(string filePath);

    // Getters
    string getEncodedFilePath();
    string getDecodedFilePath();
};

#endif //FILEDEALER_H
