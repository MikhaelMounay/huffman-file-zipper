#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "../min_heap/MinHeap.h"
#include <string>
#include <unordered_map>
using namespace std;

class HuffmanTree {
private:
    MinHeap minHeap;
    unordered_map<char, string> codewords;

    // Helper Functions
    void generateCodes(HuffmanNode* node, string codeword);

public:
    // Default Constructor
    HuffmanTree();

    // Parameterized Constructor takes a map of characters and their frequencies to build Huffman Tree
    explicit HuffmanTree(unordered_map<char, int> freqMap);

    // Gets the Huffman Code for a given character c
    string getCodeword(char c);

    // Encode some string using this Huffman Tree
    // Warning: This will not build a dedicated tree for that input.
    // i.e., if the input is not the same input used to build the tree, probably it will give not the most efficient compression
    string encode(string inputStr);

    // Decode some encoded string based on this Huffman Tree
    string decode(string encodedStr);
};

#endif //HUFFMANTREE_H
