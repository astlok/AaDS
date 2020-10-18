//1_1. Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
//Требования: Время работы - O(n).
//n ≤ 100000.

#include <iostream>
#include <vector>

#include "max_sum_index.h"

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> A(n);
    std::vector<int> B(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> B[i];
    }
    std::vector<int> indices = {0, 0};
    indices = max_sum_index( A, B, n);
    std::cout << indices[0] << " " << indices [1] << std::endl;
    return 0;
}
