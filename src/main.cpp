#include <QApplication>
#include <QPushButton>

#include <iostream>
#include "min_heap/MinHeap.h"

using namespace std;

int main(int argc, char* argv[]) {
    MinHeap myHeap = MinHeap(10);

    myHeap.insertKey(3);
    myHeap.insertKey(2);
    myHeap.insertKey(5);
    myHeap.insertKey(1);
    myHeap.insertKey(10);

    cout << myHeap.extractMin() << endl;
    cout << myHeap.extractMin() << endl;
    cout << myHeap.extractMin() << endl;
    cout << myHeap.extractMin() << endl;
    cout << myHeap.extractMin() << endl;
    cout << myHeap.extractMin() << endl;
    cout << myHeap.extractMin() << endl;

    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
