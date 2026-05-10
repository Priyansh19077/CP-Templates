// O(VE) — Single-source shortest path; handles negative weights and negative cycle detection
// dist[i] = shortest distance from src; negCycle = nodes whose distance can still be reduced
// edges[u] = list of {v, weight}
#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;

void bellmanFord(int n, int src, vector<pair<int, long long>>* edges, vector<long long>& dist, set<int>& negCycle) {
    dist.assign(n, INF);
    dist[src] = 0;
    vector<tuple<long long, int, int>> e;
    for (int i = 0; i < n; i++) {
        for (auto [dst, w] : edges[i]) {
            e.push_back({w, i, dst});
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (auto [w, u, v] : e) {
            if (dist[u] < INF) {
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }
    // Nodes whose distance can still be reduced lie on or are reachable from a negative cycle
    for (int i = 0; i < n; i++) {
        for (auto [w, u, v] : e) {
            if (dist[u] < INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                negCycle.insert(v);
            }
        }
    }
}
