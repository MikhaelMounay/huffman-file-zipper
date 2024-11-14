#ifndef FILEDEALER_H
#define FILEDEALER_H

#include "../huffman_tree/HuffmanTree.h"

class FileDealer {
private:
    string decodedOriginFilePath;
    string encodedDestinationFilePath;

    string encodedOriginFilePath;
    string decodedDestinationFilePath;

public:
    // Default constructor
    FileDealer();

    // Parameterized constructor that takes the paths of the encoded and decoded files
    FileDealer(string DecodedOriginFilePath,
               string EncodedDestinationFilePath,
               string EncodedOriginFilePath,
               string DecodedDestinationFilePath);

    // Reads a normal data file from decodedFilePath
    // (Compression)
    HuffmanTree* readOriginalDataText();

    // Takes encoded string and its accompanying map of codewords and save them to the binary file encodedFilePath
    // (Compression)
    bool writeEncodedDataBinary(const string& encodedString,
                                const unordered_map<char, string>& codewords);

    // Reads encoded string and its accompanying map of codewords from the binary file encodedFilePath and constructs a HuffmanTree with them
    // (Decompression)
    HuffmanTree* readEncodedDataBinary();

    // Writes a normal data file to decodedFilePath
    // (Decompression)
    bool writeDecodedDataText(const string& encodedString);

    // Setters
    void setDecodedOriginFilePath(string filePath);
    void setEncodedDestinationFilePath(string filePath);
    void setEncodedOriginFilePath(string filePath);
    void setDecodedDestinationFilePath(string filePath);

    // Getters
    string getDecodedOriginFilePath();
    string getEncodedDestinationFilePath();
    string getEncodedOriginFilePath();
    string getDecodedDestinationFilePath();
};

#endif //FILEDEALER_H
