#include "SetGraph.h"
#include "utils.h"

SetGraph::SetGraph(int vertices_count) {
    graph.resize(vertices_count);
}

SetGraph::SetGraph(const IGraph &igraph) {
    graph.resize(igraph.vertices_count());
    bfs(igraph, [&](int v) {
        std::vector<int> next = igraph.get_next_vertices(v);
        for (auto i: next) {
            graph[v].insert(i);
        }
    });
}

void SetGraph::add_edge(int from, int to) {
    graph[from].insert(to);
}

int SetGraph::vertices_count() const {
    return graph.size();
}

std::vector<int> SetGraph::get_next_vertices(int vertex) const {
    std::vector<int> result;
    std::for_each(graph[vertex].begin(), graph[vertex].end(), [&](auto &n) { result.push_back(n); });
    return result;
}

std::vector<int> SetGraph::get_prev_vertices(int vertex) const {
    std::vector<int> result;
    for (const auto &i : graph) {
        auto search = i.find(vertex);
        if (search != i.end()) {
            result.push_back(*search);
        }
    }
    return result;
}
