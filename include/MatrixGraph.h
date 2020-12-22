#ifndef AADS_MATRIXGRAPH_H
#define AADS_MATRIXGRAPH_H

#include "IGraph.h"

class MatrixGraph: public IGraph {
public:
    explicit MatrixGraph(size_t vertices_count);

    explicit MatrixGraph(const IGraph& igraph);

    virtual void add_edge(int from, int to) override;

    virtual int vertices_count() const override;

    virtual std::vector<int> get_next_vertices(int vertex) const override;

    virtual std::vector<int> get_prev_vertices(int vertex) const override;

private:
    std::vector<std::vector<int>> graph;
};


#endif //AADS_MATRIXGRAPH_H
