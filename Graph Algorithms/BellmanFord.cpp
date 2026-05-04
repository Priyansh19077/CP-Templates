// O(VE) — Single Source Shortest Path; handles negative weights and detects negative cycles
// edges[u] = list of {v, weight}; negCycle is filled with nodes on or reachable via negative cycles
#include <climits>
#include <set>
#include <vector>

void bellmanFord(int n, int src, std::vector<std::pair<int, long long>>* edges,
                 std::vector<long long>& dist, std::set<int>& negCycle) {
    const long long INF = LLONG_MAX / 2;
    dist.assign(n, INF);
    dist[src] = 0;

    // Build flat edge list {weight, {from, to}}
    std::vector<std::pair<long long, std::pair<int, int>>> e;
    for (int i = 0; i < n; i++)
        for (auto [to, w] : edges[i])
            e.push_back({w, {i, to}});

    for (int i = 0; i < n - 1; i++)
        for (auto [w, edge] : e)
            if (dist[edge.first] < INF)
                dist[edge.second] = std::min(dist[edge.second], dist[edge.first] + w);

    // Extra relaxation round detects negative cycles
    for (int i = 0; i < n; i++)
        for (auto [w, edge] : e)
            if (dist[edge.first] < INF && dist[edge.second] > dist[edge.first] + w) {
                dist[edge.second] = dist[edge.first] + w;
                negCycle.insert(edge.second);
            }
}
