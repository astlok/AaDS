#ifndef AADS_LISTGRAPH_H
#define AADS_LISTGRAPH_H

#include "IGraph.h"

class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t vertices_count);

    explicit ListGraph(const IGraph& igraph);

    virtual void add_edge(int from, int to) override;

    virtual int vertices_count() const override;

    virtual std::vector<int> get_next_vertices(int vertex) const  override;

    virtual std::vector<int> get_prev_vertices(int vertex) const override;

    virtual ~ListGraph() override = default;

private:
    std::vector<std::vector<int> > graph;
};

#endif //AADS_LISTGRAPH_H
