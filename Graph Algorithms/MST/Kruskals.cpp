// O(E log E) — Minimum Spanning Tree via Kruskal's algorithm
// edges: list of {weight, u, v} (0-indexed nodes)
// Returns {total MST weight, list of {u, v} MST edges}; weight = -1 if disconnected
#include <bits/stdc++.h>
using namespace std;

int kruskalGet(int a, vector<int>& parent) {
    return parent[a] = (parent[a] == a ? a : kruskalGet(parent[a], parent));
}

void kruskalMerge(int a, int b, vector<int>& rank, vector<int>& parent) {
    a = kruskalGet(a, parent);
    b = kruskalGet(b, parent);
    if (a == b) {
        return;
    }
    if (rank[a] == rank[b]) {
        rank[a]++;
    }
    if (rank[a] > rank[b]) {
        parent[b] = a;
    } else {
        parent[a] = b;
    }
}

pair<long long, vector<pair<int, int>>> kruskal(int n, vector<tuple<long long, int, int>> edges) {
    sort(edges.begin(), edges.end());
    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    long long totalWeight = 0;
    vector<pair<int, int>> mstEdges;
    for (auto [w, u, v] : edges) {
        if ((int)mstEdges.size() == n - 1) {
            break;
        }
        if (kruskalGet(u, parent) != kruskalGet(v, parent)) {
            kruskalMerge(u, v, rank, parent);
            totalWeight += w;
            mstEdges.push_back({u, v});
        }
    }
    if ((int)mstEdges.size() < n - 1) {
        return {-1, {}};
    }
    return {totalWeight, mstEdges};
}
