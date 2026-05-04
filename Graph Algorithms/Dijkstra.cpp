// O(E log V) — Single Source Shortest Path (directed/undirected, non-negative weights)
// dist[i] = shortest distance from s to i; parent[i] = predecessor on shortest path
// adj[u] = list of {v, weight} edges from u
#include <climits>
#include <queue>
#include <vector>

void dijkstra(int s, int n, std::vector<long long>& dist, std::vector<int>& parent,
              std::vector<std::pair<int, long long>>* adj) {
    const long long INF = LLONG_MAX / 2;
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[s] = 0;
    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>> q;
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
