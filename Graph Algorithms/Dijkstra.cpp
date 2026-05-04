// O(E log V) — Single Source Shortest Path (directed/undirected, non-negative weights)
// dist[i] = shortest distance from s to i; parent[i] = predecessor on shortest path
// adj[u] = list of {v, weight} edges from u
#include <bits/stdc++.h>
using namespace std;

void dijkstra(int s, int n, vector<long long>& dist, vector<int>& parent,
              vector<pair<int, long long>>* adj) {
    const long long INF = LLONG_MAX / 2;
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[s] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d_v, v] = q.top();
        q.pop();
        if (d_v != dist[v]) continue;
        for (auto [to, w] : adj[v]) {
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                parent[to] = v;
                q.push({dist[to], to});
            }
        }
    }
}
