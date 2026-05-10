#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/MST/Prims.cpp"

using namespace std;

vector<pair<int, long long>>* make_adj(const WAdj& g, int n) {
    auto* adj = new vector<pair<int, long long>>[n];
    for (int u = 0; u < n; u++) {
        adj[u] = g[u];
    }
    return adj;
}

// Build edge list from undirected WAdj for brute_mst_weight reference
vector<tuple<long long, int, int>> make_edges(const WAdj& g, int n) {
    vector<tuple<long long, int, int>> edges;
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : g[u]) {
            if (u < v) edges.push_back({w, u, v});
        }
    }
    return edges;
}

int run_tests() {
    // --- Small known graph (same as Kruskal test) ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 1}); g[1].push_back({0, 1});
        g[1].push_back({2, 2}); g[2].push_back({1, 2});
        g[2].push_back({3, 3}); g[3].push_back({2, 3});
        g[0].push_back({2, 5}); g[2].push_back({0, 5});
        g[0].push_back({3, 10}); g[3].push_back({0, 10});
        auto* adj = make_adj(g, n);
        auto [w, mst] = prims(n, adj);
        ASSERT_EQ(w, 6); // 1 + 2 + 3
        ASSERT_TRUE(is_spanning_tree(n, mst));
        delete[] adj;
    }

    // --- Single node ---
    {
        int n = 1;
        WAdj g(n);
        auto* adj = make_adj(g, n);
        auto [w, mst] = prims(n, adj);
        ASSERT_EQ(w, 0);
        ASSERT_EQ((int)mst.size(), 0);
        delete[] adj;
    }

    // --- Two nodes, single edge ---
    {
        int n = 2;
        WAdj g(n);
        g[0].push_back({1, 7}); g[1].push_back({0, 7});
        auto* adj = make_adj(g, n);
        auto [w, mst] = prims(n, adj);
        ASSERT_EQ(w, 7);
        ASSERT_TRUE(is_spanning_tree(n, mst));
        delete[] adj;
    }

    // --- Disconnected graph returns -1 ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 1}); g[1].push_back({0, 1});
        // nodes 2 and 3 isolated
        auto* adj = make_adj(g, n);
        auto [w, mst] = prims(n, adj);
        ASSERT_EQ(w, -1);
        ASSERT_TRUE(mst.empty());
        delete[] adj;
    }

    // --- Parallel edges: MST picks the lighter one ---
    {
        int n = 2;
        WAdj g(n);
        g[0].push_back({1, 5}); g[1].push_back({0, 5});
        g[0].push_back({1, 3}); g[1].push_back({0, 3});
        auto* adj = make_adj(g, n);
        auto [w, mst] = prims(n, adj);
        ASSERT_EQ(w, 3);
        delete[] adj;
    }

    // --- Stress test: weight matches brute_mst_weight, MST is a spanning tree ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 30; t++) {
            int n = 5 + rng() % 20;
            WAdj g = gen_connected_weighted(n, n / 2, 100, rng);
            auto* adj = make_adj(g, n);
            auto [w, mst] = prims(n, adj);
            auto edges = make_edges(g, n);
            long long expected = brute_mst_weight(n, edges);
            if (w != expected) cerr << "Stress test failed (seed=" << seed << " t=" << t << ")\n";
            ASSERT_EQ(w, expected);
            ASSERT_TRUE(is_spanning_tree(n, mst));
            delete[] adj;
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
