// O(E) — Find all Eulerian circuits in an undirected graph using Hierholzer's algorithm
// edges[u] = adjacency list (store each undirected edge ONCE, on one side only)
// Returns list of circuits; empty if any vertex has odd degree
#include <bits/stdc++.h>
using namespace std;

void _euler_dfs(int u, set<pair<int, int>>* edgeSet, vector<int>& path) {
    while (!edgeSet[u].empty()) {
        auto [v, id] = *edgeSet[u].begin();
        edgeSet[u].erase(edgeSet[u].begin());
        edgeSet[v].erase({u, id});
        _euler_dfs(v, edgeSet, path);
    }
    path.push_back(u);
}

vector<vector<int>> EulerCircuits(int n, vector<int>* edges) {
    set<pair<int, int>>* edgeSet = new set<pair<int, int>>[n];
    int id = 0;
    for (int u = 0; u < n; u++)
        for (int v : edges[u]) {
            edgeSet[u].insert({v, id});
            edgeSet[v].insert({u, id});
            id++;
        }

    for (int u = 0; u < n; u++)
        if ((int)edgeSet[u].size() & 1) return {};

    vector<vector<int>> circuits;
    for (int u = 0; u < n; u++) {
        if (!edgeSet[u].empty()) {
            vector<int> path;
            _euler_dfs(u, edgeSet, path);
            circuits.push_back(path);
        }
    }
    delete[] edgeSet;
    return circuits;
}
