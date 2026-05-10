#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/Shortest Paths/Dijkstra.cpp"

using namespace std;

// Helper: build raw adj array from WAdj for dijkstra()
vector<pair<int, long long>>* make_adj(const WAdj& g, int n) {
    auto* adj = new vector<pair<int, long long>>[n];
    for (int u = 0; u < n; u++) {
        adj[u] = g[u];
    }
    return adj;
}

int run_tests() {
    // --- Small known graph ---
    // 0 -1- 1 -2- 2
    //  \         /
    //   ---4----
    {
        int n = 3;
        WAdj g(n);
        g[0].push_back({1, 1}); g[1].push_back({0, 1});
        g[1].push_back({2, 2}); g[2].push_back({1, 2});
        g[0].push_back({2, 4}); g[2].push_back({0, 4});
        auto* adj = make_adj(g, n);
        vector<long long> dist; vector<int> par;
        dijkstra(0, n, dist, par, adj);
        ASSERT_EQ(dist[0], 0);
        ASSERT_EQ(dist[1], 1);
        ASSERT_EQ(dist[2], 3);
        delete[] adj;
    }

    // --- Single node ---
    {
        int n = 1;
        WAdj g(n);
        auto* adj = make_adj(g, n);
        vector<long long> dist; vector<int> par;
        dijkstra(0, n, dist, par, adj);
        ASSERT_EQ(dist[0], 0);
        delete[] adj;
    }

    // --- Disconnected node stays INF ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 5}); g[1].push_back({0, 5});
        g[0].push_back({2, 3}); g[2].push_back({0, 3});
        // node 3 is isolated
        auto* adj = make_adj(g, n);
        vector<long long> dist; vector<int> par;
        dijkstra(0, n, dist, par, adj);
        ASSERT_EQ(dist[0], 0);
        ASSERT_EQ(dist[1], 5);
        ASSERT_EQ(dist[2], 3);
        ASSERT_EQ(dist[3], INF);
        delete[] adj;
    }

    // --- Source is not node 0 ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 1}); g[1].push_back({0, 1});
        g[1].push_back({2, 2}); g[2].push_back({1, 2});
        g[2].push_back({3, 1}); g[3].push_back({2, 1});
        auto* adj = make_adj(g, n);
        vector<long long> dist; vector<int> par;
        dijkstra(2, n, dist, par, adj);
        ASSERT_EQ(dist[2], 0);
        ASSERT_EQ(dist[1], 2);
        ASSERT_EQ(dist[3], 1);
        ASSERT_EQ(dist[0], 3);
        delete[] adj;
    }

    // --- Two nodes, single edge ---
    {
        int n = 2;
        WAdj g(n);
        g[0].push_back({1, 7}); g[1].push_back({0, 7});
        auto* adj = make_adj(g, n);
        vector<long long> dist; vector<int> par;
        dijkstra(0, n, dist, par, adj);
        ASSERT_EQ(dist[0], 0);
        ASSERT_EQ(dist[1], 7);
        delete[] adj;
    }

    // --- Stress test: verify against brute_sssp (Bellman-Ford) ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 100;
        WAdj g = gen_connected_weighted(n, n / 2, 100, rng);
        auto* adj = make_adj(g, n);
        int src = rng() % n;
        vector<long long> dist; vector<int> par;
        dijkstra(src, n, dist, par, adj);
        vector<long long> expected = brute_sssp(g, n, src);
        for (int i = 0; i < n; i++) {
            if (dist[i] != expected[i]) cerr << "Stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(dist[i], expected[i]);
        }
        delete[] adj;
    }

    // --- Stress test: multiple random sources ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 80;
        WAdj g = gen_connected_weighted(n, n, 200, rng);
        auto* adj = make_adj(g, n);
        for (int t = 0; t < 20; t++) {
            int src = rng() % n;
            vector<long long> dist; vector<int> par;
            dijkstra(src, n, dist, par, adj);
            vector<long long> expected = brute_sssp(g, n, src);
            for (int i = 0; i < n; i++) {
                if (dist[i] != expected[i]) cerr << "Stress test failed (seed=" << seed << ")\n";
                ASSERT_EQ(dist[i], expected[i]);
            }
        }
        delete[] adj;
    }

    TEST_PASS();
}

int main() { return run_tests(); }
