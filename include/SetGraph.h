#ifndef AADS_SETGRAPH_H
#define AADS_SETGRAPH_H

#include <unordered_set>
#include "IGraph.h"

class SetGraph: public IGraph {
public:
    explicit SetGraph(int vertices_count);

    explicit SetGraph(const IGraph& igraph);

    virtual void add_edge(int from, int to) override;

    virtual int vertices_count() const override;

    virtual std::vector<int> get_next_vertices(int vertex) const override;

    virtual std::vector<int> get_prev_vertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> graph;
};


#endif //AADS_SETGRAPH_H
