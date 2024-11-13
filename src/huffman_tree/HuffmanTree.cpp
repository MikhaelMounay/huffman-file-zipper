#include "HuffmanTree.h"

#include <iostream>


HuffmanTree::HuffmanTree() {
    MinHeap minHeap = MinHeap();
}

HuffmanTree::HuffmanTree(unordered_map<char, int> freqMap) {
    buildTree(freqMap);
}

HuffmanTree::HuffmanTree(string inputData) {
    unordered_map<char, int> charFreqs;

    for (int i = 0; i < inputData.size(); i++) {
        charFreqs[inputData[i]] += 1;
    }

    buildTree(charFreqs);
}

void HuffmanTree::buildTree(unordered_map<char, int> freqMap) {
    for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
        minHeap.insert(it->first, it->second);
    }

    while (minHeap.getSize() != 1) {
        HuffmanNode* left = minHeap.extractMin();
        HuffmanNode* right = minHeap.extractMin();

        HuffmanNode* top = new HuffmanNode(static_cast<char>(0),
                                           left->frequency + right->frequency);
        minHeap.insert(top);

        top->left = left;
        top->right = right;
    }

    generateCodes(minHeap.getMin(), "");
    encode();
    decode(); // TODO: This line is just for testing purposes
}


void HuffmanTree::generateCodes(HuffmanNode* root, string codeword) {
    if (!root) {
        return;
    }

    if (root->data != static_cast<char>(0)) {
        codewords[root->data] = std::move(codeword);
        // Using std::move just to avoid unnecessary copies
    }

    generateCodes(root->left, codeword + "0");
    generateCodes(root->right, codeword + "1");
}

string HuffmanTree::getCodeword(char c) {
    return codewords[c];
}

string HuffmanTree::encode() {
    string encodedString;

    for (int i = 0; i < decodedData.size(); i++) {
        encodedString += getCodeword(decodedData[i]);
    }

    return encodedString;
}

string HuffmanTree::decode() {
    HuffmanNode* current = minHeap.getMin();
    string decodedString;

    for (int i = 0; i < encodedData.size(); i++) {
        if (encodedData[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedString += current->data;
            current = minHeap.getMin();
        }
    }

    return decodedString;
}

void HuffmanTree::setDecodedDataAndEncode(string originalInput) {
    decodedData = std::move(originalInput);
    encodedData = encode();
}

void HuffmanTree::setEncodedDataAndDecode(string encodedData) {
    this->encodedData = std::move(encodedData);
    decodedData = decode();
}

string HuffmanTree::getEncodedData() {
    return encodedData;
}

string HuffmanTree::getDecodedData() {
    return decodedData;
}