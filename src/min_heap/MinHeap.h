#ifndef MINHEAP_H
#define MINHEAP_H

#include "../huffman_tree/HuffmanNode.h"

class MinHeap {
private:
    HuffmanNode** heapArr;
    int capacity;
    int size;

    // A utility function to swap two elements
    void swap(HuffmanNode** a, HuffmanNode** b);

    // A utility function to resize the heap array
    void resizeHeapArray();

public:
    // Default Constructor
    MinHeap();

    // Parameterized Constructor
    explicit MinHeap(int Capacity);

    // Destructor
    ~MinHeap();

    // Gets the index of parent of the node at index "index"
    int parent(int index);

    // Gets the index of left child of the node at index "index"
    int leftChild(int index);

    // Gets the index of right child of the node at index "index"
    int rightChild(int index);

    // Inserts a new character and its frequency
    void insert(char character, int frequency);

    // Inserts a new HuffmanNode
    void insert(HuffmanNode* node);

    // A function to Heapify a subtree with the root at given index "index"
    void MinHeapify(int index);

    // Checks if the heap is empty
    bool isEmpty();

    // Gets the current size of the heap
    int getSize();

    // Gets the minimum key (key at root) from the heap
    HuffmanNode* getMin();

    // Gets the minimum key (key at root) and remove it from the heap
    HuffmanNode* extractMin();
};

#endif //MINHEAP_H
