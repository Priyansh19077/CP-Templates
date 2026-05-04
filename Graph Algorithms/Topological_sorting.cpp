// O(V+E) — Topological sort of a DAG via DFS post-order
// edges[u] = adjacency list of directed edges from u
// Returns nodes in topological order (undefined behaviour on cyclic graphs)
#include <bits/stdc++.h>
using namespace std;

void _topo_dfs(int u, vector<int>* edges, vector<bool>& visited, vector<int>& order) {
    visited[u] = true;
    for (int v : edges[u])
        if (!visited[v])
            _topo_dfs(v, edges, visited, order);
    order.push_back(u);
}

vector<int> topo_sort(int n, vector<int>* edges) {
    vector<bool> visited(n, false);
    vector<int> order;
    for (int i = 0; i < n; i++)
        if (!visited[i])
            _topo_dfs(i, edges, visited, order);
    reverse(order.begin(), order.end());
    return order;
}
