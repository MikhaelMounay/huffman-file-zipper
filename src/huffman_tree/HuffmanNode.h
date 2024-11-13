#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

struct HuffmanNode {
    HuffmanNode* left;
    HuffmanNode* right;

    char data;
    int frequency;

    HuffmanNode(char Data, int Frequency): data(Data),
                                           frequency(Frequency) {
        left = right = nullptr;
    }
};

#endif //HUFFMANNODE_H
