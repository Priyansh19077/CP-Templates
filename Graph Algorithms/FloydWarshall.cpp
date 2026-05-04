// O(V³) — All-Pairs Shortest Paths
// dist[i][j] = shortest distance from i to j after the call
// adj[u] = list of {v, weight} directed edges from u
// Note: check dist[i][i] < 0 after the call to detect negative cycles
#include <climits>
#include <vector>

void floydWarshall(int n, std::vector<std::pair<int, long long>>* adj,
                   std::vector<std::vector<long long>>& dist) {
    const long long INF = LLONG_MAX / 2;
    dist.assign(n, std::vector<long long>(n, INF));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (auto [to, w] : adj[i])
            dist[i][to] = std::min(dist[i][to], w);
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
}
