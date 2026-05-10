#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/Shortest Paths/FloydWarshall.cpp"

using namespace std;

vector<pair<int, long long>>* make_adj(const WAdj& g, int n) {
    auto* adj = new vector<pair<int, long long>>[n];
    for (int u = 0; u < n; u++) {
        adj[u] = g[u];
    }
    return adj;
}

int run_tests() {
    // --- Small known graph ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 3});
        g[0].push_back({2, 6});
        g[1].push_back({3, 2});
        g[2].push_back({3, 1});
        g[1].push_back({2, 1});
        auto* adj = make_adj(g, n);
        vector<vector<long long>> dist;
        floydWarshall(n, adj, dist);
        ASSERT_EQ(dist[0][3], 5);  // 0→1→3 = 3+2
        ASSERT_EQ(dist[0][2], 4);  // 0→1→2 = 3+1
        ASSERT_EQ(dist[1][3], 2);
        ASSERT_EQ(dist[0][0], 0);
        ASSERT_EQ(dist[3][0], INF); // directed, no back edges
        delete[] adj;
    }

    // --- Single node ---
    {
        int n = 1;
        WAdj g(n);
        auto* adj = make_adj(g, n);
        vector<vector<long long>> dist;
        floydWarshall(n, adj, dist);
        ASSERT_EQ(dist[0][0], 0);
        delete[] adj;
    }

    // --- Two nodes, single directed edge ---
    {
        int n = 2;
        WAdj g(n);
        g[0].push_back({1, 5});
        auto* adj = make_adj(g, n);
        vector<vector<long long>> dist;
        floydWarshall(n, adj, dist);
        ASSERT_EQ(dist[0][1], 5);
        ASSERT_EQ(dist[1][0], INF);
        delete[] adj;
    }

    // --- Transitive path beats direct ---
    {
        int n = 3;
        WAdj g(n);
        g[0].push_back({2, 10});
        g[0].push_back({1, 2});
        g[1].push_back({2, 3});
        auto* adj = make_adj(g, n);
        vector<vector<long long>> dist;
        floydWarshall(n, adj, dist);
        ASSERT_EQ(dist[0][2], 5); // 0→1→2
        delete[] adj;
    }

    // --- Stress test: compare against brute_apsp on random graphs ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 50;
        WAdj g = gen_connected_weighted(n, n / 2, 100, rng);
        auto* adj = make_adj(g, n);
        vector<vector<long long>> dist;
        floydWarshall(n, adj, dist);
        auto expected = brute_apsp(g, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] != expected[i][j]) cerr << "Stress test failed (seed=" << seed << ")\n";
                ASSERT_EQ(dist[i][j], expected[i][j]);
            }
        }
        delete[] adj;
    }

    // --- Stress test: random directed sparse graphs ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 20; t++) {
            int n = 5 + rng() % 15;
            WAdj g(n);
            int m = n + rng() % (n * 2);
            for (int i = 0; i < m; i++) {
                int u = rng() % n, v = rng() % n;
                long long w = rng() % 50 + 1;
                g[u].push_back({v, w});
            }
            auto* adj = make_adj(g, n);
            vector<vector<long long>> dist;
            floydWarshall(n, adj, dist);
            auto expected = brute_apsp(g, n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] != expected[i][j]) cerr << "Stress test failed (seed=" << seed << ")\n";
                    ASSERT_EQ(dist[i][j], expected[i][j]);
                }
            }
            delete[] adj;
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
