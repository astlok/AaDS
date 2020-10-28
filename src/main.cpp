#include <iostream>
#include <sstream>

#include "Heap.cpp"
#include "D_Array.cpp"
#include "merge_sort.cpp"

struct int_comporator {
    bool operator()(int &l, int &r) {
        return l < r;
    }
};

struct Train {
    int arrive;
    int departure;

    bool operator==(Train &rhs) const {
        return this->departure == rhs.departure;
    }
};

struct train_comporator {
    bool operator()(const Train &l, const Train &r) {
        return l.departure > r.departure;
    }
};

struct Segment {
    int l;
    int r;
};

struct segment_comparator {
    bool operator()(const Segment &l, const Segment &r) {
        return l.l < r.l;
    }
};

bool is_point_in_segment(int i, Segment segment) {
    return (i >= segment.l && i <= segment.r);
}

void run(std::istream &is, std::ostream &os) {
    D_Array<Segment> array;
    array.add({1, 4});
    array.add({7 , 8});
    array.add({2, 5});

    merge_sort(array, 0, array.size() - 1, segment_comparator());
    for (int i = 0; i < array.size(); ++i) {
        os << "{" << array[i].l << ", " << array[i].r << "} ";
    }
    int max_layers = 0;


    for (int j = 0; j < array.size(); ++j) {
        if
    }

    os << std::endl << max_layers;

}

int main() {
    run(std::cin, std::cout);
    return 0;
}
