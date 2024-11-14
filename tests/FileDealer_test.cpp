#include "../src/file_dealer/FileDealer.h"
#include <gtest/gtest.h>

TEST(FileDealerTest, WritingEncodedDataAsBinary) {
    FileDealer fDealer;

    HuffmanTree huffTree("abacdab");
    EXPECT_TRUE(
        fDealer.writeEncodedDataBinary(huffTree.getEncodedData(), *huffTree.
            getCodewordsMap()
        )) << "Failed to write encoded data to binary file!";
}

TEST(FileDealerTest, ReadingEncodedDataAsBinaryAndCreatingTree) {
    FileDealer fDealer;
    fDealer.setEncodedOriginFilePath("encodedOutput.hfz");

    HuffmanTree* huffTree = fDealer.readEncodedDataBinary();
    EXPECT_NE(huffTree,
              nullptr) << "Failed to read encoded data from binary file!";
    EXPECT_EQ(huffTree->getDecodedData(), "abacdab");
}

TEST(FileDealerTest, WritingDecodedDataAsText) {
    FileDealer fDealer;

    EXPECT_TRUE(
        fDealer.writeDecodedDataText("abacdab"
        )) << "Failed to write decoded data to text file!";
}

TEST(FileDealerTest, ReadingOriginDataAsTextAndCreatingTree) {
    FileDealer fDealer;
    fDealer.setDecodedOriginFilePath("decodedOutput.txt");

    HuffmanTree* huffTree = fDealer.readOriginalDataText();
    EXPECT_NE(huffTree, nullptr) << "Failed to read original data from text!";
}
