//1_1. Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
//Требования: Время работы - O(n).
//n ≤ 100000.

#include <iostream>

void max_sum_index(const int *a, const int *b, int *indices, int n) {
    int max = a[0];
    int curr_max_ind = 0;
    int *max_ind_of_a_mas = new int [n];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
            curr_max_ind= i;
        }
        max_ind_of_a_mas[i] = curr_max_ind;
    }
    int max_ind_a = 0;
    int max_ind_b = 0;
    int max_sum = 0;
    int curr_max_sum = 0;
    for (int i = 0; i < n; i++) {
        curr_max_sum = b[i] + a[max_ind_of_a_mas[i]];
        if (curr_max_sum > max_sum) {
            max_sum = curr_max_sum;
            max_ind_a = max_ind_of_a_mas[i];
            max_ind_b = i;
        }
    }
    indices[0] = max_ind_a;
    indices[1] = max_ind_b;
    delete [] max_ind_of_a_mas;
}

int main() {
    int n = 0;
    std::cin >> n;
    int *A = new int [n];
    int *B = new int [n];
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> B[i];
    }
    int indices[2] = {0, 0};
    max_sum_index(A, B, indices, n);
    std::cout << indices[0] << " " << indices [1] << std::endl;
    delete [] A;
    delete [] B;
    return 0;
}
