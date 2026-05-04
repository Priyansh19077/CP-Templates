// O(V³) — All-Pairs Shortest Paths
// dist[i][j] = shortest distance from i to j after the call
// adj[u] = list of {v, weight} directed edges from u
// Check dist[i][i] < 0 after the call to detect negative cycles
#include <bits/stdc++.h>
using namespace std;

void floydWarshall(int n, vector<pair<int, long long>>* adj,
                   vector<vector<long long>>& dist) {
    const long long INF = LLONG_MAX / 2;
    dist.assign(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (auto [to, w] : adj[i])
            dist[i][to] = min(dist[i][to], w);
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
