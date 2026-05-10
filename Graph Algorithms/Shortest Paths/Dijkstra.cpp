// O(E log V) — Single-source shortest path (non-negative weights)
// dist[i] = shortest distance from src; parent[i] = previous node on shortest path
// adj[u] = list of {v, weight}
#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;

void dijkstra(int src, int n, vector<long long>& dist, vector<int>& parent, vector<pair<int, long long>>* adj) {
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[src] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) {
            continue;
        }
        for (auto [u, w] : adj[v]) {
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                parent[u] = v;
                pq.push({dist[u], u});
            }
        }
    }
}
