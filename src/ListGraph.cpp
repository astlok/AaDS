#include "IGraph.h"
#include "ListGraph.h"
#include "utils.h"

ListGraph::ListGraph(size_t vertices_count) {
    graph.resize(vertices_count);
}

ListGraph::ListGraph(const IGraph &igraph) {
    graph.resize(igraph.vertices_count());
    bfs(igraph, [&](int v) {
        std::vector<int> next = igraph.get_next_vertices(v);
        for (auto i: next) {
            graph[v].push_back(i);
        }
    });
}

void ListGraph::add_edge(int from, int to) {
    graph[from].push_back(to);
}


int ListGraph::vertices_count() const {
    return graph.size();
}

std::vector<int> ListGraph::get_next_vertices(int vertex) const {
    std::vector<int> result;
    result.resize(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<int> ListGraph::get_prev_vertices(int vertex) const {
    std::vector<int> result;
    for (size_t i = 0; i < graph.size(); ++i) {
        for (auto child : graph[i]) {
            if (child == vertex) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}
