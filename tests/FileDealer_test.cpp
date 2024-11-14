#include "../src/file_dealer/FileDealer.h"
#include <gtest/gtest.h>

TEST(FileDealerTest, WritingEncodedDataAsBinary) {
    FileDealer fDealer("extractedFileAfterDecoding.txt", "compressedFileFromHardCoded.hfz");

    HuffmanTree huffTree("abacdab");
    EXPECT_TRUE(fDealer.writeEncodedDataBinary(huffTree.getEncodedData(), *huffTree.getCodewordsMap())) << "Failed to write encoded data to binary file!";
}

TEST(FileDealerTest, ReadingEncodedDataAsBinaryAndCreatingTree) {
    FileDealer fDealer("extractedFileAfterDecoding.txt", "compressedFileFromHardCoded.hfz");

    HuffmanTree* huffTree = fDealer.readEncodedDataBinary();
    EXPECT_NE(huffTree, nullptr) << "Failed to read encoded data from binary file!";
    EXPECT_EQ(huffTree->getDecodedData(), "abacdab");
}
