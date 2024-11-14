#include "MinHeap.h"

MinHeap::MinHeap(): capacity(1), size(0) {
    heapArr = new HuffmanNode*[capacity];
}

MinHeap::MinHeap(int Capacity): capacity(Capacity), size(0) {
    heapArr = new HuffmanNode*[capacity];
}

MinHeap::~MinHeap() {
    for (int i = 1; i <= size; i++) {
        delete heapArr[i];
    }
    delete[] heapArr;
}

void MinHeap::swap(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

void MinHeap::resizeHeapArray() {
    capacity = capacity * 2;
    HuffmanNode** newHeapArr = new HuffmanNode*[capacity];

    for (int i = 0; i <= size; i++) {
        newHeapArr[i] = heapArr[i];
    }

    delete[] heapArr;
    heapArr = newHeapArr;
}

int MinHeap::parent(int index) {
    return (index / 2);
}

int MinHeap::leftChild(int index) {
    return (2 * index);
}

int MinHeap::rightChild(int index) {
    return (2 * index + 1);
}

void MinHeap::insert(char character, int frequency) {
    if (size == capacity) {
        resizeHeapArray();
    }

    heapArr[++size] = new HuffmanNode(character, frequency);

    int i = size;
    while (i != 1 && heapArr[parent(i)]->frequency > heapArr[i]->frequency) {
        swap(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::insert(HuffmanNode* node) {
    if (size == capacity) {
        resizeHeapArray();
    }

    heapArr[++size] = node;

    int i = size;
    while (i != 1 && heapArr[parent(i)]->frequency > heapArr[i]->frequency) {
        swap(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::MinHeapify(int index) {
    int leftIndex = leftChild(index);
    int rightIndex = rightChild(index);

    int minIndex = index;

    if (leftIndex <= size && heapArr[leftIndex]->frequency < heapArr[index]->
        frequency) {
        minIndex = leftIndex;
    }

    if (rightIndex <= size && heapArr[rightIndex]->frequency < heapArr[minIndex]
        ->frequency) {
        minIndex = rightIndex;
    }

    if (minIndex != index) {
        swap(&heapArr[index], &heapArr[minIndex]);
        MinHeapify(minIndex);
    }
}

bool MinHeap::isEmpty() {
    return size == 0;
}

int MinHeap::getSize() {
    return size;
}

HuffmanNode* MinHeap::getMin() {
    if (isEmpty()) {
        return nullptr;
    }

    return heapArr[1];
}

HuffmanNode* MinHeap::extractMin() {
    if (isEmpty()) {
        return nullptr;
    }

    if (size == 1) {
        size--;
        return heapArr[1];
    }

    HuffmanNode* min = heapArr[1];
    heapArr[1] = heapArr[size--];
    MinHeapify(1);

    return min;
}
