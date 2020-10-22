#include "gtest/gtest.h"
#include "D_Array.cpp"

TEST(test, test1) {
    D_Array array;
    int expect_array[] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; ++i) {
        array.add(i);
    }
    for (int i = 0; i < 5; ++i) {
        EXPECT_TRUE(array[i] == expect_array[i]);
    }
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}