#include "func.h"
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
                k_range[1] = i * 2 - 1;
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

int print_result(const int *mas, int length, int search_result, int elem){
    if (search_result > 0 && elem < mas[length - 1]) {
        if (abs(elem - mas[search_result]) < abs(elem - mas[search_result - 1])) {
            return search_result;
        } else {
            return search_result - 1;
        }
    } else {
        return search_result;
    }
}


