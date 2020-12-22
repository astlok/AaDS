#include <vector>
#include <queue>
#include "utils.h"

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