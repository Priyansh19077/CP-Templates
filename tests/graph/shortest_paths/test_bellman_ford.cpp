#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/Shortest Paths/BellmanFord.cpp"

using namespace std;

vector<pair<int, long long>>* make_adj(const WAdj& g, int n) {
    auto* adj = new vector<pair<int, long long>>[n];
    for (int u = 0; u < n; u++) {
        adj[u] = g[u];
    }
    return adj;
}

int run_tests() {
    // --- Small known graph with positive weights ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 1});
        g[1].push_back({2, 3});
        g[0].push_back({2, 10});
        g[2].push_back({3, 2});
        auto* adj = make_adj(g, n);
        vector<long long> dist(n, INF); set<int> neg;
        bellmanFord(n, 0, adj, dist, neg);
        ASSERT_EQ(dist[0], 0);
        ASSERT_EQ(dist[1], 1);
        ASSERT_EQ(dist[2], 4);
        ASSERT_EQ(dist[3], 6);
        ASSERT_TRUE(neg.empty());
        delete[] adj;
    }

    // --- Negative weight edge (no cycle) ---
    {
        int n = 3;
        WAdj g(n);
        g[0].push_back({1, 4});
        g[1].push_back({2, -2});
        g[0].push_back({2, 5});
        auto* adj = make_adj(g, n);
        vector<long long> dist(n, INF); set<int> neg;
        bellmanFord(n, 0, adj, dist, neg);
        ASSERT_EQ(dist[0], 0);
        ASSERT_EQ(dist[1], 4);
        ASSERT_EQ(dist[2], 2);
        ASSERT_TRUE(neg.empty());
        delete[] adj;
    }

    // --- Negative cycle detected ---
    {
        int n = 3;
        WAdj g(n);
        g[0].push_back({1, 1});
        g[1].push_back({2, -3});
        g[2].push_back({1, 1}); // 1→2→1 cycle with weight -2
        auto* adj = make_adj(g, n);
        vector<long long> dist(n, INF); set<int> neg;
        bellmanFord(n, 0, adj, dist, neg);
        ASSERT_TRUE(!neg.empty());
        delete[] adj;
    }

    // --- Disconnected node stays INF ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 2});
        g[1].push_back({2, 3});
        // node 3 isolated
        auto* adj = make_adj(g, n);
        vector<long long> dist(n, INF); set<int> neg;
        bellmanFord(n, 0, adj, dist, neg);
        ASSERT_EQ(dist[3], INF);
        delete[] adj;
    }

    // --- Single node ---
    {
        int n = 1;
        WAdj g(n);
        auto* adj = make_adj(g, n);
        vector<long long> dist(n, INF); set<int> neg;
        bellmanFord(n, 0, adj, dist, neg);
        ASSERT_EQ(dist[0], 0);
        delete[] adj;
    }

    // --- Stress test: verify against brute_sssp on random positive-weight graphs ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 80;
        WAdj g = gen_connected_weighted(n, n / 2, 100, rng);
        auto* adj = make_adj(g, n);
        int src = rng() % n;
        vector<long long> dist(n, INF); set<int> neg;
        bellmanFord(n, src, adj, dist, neg);
        vector<long long> expected = brute_sssp(g, n, src);
        for (int i = 0; i < n; i++) {
            if (dist[i] != expected[i]) cerr << "Stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(dist[i], expected[i]);
        }
        ASSERT_TRUE(neg.empty());
        delete[] adj;
    }

    // --- Stress test: many random directed graphs, no negative cycles ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 30; t++) {
            int n = 5 + rng() % 20;
            WAdj g(n);
            int m = n + rng() % (n * 2);
            for (int i = 0; i < m; i++) {
                int u = rng() % n, v = rng() % n;
                long long w = rng() % 50 + 1;
                g[u].push_back({v, w});
            }
            auto* adj = make_adj(g, n);
            int src = rng() % n;
            vector<long long> dist(n, INF); set<int> neg;
            bellmanFord(n, src, adj, dist, neg);
            vector<long long> expected = brute_sssp(g, n, src);
            for (int i = 0; i < n; i++) {
                if (dist[i] != expected[i]) cerr << "Stress test failed (seed=" << seed << ")\n";
                ASSERT_EQ(dist[i], expected[i]);
            }
            delete[] adj;
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
