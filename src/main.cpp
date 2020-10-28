#include <iostream>
#include <sstream>

#include "Heap.cpp"
#include "D_Array.cpp"

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

void run(std::istream &is, std::ostream &os) {
    int n = 0;
    is >> n;

    D_Array<Train> array;

    Heap<Train, train_comporator> heap(array);

    int max_size_heap = 0;
    for (int i = 0; i < n; ++i) {
        Train train;
        is >> train.arrive >> train.departure;
        if (heap.heap_size() == 0) {
            heap.insert(train);
            max_size_heap = 1;
            continue;
        }
        bool put = false;
        while (!put) {
            if (heap.see_max().departure < train.arrive) {
                heap.extract_max();
            } else {
                heap.insert(train);
                put = true;
            }
            if (heap.heap_size() == 0) {
                heap.insert(train);
                put = true;
            }
        }
        if (heap.heap_size() > max_size_heap) {
            max_size_heap = heap.heap_size();
        }
    }
    os << max_size_heap;
}

void test1() {
    std::stringstream input;
    std::stringstream output;
    input << "3" << std::endl;
    input << "10 " << "20" << std::endl;
    input << "20 " << "25" << std::endl;
    input << "21 " << "30" << std::endl;
    run(input, output);
    assert(output.str() == "2");
}

void test2() {
    std::stringstream input;
    std::stringstream output;
    input << "4" << std::endl;
    input << "10 " << "20" << std::endl;
    input << "20 " << "25" << std::endl;
    input << "21 " << "30" << std::endl;
    input << "30 " << "31" << std::endl;
    run(input, output);
    assert(output.str() == "2");
}

void test3() {
    std::stringstream input;
    std::stringstream output;
    input << "4" << std::endl;
    input << "10 " << "100" << std::endl;
    input << "20 " << "90" << std::endl;
    input << "21 " << "89" << std::endl;
    input << "30 " << "87" << std::endl;
    run(input, output);
    assert(output.str() == "4");
}

void test4() {
    std::stringstream input;
    std::stringstream output;
    input << "4" << std::endl;
    input << "10 " << "20" << std::endl;
    input << "21 " << "22" << std::endl;
    input << "23 " << "24" << std::endl;
    input << "25 " << "26" << std::endl;
    run(input, output);
    assert(output.str() == "1");
}

void test5() {
    std::stringstream input;
    std::stringstream output;
    input << "0" << std::endl;
    run(input, output);
    assert(output.str() == "0");
}

void test6() {
    std::stringstream input;
    std::stringstream output;
    input << "4" << std::endl;
    input << "10 " << "20" << std::endl;
    input << "19 " << "26" << std::endl;
    input << "20 " << "21" << std::endl;
    input << "21 " << "26" << std::endl;
    run(input, output);
    assert(output.str() == "3");
}

void test7() {
    std::stringstream input;
    std::stringstream output;
    input << "7" << std::endl;
    input << "10 " << "20" << std::endl;
    input << "19 " << "26" << std::endl;
    input << "20 " << "25" << std::endl;
    input << "27 " << "31" << std::endl;
    input << "28 " << "30" << std::endl;
    input << "29 " << "40" << std::endl;
    input << "30 " << "40" << std::endl;

    run(input, output);
    assert(output.str() == "4");
}

void test8() {
    std::stringstream input;
    std::stringstream output;
    input << "3" << std::endl;
    input << "10 " << "20" << std::endl;
    input << "19 " << "26" << std::endl;
    input << "1000000000 " << "1000000001" << std::endl;

    run(input, output);
    assert(output.str() == "2");
}

void test9() {
    std::stringstream input;
    std::stringstream output;
    input << "10" << std::endl;
    input << "10 " << "20" << std::endl;
    input << "19 " << "26" << std::endl;
    input << "20 " << "25" << std::endl;
    input << "27 " << "31" << std::endl;
    input << "28 " << "30" << std::endl;
    input << "29 " << "40" << std::endl;
    input << "30 " << "40" << std::endl;
    input << "32 " << "40" << std::endl;
    input << "33 " << "39" << std::endl;
    input << "35 " << "38" << std::endl;

    run(input, output);
    assert(output.str() == "5");
}

int main() {
//    run(std::cin, std::cout);
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    return 0;
}
