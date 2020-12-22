#ifndef AADS_UTILS_H
#define AADS_UTILS_H

#include "IGraph.h"

void bfs(const IGraph& graph, const std::function<void(int)>& callback);

#endif //AADS_UTILS_H
