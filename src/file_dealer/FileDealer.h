#ifndef FILEDEALER_H
#define FILEDEALER_H

#include "../huffman_tree/HuffmanTree.h"

class FileDealer {
public:
    // Default Constructor
    FileDealer();

    void writeEncodedDataBinary(string filePath);

    HuffmanTree* readEncodedDataAndCreateHuffmanTree(string filePath);
};

#endif //FILEDEALER_H
