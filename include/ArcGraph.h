#ifndef AADS_ARCGRAPH_H
#define AADS_ARCGRAPH_H

#include "IGraph.h"

struct Edge {
    Edge() = default;
    explicit Edge(int from, int to): from(from), to(to) {};
    int from;
    int to;
};

class ArcGraph: public IGraph {
public:
    explicit ArcGraph(int vertices_count);

    explicit ArcGraph(const IGraph& igraph);

    virtual void add_edge(int from, int to) override;

    virtual int vertices_count() const override;

    virtual std::vector<int> get_next_vertices(int vertex) const override;

    virtual std::vector<int> get_prev_vertices(int vertex) const override;

private:
    std::vector<Edge> graph;
};


#endif //AADS_ARCGRAPH_H
