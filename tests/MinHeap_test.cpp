#include "../src/min_heap/MinHeap.h"
#include <gtest/gtest.h>

TEST(MinHeapTest, ConstructorAndEmpty) {
    MinHeap minH;
    EXPECT_TRUE(minH.isEmpty()) << "Default Constructor not initializing MinHeap as empty!";

    MinHeap minH2(10);
    EXPECT_TRUE(minH2.isEmpty()) << "Parameterized Constructor not initializing MinHeap as empty!";
}

TEST(MinHeapTest, SingleElementHeap) {
    MinHeap minH(10);
    minH.insert('a', 5);

    EXPECT_FALSE(minH.isEmpty()) << "MinHeap with single inserted element shouldn't be empty!";
    EXPECT_EQ(minH.extractMin()->frequency, 5) << "MinHeap extracted element should be the same as inserted!";
    EXPECT_TRUE(minH.isEmpty()) << "MinHeap with should be empty after extracting its single element!";
}

TEST(MinHeapTest, MultipleElementHeap) {
    MinHeap minH(10);
    minH.insert('a', 10);
    minH.insert('b', 5);
    minH.insert('c', 15);

    EXPECT_EQ(minH.extractMin()->frequency, 5) << "MinHeap extracted element should be sorted ascendingly!";
    EXPECT_EQ(minH.extractMin()->frequency, 10) << "MinHeap extracted element should be sorted ascendingly!";
    EXPECT_EQ(minH.extractMin()->frequency, 15) << "MinHeap extracted element should be sorted ascendingly!";
}

TEST(MinHeapTest, ResizingHeap) {
    MinHeap minH(1);
    minH.insert('a', 10);
    minH.insert('b', 5);
    EXPECT_EQ(minH.extractMin()->frequency, 5) << "Resized MinHeap extracted element should be the minimum of inserted!";
    EXPECT_EQ(minH.extractMin()->frequency, 10) << "Resized MinHeap extracted element should be the minimum of inserted!";
    EXPECT_TRUE(minH.isEmpty()) << "Resized MinHeap with no elements after extraction should be empty!";
}

TEST(MinHeapTest, DuplicateElements) {
    MinHeap minH(10);
    minH.insert('a', 5);
    minH.insert('b', 5);
    minH.insert('c', 5);

    EXPECT_EQ(minH.extractMin()->frequency, 5) << "MinHeap with duplicates extracted element should be the minimum of inserted!";
    EXPECT_EQ(minH.extractMin()->frequency, 5) << "MinHeap with duplicates extracted element should be the minimum of inserted!";
    EXPECT_EQ(minH.extractMin()->frequency, 5) << "MinHeap with duplicates extracted element should be the minimum of inserted!";
}
