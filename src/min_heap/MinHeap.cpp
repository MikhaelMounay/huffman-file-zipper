#include "MinHeap.h"

MinHeap::MinHeap(): capacity(1), size(0) {
    heapArr = new int[capacity];
}

MinHeap::MinHeap(int Capacity): capacity(Capacity), size(0) {
    heapArr = new int[capacity];
}

MinHeap::~MinHeap() {
    delete[] heapArr;
}

void MinHeap::swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void MinHeap::resizeHeapArray() {
    int* newHeapArr = new int[capacity * 2];

    for (int i = 0; i <= size; i++) {
        newHeapArr[i] = heapArr[i];
    }

    capacity = capacity * 2;

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

void MinHeap::insertKey(int key) {
    if (size == capacity) {
        resizeHeapArray();
    }

    heapArr[++size] = key;

    int i = size;
    while (i != 1 && heapArr[parent(i)] > heapArr[i]) {
        swap(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::MinHeapify(int index) {
    int leftIndex = leftChild(index);
    int rightIndex = rightChild(index);

    int minIndex = index;

    if (leftIndex <= size && heapArr[leftIndex] < heapArr[index]) {
        minIndex = leftIndex;
    }

    if (rightIndex <= size && heapArr[rightIndex] < heapArr[minIndex]) {
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

int MinHeap::getMin() {
    if (isEmpty()) {
        return -1;
    }

    return heapArr[1];
}

int MinHeap::extractMin() {
    if (isEmpty()) {
        return -1;
    }

    if (size == 1) {
        size--;
        return heapArr[1];
    }

    int min = heapArr[1];
    heapArr[1] = heapArr[size--];
    MinHeapify(1);

    return min;
}
