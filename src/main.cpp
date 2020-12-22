#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include <cassert>
#include <algorithm>

#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include "utils.h"

int main() {
    ListGraph list(6);

    list.add_edge(0, 1);
    list.add_edge(1, 2);
    list.add_edge(1, 5);
    list.add_edge(2, 3);
    list.add_edge(3, 4);
    list.add_edge(4, 2);

    bfs(list, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "------------------" << std::endl;

    assert(list.vertices_count() == 6);

    MatrixGraph matr(list);
    bfs(matr, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "------------------" << std::endl;
    assert(matr.vertices_count() == 6);

    ArcGraph arc(matr);
    bfs(arc, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "------------------" << std::endl;
    assert(arc.vertices_count() == 6);

    SetGraph set(arc);
    bfs(arc, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "------------------" << std::endl;
    assert(set.vertices_count() == 6);

    return 0;
}