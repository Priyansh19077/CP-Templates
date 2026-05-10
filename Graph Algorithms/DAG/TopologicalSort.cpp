// O(V + E) — Topological sort via DFS post-order
// edges[u] = list of directed neighbors (0-indexed)
// Returns nodes in topological order; result is undefined if graph has a cycle
#include <bits/stdc++.h>
using namespace std;

void topoSortDFS(int start, vector<int>* edges, vector<bool>& visited, vector<int>& order) {
    visited[start] = true;
    for (int i : edges[start]) {
        if (!visited[i]) {
            topoSortDFS(i, edges, visited, order);
        }
    }
    order.push_back(start);
}

vector<int> topoSort(int n, vector<int>* edges) {
    vector<int> order;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topoSortDFS(i, edges, visited, order);
        }
    }
    reverse(order.begin(), order.end());
    return order;
}
