#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "../min_heap/MinHeap.h"
#include <string>
#include <unordered_map>
using namespace std;

class HuffmanTree {
private:
    HuffmanNode* huffRoot;
    MinHeap minHeap;
    unordered_map<char, string> codewordsMap;
    string decodedData;
    string encodedData;

    // Helper Functions

    // A function to build Huffman Tree given a map of characters and their frequencies
    void buildTreeFreqMap(unordered_map<char, int> freqMap);

    // A function to build Huffman Tree given a map of characters and their frequencies
    void buildTreeCodewordsMap();

    // A function to generate codewords used after building the tree
    void generateCodes(HuffmanNode* node, string codeword);

    // Encodes the input data using this Huffman Tree
    string encode();

    // Gets the original/decoded data based on this Huffman Tree
    string decode();

public:
    // Default Constructor
    HuffmanTree();

    // Parameterized constructor that takes a map of characters and their frequencies to build Huffman Tree
    explicit HuffmanTree(unordered_map<char, int> freqMap);

    // Parameterized constructor that takes input data as string to encode
    explicit HuffmanTree(string inputData);

    explicit HuffmanTree(unordered_map<char, string> codewordsMap);

    // Gets the Huffman Code for a given character c
    string getCodeword(char c);

    // Sets the decoded data and encodes it based on this Huffman Tree
    void setDecodedDataAndEncode(string originalInput);

    // Sets the encoded data and decodes it based on this Huffman Tree
    void setEncodedDataAndDecode(string encodedData);

    // Gets the data after encoding using this Huffman Tree
    string getEncodedData();

    // Gets the original/decoded data based on this Huffman Tree
    string getDecodedData();
};

#endif //HUFFMANTREE_H
