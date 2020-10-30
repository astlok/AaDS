#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>

#include "D_Array.cpp"
#include "kth_statistic.cpp"

void run(std::istream &is, std::ostream &os) {
    int n = 0;
    int k = 0;

    is >> n >> k;
    D_Array<int> array;

    for (int i = 0; i < n; ++i) {
        int elem = 0;
        is >> elem;
        array.add(elem);
    }

    os << kth_statistic(array, k, 0, array.size() - 1);
}
void test1() {
    std::stringstream input;
    std::stringstream output;
    input << "10 " << "5 ";
    input << "1 2 3 4 5 6 7 8 9 10";
    run(input, output);
    assert(output.str() == "6");
}
void test2() {
    std::stringstream input;
    std::stringstream output;
    input << "48 " << " 47 ";
    input << "2 8 9 0 6 8 8 2 3 23 87 42 92 6 3 4 5 26 4 84 57 93 48 8 6 2 39 45 5 3 2 9 7 7 6 3 3 5 6 3 5 6 3 4 5 6 7 4";
    run(input, output);
    assert(output.str() == "93");
}
int main() {
//    run(std::cin, std::cout);
    test1();
    test2();

    return 0;
}
