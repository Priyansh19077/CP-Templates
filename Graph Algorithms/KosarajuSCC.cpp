// O(V+E) — Strongly Connected Components via Kosaraju's algorithm
// edges[u] = forward adjacency list; edgesT[u] = reverse adjacency list
// Returns list of SCCs, each SCC is a vector of node indices
#include <algorithm>
#include <vector>

static void _scc_dfs_topo(int u, std::vector<int>* edges, std::vector<bool>& visited,
                           std::vector<int>& order) {
    visited[u] = true;
    for (int v : edges[u])
        if (!visited[v])
            _scc_dfs_topo(v, edges, visited, order);
    order.push_back(u);
}

static void _scc_dfs_collect(int u, std::vector<int>* edgesT, std::vector<bool>& visited,
                              std::vector<int>& comp) {
    comp.push_back(u);
    visited[u] = true;
    for (int v : edgesT[u])
        if (!visited[v])
            _scc_dfs_collect(v, edgesT, visited, comp);
}

std::vector<std::vector<int>> getSCC(int n, std::vector<int>* edges, std::vector<int>* edgesT) {
    std::vector<bool> visited(n, false);
    std::vector<int> order;
    for (int i = 0; i < n; i++)
        if (!visited[i])
            _scc_dfs_topo(i, edges, visited, order);

    std::fill(visited.begin(), visited.end(), false);
    std::vector<std::vector<int>> scc;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        if (!visited[order[i]]) {
            std::vector<int> comp;
            _scc_dfs_collect(order[i], edgesT, visited, comp);
            scc.push_back(comp);
        }
    }
    return scc;
}
