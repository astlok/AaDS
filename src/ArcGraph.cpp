#include <set>

#include "ArcGraph.h"
#include "utils.h"


ArcGraph::ArcGraph(int vertices_count) {
    graph.resize(2 * vertices_count);
}

ArcGraph::ArcGraph(const IGraph &igraph) {
    graph.resize(2 * igraph.vertices_count());
    bfs(igraph, [&](int v) {
        std::vector<int> next = igraph.get_next_vertices(v);
        for (int i: next) {
            graph.emplace_back(v, i);
        }
    });
}

void ArcGraph::add_edge(int from, int to) {
    graph.emplace_back(from, to);
}

int ArcGraph::vertices_count() const {
    std::set<int> uniq_vertices;
    for (auto edge: graph) {
        uniq_vertices.insert(edge.from);
        uniq_vertices.insert(edge.to);
    }
    return uniq_vertices.size();
}

std::vector<int> ArcGraph::get_next_vertices(int vertex) const {
    std::vector<int> result;
    for (auto edge: graph) {
        if (edge.from == vertex) {
            result.push_back(edge.to);
        }
    }
    return result;
}

std::vector<int> ArcGraph::get_prev_vertices(int vertex) const {
    std::vector<int> result;
    for (auto edge: graph) {
        if (edge.to == vertex) {
            result.push_back(edge.from);
        }
    }
    return result;
}
