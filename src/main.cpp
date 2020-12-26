//Задача 3. «Города» (4 балла)
//Обязательная задача
//Требуется отыскать самый выгодный маршрут между городами.
//Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <set>

struct ToEdge {
    ToEdge() = default;
    ToEdge(int to, int weight): to(to), weight(weight)
    {}

    int to;
    int weight;
};

struct IGraph {

    virtual ~IGraph() {}

    virtual void add_edge(int from, int to, int weight) = 0;

    virtual int vertices_count() const  = 0;

    virtual std::vector<ToEdge> get_next_vertices(int vertex) const = 0;

    virtual std::vector<ToEdge> get_prev_vertices(int vertex) const = 0;
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
                    if (!visited[child.to]) {
                        queue.push(child.to);
                        visited[child.to] = true;
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

    virtual void add_edge(int from, int to, int weight) override;

    virtual int vertices_count() const override;

    virtual std::vector<ToEdge> get_next_vertices(int vertex) const  override;

    virtual std::vector<ToEdge> get_prev_vertices(int vertex) const override;

    virtual ~ListGraph() override = default;

private:
    std::vector<std::vector<ToEdge> > graph;
};

ListGraph::ListGraph(size_t vertices_count) {
    graph.resize(vertices_count);
}

void ListGraph::add_edge(int from, int to, int weight) {
    graph[from].emplace_back(to, weight);
    graph[to].emplace_back(from, weight);

}

int ListGraph::vertices_count() const {
    return graph.size();
}

std::vector<ToEdge> ListGraph::get_next_vertices(int vertex) const {
    std::vector<ToEdge> result;
    result.resize(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<ToEdge> ListGraph::get_prev_vertices(int vertex) const {
    std::vector<ToEdge> result;
    for (size_t i = 0; i < graph.size(); ++i) {
        for (auto child : graph[i]) {
            if (child.to == vertex) {
                result.push_back(child);
                break;
            }
        }
    }
    return result;
}

struct DistFromBegin {
    DistFromBegin(int vertex, int distance): vertex(vertex), distance(distance)
    {}

    int vertex;
    int distance;

    bool operator()(const DistFromBegin &left, const DistFromBegin &right) {
        return left.distance <= right.distance;
    }
    bool operator<(const DistFromBegin & rhs) const {
        return (this->distance <= rhs.distance);
    }
};
int shortest_way(IGraph &graph, int begin, int end) {
    std::set<DistFromBegin> queue;
    queue.emplace(begin, 0);

    std::vector<int> distance;
    distance.resize(graph.vertices_count(), 0);

    std::vector<bool> visited;
    visited.resize(graph.vertices_count(), false);

    visited[begin] = true;

    while(!queue.empty()) {
        DistFromBegin dist = *queue.begin();
        queue.erase(queue.begin());
        for (auto child: graph.get_next_vertices(dist.vertex)) {
            if (!visited[child.to]) {
                distance[child.to] = child.weight + dist.distance;
                queue.emplace(child.to, distance[child.to]);
                visited[child.to] = true;
            } else if (distance[dist.vertex] + child.weight < distance[child.to]) {
                queue.erase(DistFromBegin(child.to, distance[child.to]));
                distance[child.to] = distance[dist.vertex] + child.weight;
                queue.emplace(child.to, distance[child.to]);
            }
        }
    }
    return distance[end];
}


int main() {
    int vertex, edge;
    std::cin >> vertex >> edge;
    ListGraph graph(vertex);
    for (int i = 0; i < edge; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph.add_edge(from, to, weight);
    }
    int begin, end;
    std::cin >> begin >> end;
    std::cout << shortest_way(graph, begin, end);
    return 0;
}
