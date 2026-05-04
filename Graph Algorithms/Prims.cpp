// O(E log V) — Minimum Spanning Tree via Prim's algorithm (set-based priority queue)
// edges[u] = list of {v, weight} for undirected graph; returns total MST weight
#include <bits/stdc++.h>
using namespace std;

long long prims(int n, vector<pair<int, long long>>* edges) {
    if (n <= 1) return 0;
    const long long INF = LLONG_MAX / 2;
    vector<long long> dist(n, INF);
    vector<bool> visited(n, false);
    dist[0] = 0;
    set<pair<long long, int>> pq;
    pq.insert({0, 0});
    long long total = 0;

    for (int i = 0; i < n; i++) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        visited[u] = true;
        total += d;
        for (auto [v, w] : edges[u]) {
            if (!visited[v] && w < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = w;
                pq.insert({dist[v], v});
            }
        }
    }
    return total;
}
