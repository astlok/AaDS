#include "gtest/gtest.h"
#include "func.h"

TEST(test, test1) {
    int n = 3;
    int m = 3;
    int A[] = {10, 20, 30};
    int B[] = {9, 15, 35};

    int k_range[2];
    std::string result;
    for (int i = 0; i < m; ++i) {
        find_k_range(B[i], A, n, k_range);
        int search_result = binary_search(A, k_range[0], k_range[1], n, B[i]);
        result += std::to_string(print_result(A, n, search_result, B[i])) + " ";
    }
    ASSERT_EQ("0 0 2 ", result);
}

TEST(test, test2) {
    int n = 3;
    int m = 4;
    int A[] = {10, 20, 30};
    int B[] = {8, 9, 10, 32};

    int k_range[2];
    std::string result;
    for (int i = 0; i < m; ++i) {
        find_k_range(B[i], A, n, k_range);
        int search_result = binary_search(A, k_range[0], k_range[1], n, B[i]);
        result += std::to_string(print_result(A, n, search_result, B[i])) + " ";
    }
    ASSERT_EQ("0 0 0 2 ", result);
}

TEST(test, test3) {
    int n = 3;
    int m = 5;
    int A[] = {-10, 20, 30};
    int B[] = {8, 9, 25, 30, 32};

    int k_range[2];
    std::string result;
    for (int i = 0; i < m; ++i) {
        find_k_range(B[i], A, n, k_range);
        int search_result = binary_search(A, k_range[0], k_range[1], n, B[i]);
        result += std::to_string(print_result(A, n, search_result, B[i])) + " ";
    }
    ASSERT_EQ("1 1 1 2 2 ", result);
}

TEST(test, test4) {
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
