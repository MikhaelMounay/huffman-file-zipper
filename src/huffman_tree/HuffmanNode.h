#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

struct HuffmanNode {
    HuffmanNode* left;
    HuffmanNode* right;

    char data;
    int frequency;

    HuffmanNode(): data(static_cast<char>(0)), frequency(0) {
        left = right = nullptr;
    }

    HuffmanNode(char Data, int Frequency): data(Data),
                                           frequency(Frequency) {
        left = right = nullptr;
    }
};

#endif //HUFFMANNODE_H
