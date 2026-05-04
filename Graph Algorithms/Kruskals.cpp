// O(E log E) — Minimum Spanning Tree via Kruskal's algorithm
// edges = list of {weight, u, v}; returns total MST weight
#include <algorithm>
#include <tuple>
#include <vector>

static int _kruskal_get(int a, std::vector<int>& parent) {
    return parent[a] = (parent[a] == a ? a : _kruskal_get(parent[a], parent));
}

long long kruskals(int n, std::vector<std::tuple<long long, int, int>>& edges) {
    std::sort(edges.begin(), edges.end());
    std::vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++) parent[i] = i;

    long long total = 0;
    int taken = 0;
    for (auto [w, u, v] : edges) {
        int pu = _kruskal_get(u, parent), pv = _kruskal_get(v, parent);
        if (pu == pv) continue;
        if (rank[pu] == rank[pv]) rank[pu]++;
        if (rank[pu] > rank[pv]) parent[pv] = pu;
        else parent[pu] = pv;
        total += w;
        if (++taken == n - 1) break;
    }
    return total;
}
