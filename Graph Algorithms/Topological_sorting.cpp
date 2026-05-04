// O(V+E) — Topological sort of a DAG via DFS post-order
// edges[u] = adjacency list of directed edges from u
// Returns nodes in topological order (undefined behaviour on cyclic graphs)
#include <algorithm>
#include <vector>

static void _topo_dfs(int u, std::vector<int>* edges, std::vector<bool>& visited,
                      std::vector<int>& order) {
    visited[u] = true;
    for (int v : edges[u])
        if (!visited[v])
            _topo_dfs(v, edges, visited, order);
    order.push_back(u);
}

std::vector<int> topo_sort(int n, std::vector<int>* edges) {
    std::vector<bool> visited(n, false);
    std::vector<int> order;
    for (int i = 0; i < n; i++)
        if (!visited[i])
            _topo_dfs(i, edges, visited, order);
    std::reverse(order.begin(), order.end());
    return order;
}
