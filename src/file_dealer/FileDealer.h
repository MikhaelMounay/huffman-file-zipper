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

    // Reads a normal data file from decodedFilePath
    // TODO: void readOriginalData();

    // Takes encoded string and its accompanying map of codewords and save them to the binary file encodedFilePath
    bool writeEncodedDataBinary(string encodedString,
                                const unordered_map<char, string>& codewords);

    // Reads encoded string and its accompanying map of codewords from the binary file encodedFilePath and constructs a HuffmanTree with them
    HuffmanTree* readEncodedDataBinary();

    // Writes a normal data file to decodedFilePath
    // TODO: void writeDecodedData();

    // Setters
    void setDecodedFilePath(string filePath);
    void setEncodedFilePath(string filePath);

    // Getters
    string getEncodedFilePath();
    string getDecodedFilePath();
};

#endif //FILEDEALER_H
