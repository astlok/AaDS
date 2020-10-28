#ifndef HEAP_CPP
#define HEAP_CPP

#include "D_Array.cpp"

template<class T>
struct Default_Comporator {
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<class T, class Comarator = Default_Comporator<T>>
class Heap {
public:
    explicit Heap(D_Array<T> &array, Comarator comp = Comarator()) : array(array), size(array.size()), comp(comp) {
        build_heap();
    }

    void insert(T elem) {
        array.add(elem);
        sift_up(array.size() - 1);
        ++size;
    }

    T extract_max() {
        T result = array[0];
        array.swap(0, array.size() - 1);
        array.pop();

        sift_down(0);
        --size;
        return result;
    }

    T see_max() const {
        return array[0];
    }

    int heap_size() const {
        return size;
    }

private:
    void build_heap() {
        for (int i = array.size() / 2; i >= 0; --i) {
            sift_down(i);
        }
    }

    void sift_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        int largest = i;
        if (left < array.size() && comp(array[largest], array[left])) {
            largest = left;
        }

        if (right < array.size() && comp(array[largest], array[right])) {
            largest = right;
        }

        if (largest != i) {
            array.swap(i, largest);
            sift_down(largest);
        }
    }

    void sift_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (comp(array[i], array[parent]) || array[i] == array[parent]) {
                return;
            }
            array.swap(i, parent);
            i = parent;
        }
    }

    D_Array<T> &array;
    int size;
    Comarator comp;
};

#endif
