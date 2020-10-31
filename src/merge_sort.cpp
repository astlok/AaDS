#ifndef MERGE_SORT_CPP
#define MERGE_SORT_CPP

#include "D_Array.cpp"

template<class T>
struct Default_Comparator {
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<class T, class Comparator = Default_Comparator<T>>
void merge_sort(D_Array<T> &array, int l, int r, Comparator comp = Comparator()) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(array, l, mid, comp);
    merge_sort(array, mid + 1, r, comp);

    int i = l;
    int j = mid + 1;
    D_Array<T> tmp(r - l + 1);

    for (int step = 0; step < r - l + 1; ++step) {
        if ((j > r) || ((i <= mid) && comp(array[i], array[j]))) {
            tmp[step] = array[i];
            i++;
        } else {
            tmp[step] = array[j];
            j++;
        }
    }
    for (int step = 0; step < r - l + 1; step++) {
        array[l + step] = tmp[step];
    }
}

#endif  // MERGE_SORT_CPP
