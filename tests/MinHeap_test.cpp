#include "../src/min_heap/MinHeap.h"
#include <gtest/gtest.h>

TEST(MinHeapTest, ConstructorAndEmpty) {
    MinHeap minH;
    EXPECT_TRUE(minH.isEmpty()) << "Default Constructor not initializing MinHeap as empty!";

    MinHeap minH2 = MinHeap(10);
    EXPECT_TRUE(minH2.isEmpty()) << "Parameterized Constructor not initializing MinHeap as empty!";
}
