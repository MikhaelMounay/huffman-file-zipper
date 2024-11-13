#include "../src/huffman_tree/HuffmanTree.h"
#include <gtest/gtest.h>

TEST(HuffmanTreeTest, SingleCharacterTree) {
    unordered_map<char, int> charFreqs = {{'a', 10}};
    HuffmanTree tree(charFreqs);

    EXPECT_EQ(tree.getCodeword('a'), "");
}

TEST(HuffmanTreeTest, TwoCharacterTree) {
    unordered_map<char, int> charFreqs = {{'a', 5}, {'b', 10}};
    HuffmanTree tree(charFreqs);

    EXPECT_EQ(tree.getCodeword('a'), "0");
    EXPECT_EQ(tree.getCodeword('b'), "1");
}

TEST(HuffmanTreeTest, MultipleCharacterTree) {
    unordered_map<char, int> charFreqs = {
        {'a', 5}, {'b', 10}, {'c', 15}, {'d', 20}};
    HuffmanTree tree(charFreqs);

    EXPECT_EQ(tree.getCodeword('a'), "110");
    EXPECT_EQ(tree.getCodeword('b'), "111");
    EXPECT_EQ(tree.getCodeword('c'), "10");
    EXPECT_EQ(tree.getCodeword('d'), "0");
}

TEST(HuffmanTreeTest, EncodingAndDecodingFreqMapConstructor) {
    std::string input = "abacdab";
    unordered_map<char, int> charFreqs;

    for (int i = 0; i < input.size(); i++) {
        charFreqs[input[i]] += 1;
    }
    HuffmanTree tree(charFreqs);

    tree.setDecodedDataAndEncode(input);
    std::string encoded = tree.getEncodedData();
    std::string decoded = tree.getDecodedData();

    EXPECT_EQ(decoded, input);
}

TEST(HuffmanTreeTest, EncodingAndDecodingStringConstructor) {
    std::string input = "abacdab";
    HuffmanTree tree(input);

    tree.setDecodedDataAndEncode(input);
    std::string encoded = tree.getEncodedData();
    std::string decoded = tree.getDecodedData();

    EXPECT_EQ(decoded, input);
}
