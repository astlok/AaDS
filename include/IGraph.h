#ifndef AADS_IGRAPH_H
#define AADS_IGRAPH_H

#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void add_edge(int from, int to) = 0;

    virtual int vertices_count() const  = 0;

    virtual std::vector<int> get_next_vertices(int vertex) const = 0;
    virtual std::vector<int> get_prev_vertices(int vertex) const = 0;
};

#endif //AADS_IGRAPH_H
