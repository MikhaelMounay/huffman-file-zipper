#include "HuffmanTree.h"

HuffmanTree::HuffmanTree() {
    MinHeap minHeap = MinHeap();
}

HuffmanTree::HuffmanTree(unordered_map<char, int> freqMap) {
    MinHeap minHeap = MinHeap(freqMap.size());
    buildTreeFreqMap(freqMap);
}

HuffmanTree::HuffmanTree(string inputData) {
    unordered_map<char, int> freqMap;

    for (int i = 0; i < inputData.size(); i++) {
        freqMap[inputData[i]] += 1;
    }

    MinHeap minHeap = MinHeap(freqMap.size());
    buildTreeFreqMap(freqMap);
}

HuffmanTree::HuffmanTree(unordered_map<char, string> codewordsMap) {
    this->codewordsMap = std::move(codewordsMap);
    buildTreeCodewordsMap();
}

void HuffmanTree::buildTreeFreqMap(unordered_map<char, int> freqMap) {
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

    huffRoot = minHeap.getMin();
    generateCodes(huffRoot, "");
    encode();
    decode(); // TODO: This line is just for testing purposes
}

void HuffmanTree::buildTreeCodewordsMap() {
    unordered_map<string, HuffmanNode*> prefixTree;
    HuffmanNode* root = nullptr;

    for (auto it = codewordsMap.begin(); it != codewordsMap.end(); it++) {
        char character = it->first;
        string codeword = it->second;

        HuffmanNode* current = root;
        for (int i = 0; i < codeword.length(); i++) {
            if (current == nullptr) {
                current = new HuffmanNode();
            }

            if (codeword[i] == '0') {
                if (current->left == nullptr) {
                    current->left = new HuffmanNode();
                }
                current = current->left;
            } else if (codeword[i] == '1') {
                if (current->right == nullptr) {
                    current->right = new HuffmanNode();
                }
                current = current->right;
            }
        }

        current->data = character;
    }

    huffRoot = root;
}

void HuffmanTree::generateCodes(HuffmanNode* root, string codeword) {
    if (!root) {
        return;
    }

    if (root->data != static_cast<char>(0)) {
        codewordsMap[root->data] = std::move(codeword);
        // Using std::move just to avoid unnecessary copies
    }

    generateCodes(root->left, codeword + "0");
    generateCodes(root->right, codeword + "1");
}

string HuffmanTree::getCodeword(char c) {
    return codewordsMap[c];
}

string HuffmanTree::encode() {
    string encodedString;

    for (int i = 0; i < decodedData.size(); i++) {
        encodedString += getCodeword(decodedData[i]);
    }

    return encodedString;
}

string HuffmanTree::decode() {
    HuffmanNode* current = huffRoot;
    string decodedString;

    for (int i = 0; i < encodedData.size(); i++) {
        if (encodedData[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedString += current->data;
            current = huffRoot;
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
