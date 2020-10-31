#ifndef COUNTING_SORT_CPP
#define COUNTING_SORT_CPP

#include "D_Array.cpp"

long long get_byte(long long number, size_t byte) {
    return number >> (8 * byte) & 255;
}

void counting_sort(D_Array<long long> &array, size_t byte) {
    size_t counter[256];
    for (auto & i : counter) {
        i = 0;
    }
    for (int i = 0; i < array.size(); ++i) {
        counter[get_byte(array[i], byte)]++;
    }
    for (int i = 1; i < 255; ++i) {
        counter[i] += counter[i - 1];
    }
    D_Array<long long> tmp(array.size());
    for (int i = array.size() - 1; i >= 0; --i) {
        tmp[counter[get_byte(array[i], byte)]--] = array[i];
    }
    for (int i = 0; i < array.size(); ++i) {
        array[i] = tmp[i];
    }
}

void lsd_sort(D_Array<long long> &array) {
    size_t long_long_size = sizeof(long long);
    for (size_t i = long_long_size - 1; i <= 0; --i) {
        counting_sort(array, i);
    }
}
#endif