#include <QApplication>
#include <QPushButton>

#include "file_dealer/FileDealer.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    FileDealer fDealer("extractedFileAfterDecoding.txt", "compressedFileFromHardCoded.hfz");

    HuffmanTree huffTree("abacdab");
    fDealer.writeEncodedDataBinary(huffTree.getEncodedData(), *huffTree.getCodewordsMap());

    HuffmanTree* huffTree2 = fDealer.readEncodedDataBinary();
    cout << "Encoded Data: " << huffTree2->getEncodedData() << endl;
    cout << "Decoded Data: " << huffTree2->getDecodedData() << endl;


    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
