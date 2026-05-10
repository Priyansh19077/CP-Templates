// O((V + E) log V) — Minimum Spanning Tree via Prim's algorithm
// adj[u] = list of {v, weight} (0-indexed nodes, undirected graph)
// Returns {total MST weight, list of {u, v} MST edges}; weight = -1 if disconnected
#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;

pair<long long, vector<pair<int, int>>> prims(int n, vector<pair<int, long long>>* adj) {
    vector<long long> dist(n, INF);
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    set<pair<long long, int>> pq;
    dist[0] = 0;
    pq.insert({0, 0});
    long long totalWeight = 0;
    int count = 0;
    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        visited[u] = true;
        totalWeight += d;
        count++;
        for (auto [v, w] : adj[u]) {
            if (!visited[v] && w < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = w;
                parent[v] = u;
                pq.insert({dist[v], v});
            }
        }
    }
    if (count < n) {
        return {-1, {}};
    }
    vector<pair<int, int>> mstEdges;
    for (int i = 1; i < n; i++) {
        mstEdges.push_back({parent[i], i});
    }
    return {totalWeight, mstEdges};
}
