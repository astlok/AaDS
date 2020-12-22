#include "MatrixGraph.h"
#include "utils.h"

MatrixGraph::MatrixGraph(size_t vertices_count) {
    graph.resize(vertices_count);
    for (auto gr: graph) {
        gr.resize(vertices_count);
    }
}

MatrixGraph::MatrixGraph(const IGraph &igraph) {
    graph.resize(igraph.vertices_count());
    for (auto &gr: graph) {
        gr.resize(igraph.vertices_count());
    }
    bfs(igraph, [&](int v) {
        std::vector<int> next = igraph.get_next_vertices(v);
        for (auto i: next) {
            graph[v][i] = 1;
        }
    });
}

void MatrixGraph::add_edge(int from, int to) {
    graph[from][to] = 1;
}

int MatrixGraph::vertices_count() const {
    return graph.size();
}

std::vector<int> MatrixGraph::get_next_vertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph[vertex].size(); ++i) {
        if (graph[vertex][i]) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::get_prev_vertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i][vertex]) {
            result.push_back(i);
        }
    }
    return result;
}
