// O(V+E) — Strongly Connected Components via Kosaraju's algorithm
// edges[u] = forward adjacency list; edgesT[u] = reverse adjacency list
// Returns list of SCCs, each SCC is a vector of node indices
#include <bits/stdc++.h>
using namespace std;

void _scc_dfs_topo(int u, vector<int>* edges, vector<bool>& visited, vector<int>& order) {
    visited[u] = true;
    for (int v : edges[u])
        if (!visited[v])
            _scc_dfs_topo(v, edges, visited, order);
    order.push_back(u);
}

void _scc_dfs_collect(int u, vector<int>* edgesT, vector<bool>& visited, vector<int>& comp) {
    comp.push_back(u);
    visited[u] = true;
    for (int v : edgesT[u])
        if (!visited[v])
            _scc_dfs_collect(v, edgesT, visited, comp);
}

vector<vector<int>> getSCC(int n, vector<int>* edges, vector<int>* edgesT) {
    vector<bool> visited(n, false);
    vector<int> order;
    for (int i = 0; i < n; i++)
        if (!visited[i])
            _scc_dfs_topo(i, edges, visited, order);

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> scc;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        if (!visited[order[i]]) {
            vector<int> comp;
            _scc_dfs_collect(order[i], edgesT, visited, comp);
            scc.push_back(comp);
        }
    }
    return scc;
}
