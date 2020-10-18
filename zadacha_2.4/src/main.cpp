//2_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента
// массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
//Требования: Время работы поиска для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i]
//сначала нужно определить диапазон для бинарного поиска размером порядка k, а потом уже в нем делать бинарный поиск.

#include <iostream>
#include <vector>

#include "nearest_index.h"

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> A(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    int m = 0;
    std::cin >> m;
    std::vector<int> B(m);
    for (int i = 0; i < m; i++) {
        std::cin >> B[i];
    }
    std::vector<int> indices = {0, 0, 0};
    indices = nearest_index(A, B, n, m);
    std::cout << indices[0] << " " << indices[1] << " " << indices[2] << std::endl;
    return 0;
}