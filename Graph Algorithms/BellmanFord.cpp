// O(VE) — Single Source Shortest Path; handles negative weights and detects negative cycles
// edges[u] = list of {v, weight}; negCycle is filled with nodes on or reachable via negative cycles
#include <bits/stdc++.h>
using namespace std;

void bellmanFord(int n, int src, vector<pair<int, long long>>* edges,
                 vector<long long>& dist, set<int>& negCycle) {
    const long long INF = LLONG_MAX / 2;
    dist.assign(n, INF);
    dist[src] = 0;

    vector<pair<long long, pair<int, int>>> e;
    for (int i = 0; i < n; i++)
        for (auto [to, w] : edges[i])
            e.push_back({w, {i, to}});

    for (int i = 0; i < n - 1; i++)
        for (auto [w, edge] : e)
            if (dist[edge.first] < INF)
                dist[edge.second] = min(dist[edge.second], dist[edge.first] + w);

    for (int i = 0; i < n; i++)
        for (auto [w, edge] : e)
            if (dist[edge.first] < INF && dist[edge.second] > dist[edge.first] + w) {
                dist[edge.second] = dist[edge.first] + w;
                negCycle.insert(edge.second);
            }
}
