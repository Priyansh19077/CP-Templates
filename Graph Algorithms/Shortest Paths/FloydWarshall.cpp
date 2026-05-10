// O(V³) — All-pairs shortest paths
// dist[i][j] = shortest distance from i to j; INF if no path exists
// Check dist[i][i] < 0 after the algorithm to detect negative cycles
// Maintain parent[i][j] for path reconstruction
// adj[u] = list of {v, weight}
#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;

void floydWarshall(int n, vector<pair<int, long long>>* adj, vector<vector<long long>>& dist) {
    dist.assign(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (auto [j, w] : adj[i]) {
            dist[i][j] = min(dist[i][j], w);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) { // guard against overflow
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}
