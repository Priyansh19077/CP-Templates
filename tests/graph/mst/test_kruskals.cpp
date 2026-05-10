#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/MST/Kruskals.cpp"

using namespace std;

// Build edge list from undirected WAdj (each undirected edge stored once)
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
    // --- Small known graph ---
    // 0 -1- 1 -2- 2 -3- 3
    //  \___________5___/
    //       \___10___/
    {
        int n = 4;
        vector<tuple<long long, int, int>> edges = {
            {1, 0, 1}, {2, 1, 2}, {3, 2, 3}, {5, 0, 2}, {10, 0, 3}
        };
        auto [w, mst] = kruskal(n, edges);
        ASSERT_EQ(w, 6); // 1 + 2 + 3
        ASSERT_TRUE(is_spanning_tree(n, mst));
    }

    // --- Single node ---
    {
        int n = 1;
        vector<tuple<long long, int, int>> edges;
        auto [w, mst] = kruskal(n, edges);
        ASSERT_EQ(w, 0);
        ASSERT_EQ((int)mst.size(), 0);
    }

    // --- Two nodes, single edge ---
    {
        int n = 2;
        vector<tuple<long long, int, int>> edges = {{7, 0, 1}};
        auto [w, mst] = kruskal(n, edges);
        ASSERT_EQ(w, 7);
        ASSERT_TRUE(is_spanning_tree(n, mst));
    }

    // --- Disconnected graph returns -1 ---
    {
        int n = 4;
        vector<tuple<long long, int, int>> edges = {
            {1, 0, 1}, {2, 2, 3}
        };
        auto [w, mst] = kruskal(n, edges);
        ASSERT_EQ(w, -1);
        ASSERT_TRUE(mst.empty());
    }

    // --- Parallel edges: picks the lighter one ---
    {
        int n = 2;
        vector<tuple<long long, int, int>> edges = {{5, 0, 1}, {3, 0, 1}};
        auto [w, mst] = kruskal(n, edges);
        ASSERT_EQ(w, 3);
    }

    // --- Stress test: weight matches brute_mst_weight on random graphs ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 30; t++) {
            int n = 5 + rng() % 20;
            WAdj g = gen_connected_weighted(n, n / 2, 100, rng);
            auto edges = make_edges(g, n);
            auto [w, mst] = kruskal(n, edges);
            long long expected = brute_mst_weight(n, edges);
            if (w != expected) cerr << "Stress test failed (seed=" << seed << " t=" << t << ")\n";
            ASSERT_EQ(w, expected);
            ASSERT_TRUE(is_spanning_tree(n, mst));
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
