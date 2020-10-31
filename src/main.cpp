#include <iostream>

#include "D_Array.cpp"

long long get_byte(const long long number, const int byte) {
    return (number >> (8 * byte)) & 255;
}

void counting_sort(D_Array<long long> &array, int byte) {
    int counter[256];
    for (auto & i : counter) {
        i = 0;
    }
    for (int i = 0; i < array.size(); ++i) {
        counter[get_byte(array[i], byte)]++;
    }
    for (int i = 1; i < 256; ++i) {
        counter[i] += counter[i - 1];
    }
    D_Array<long long> tmp(array.size());
    for (int i = array.size() - 1; i >= 0; --i) {
        tmp[--counter[get_byte(array[i], byte)]] = array[i];
    }
    for (int i = 0; i < array.size(); ++i) {
        array[i] = tmp[i];
    }
}

void lsd_sort(D_Array<long long> &array) {
    int long_long_size = sizeof(long long);
    for (int i = 0; i < long_long_size; ++i) {
        counting_sort(array, i);
    }
}
void run(std::istream &is, std::ostream &os) {
    int n = 0;

    is >> n;
    D_Array<long long> array;

    for (int i = 0; i < n; ++i) {
        long long elem = 0;
        is >> elem;
        array.add(elem);
    }

    lsd_sort(array);

    for (int i = 0; i < n; ++i) {
        os << array[i] << " ";
    }
}

int main() {
    run(std::cin, std::cout);
    return 0;
}
