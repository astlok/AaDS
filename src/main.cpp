//2_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента
// массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
//Требования: Время работы поиска для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i]
//сначала нужно определить диапазон для бинарного поиска размером порядка k, а потом уже в нем делать бинарный поиск.

#include <iostream>
#include "func.h"

int main() {
    int n = 0;
    std::cin >> n;
    int *A = new int [n];
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }
    int m = 0;
    std::cin >> m;
    int *B = new int [m];
    for (int i = 0; i < m; ++i) {
        std::cin >> B[i];
    }
    int k_range[2];
    for (int i = 0; i < m; ++i) {
        find_k_range(B[i], A, n, k_range);
        int search_result = binary_search(A, k_range[0], k_range[1], n, B[i]);
        std::cout << print_result(A, n, search_result, B[i]) << " ";
    }
    delete [] A;
    delete [] B;
    return 0;
}