//Задача 2. Количество различных путей (3 балла)
//Обязательная задача
//Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
//Найдите количество различных кратчайших путей между заданными вершинами.

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

struct IGraph {
    virtual ~IGraph() {}

    virtual void add_edge(int from, int to) = 0;

    virtual int vertices_count() const  = 0;

    virtual std::vector<int> get_next_vertices(int vertex) const = 0;

    virtual std::vector<int> get_prev_vertices(int vertex) const = 0;
};

void bfs(const IGraph& graph, const std::function<void(int)>& callback) {
    std::vector<bool> visited;
    std::queue<int> queue;
    visited.resize(graph.vertices_count(), false);
    for (int i = 0; i < graph.vertices_count(); ++i) {
        if (!visited[i]) {
            queue.push(i);
            visited[i] = true;
            while (!queue.empty()) {
                int vertex = queue.front();
                queue.pop();
                callback(vertex);
                for (auto child : graph.get_next_vertices(vertex)) {
                    if (!visited[child]) {
                        queue.push(child);
                        visited[child] = true;
                    }
                }
            }
        }
    }
}

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
    graph[to].push_back(from);
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


int diff_way_num(const IGraph& graph, const int begin, const int end) {
    std::vector<int> ways;
    std::vector<int> deep;
    std::vector<bool> visited;
    std::queue<int> queue;
    ways.resize(graph.vertices_count(), 0);
    deep.resize(graph.vertices_count(),0);
    visited.resize(graph.vertices_count(), false);
    for (int i = 0; i < graph.vertices_count(); ++i) {
        if (i == begin) {
            queue.push(i);
            ways[i] = 1;
            while (!queue.empty()) {
                int vertex = queue.front();
                queue.pop();
                for (auto child : graph.get_next_vertices(vertex)) {
                    if (!visited[child]) {
                        queue.push(child);
                        ways[child] += ways[vertex];
                        deep[child] += deep[vertex] + 1;
                        visited[child] = true;
                    } else if (deep[child] == deep[vertex] + 1) {
                        ways[child] += ways[vertex];
                    }
                }
            }
        }
    }
    return ways[end];
}

int main() {
    int vertex;
    int edge;
    std::cin >> vertex >> edge;

    ListGraph graph(vertex);
    for (int i = 0; i < edge; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.add_edge(from, to);
    }

    int begin, end;
    std::cin >> begin >> end;
    int ways = diff_way_num(graph, begin, end);
    std::cout << ways << std::endl;
    return 0;
}
