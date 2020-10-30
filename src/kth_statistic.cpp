#ifndef kth_statistic_cpp
#define kth_statistic_cpp

#include "D_Array.cpp"

template<class T>
struct Default_Comporator {
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<class T>
int mid_of_three(D_Array<T> &array, int first, int second, int third) {
    int result;
    if (array[first] >= array[second] && array[first] <= array[third]) {
        result = first;
    }
    if (array[second] >= array[first] && array[second] <= array[third]) {
        result = second;
    }
    if (array[third] >= array[first] && array[third] <= array[second]) {
        result = third;
    }
    if (array[first] <= array[second] && array[first] >= array[third]) {
        result = first;
    }
    if (array[second] <= array[first] && array[second] >= array[third]) {
        result = second;
    }
    if (array[third] <= array[first] && array[third] >= array[second]) {
        result = third;
    }
    return result;
}

template<class T, class Comparator = Default_Comporator<T>>
int partition(D_Array<T> &array, int l, int r, Comparator comp = Comparator()) {
    int pivot_pos = mid_of_three(array, l, (r + l) / 2, r);
    T pivot = array[pivot_pos];
    array.swap(l, pivot_pos);
    int i = r;
    int j = r;
    for (int count = r; count > l; --count) {
        if (i == j) {
            if (comp(array[j], pivot)) {
                --j;
            } else if (comp(pivot, array[j]) || array[j] == pivot) {
                --i;
                --j;
            }
            continue;
        }
        if (i != j) {
            if (comp(pivot, array[j])) {
                array.swap(i, j);
                --j;
                --i;
            } else {
                --j;
            }
        }
    }
    array.swap(l, i);
    return i;
}

template<class T, class Comparator = Default_Comporator<T>>
T kth_statistic(D_Array<T> &array, int k, int l, int r, Comparator comp = Comparator()) {
    while (true) {
        int pivot_index = partition(array, l, r);
        if (pivot_index == k) {
            return array[pivot_index];
        }
        if (pivot_index > k) {
            r = pivot_index - 1;
        }
        if (pivot_index < k) {
            l = pivot_index + 1;
        }
    }
}

#endif