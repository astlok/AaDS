#include <iostream>

#include "D_Array.cpp"
#include "merge_sort.cpp"

typedef enum state {
    BEGIN,
    END,
} state_t;

struct Point {
    int coor;
    state_t state;
};

struct point_comparator {
    bool operator()(const Point &l, const Point &r) {
        return l.coor < r.coor;
    }
};

void run(std::istream &is, std::ostream &os) {
    int n = 0;

    is >> n;
    D_Array<Point> array;

    for (int i = 0; i < n; ++i) {
        Point point;
        is >> point.coor;
        point.state = BEGIN;
        array.add(point);
        is >> point.coor;
        point.state = END;
        array.add(point);
    }

    merge_sort(array, 0, array.size() - 1, point_comparator());

    int layers_count = 0;
    int layers_lenght = 0;
    int last_first_coor = 0;
    for (int i = 0; i < array.size(); ++i) {
        if (array[i].state == BEGIN) {
            if (layers_count == 0) {
                last_first_coor = array[i].coor;
            } else if (layers_count == 1) {
                layers_lenght = layers_lenght + array[i].coor - last_first_coor;
                last_first_coor = 0;
            }
            layers_count++;
        } else if (array[i].state == END) {
            if (layers_count == 1) {
                layers_lenght = layers_lenght + array[i].coor - last_first_coor;
                last_first_coor = 0;
            }
            layers_count--;
            if (layers_count == 1) {
                last_first_coor = array[i].coor;
            }
        }
    }
    os << layers_lenght;

}

int main() {
    run(std::cin, std::cout);
    return 0;
}
