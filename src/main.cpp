//2_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента
// массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
//Требования: Время работы поиска для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i]
//сначала нужно определить диапазон для бинарного поиска размером порядка k, а потом уже в нем делать бинарный поиск.

#include <iostream>
#include <cmath>

void find_k_range(const int elem, const int *mas, int length, int k_range[2]) {
    if (elem < mas[0]) {
        k_range[0] = 0;
        k_range[1] = 0;
        return;
    }
    if (elem > mas[length - 1]) {
        k_range[0] = length - 1;
        k_range[1] = length - 1;
        return;
    }
    int last_power_of_2 = 0;
    for (int i = 1; i < length; i *= 2) {
        if (elem >= mas[last_power_of_2]) {
            if ((i * 2 - 1) > length - 1) {
                k_range[0] = last_power_of_2;
                k_range[1] = length - 1;
                return;
            } else if (elem < mas[i * 2 - 1]) {
                k_range[0] = last_power_of_2;
                k_range[1] = i * 2 -1;
                return;
            }
        }
        last_power_of_2 = i;
    }
    k_range[0] = last_power_of_2;
    k_range[1] = length - 1;
}

int binary_search(const int *mas, int first, int last, int count, int elem) {
    while (first < last) {
        int mid = (first + last) / 2;
        if (elem > mas[mid]) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return first;
}
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
        if (search_result > 0 && B[i] < A[n - 1]) {
            if (abs(B[i] - A[search_result]) > abs(B[i] - A[search_result - 1])) {
                    std::cout << search_result << " ";
                } else {
                    std::cout << search_result - 1 << " ";
            }
        } else {
            std::cout << search_result << " ";
        }
//        std::cout << k_range[0] << " " << k_range[1] << std::endl;
    }
    delete [] A;
    delete [] B;
    return 0;
}