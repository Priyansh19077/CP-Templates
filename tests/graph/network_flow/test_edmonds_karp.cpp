#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/Network Flow/EdmondsKarp.cpp"

using namespace std;

vector<pair<int, long long>>* make_adj(const WAdj& g, int n) {
    auto* adj = new vector<pair<int, long long>>[n];
    for (int u = 0; u < n; u++) {
        adj[u] = g[u];
    }
    return adj;
}

// Build capacity matrix from WAdj for brute_max_flow reference
vector<vector<long long>> make_cap(const WAdj& g, int n) {
    vector<vector<long long>> cap(n, vector<long long>(n, 0));
    for (int u = 0; u < n; u++) {
        for (auto [v, c] : g[u]) {
            cap[u][v] += c;
        }
    }
    return cap;
}

int run_tests() {
    // --- Small known graph: same as Ford-Fulkerson test ---
    // 0→1 (10), 0→2 (5), 1→3 (7), 2→3 (8); max flow = 12
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 10});
        g[0].push_back({2, 5});
        g[1].push_back({3, 7});
        g[2].push_back({3, 8});
        auto* adj = make_adj(g, n);
        Flow f(adj, n, 0, 3);
        ASSERT_EQ(f.maxFlow(), 12);
        delete[] adj;
    }

    // --- No path from src to sink ---
    {
        int n = 3;
        WAdj g(n);
        g[0].push_back({1, 5}); // no edge to node 2
        auto* adj = make_adj(g, n);
        Flow f(adj, n, 0, 2);
        ASSERT_EQ(f.maxFlow(), 0);
        delete[] adj;
    }

    // --- Single bottleneck edge ---
    {
        int n = 4;
        WAdj g(n);
        g[0].push_back({1, 100});
        g[1].push_back({2, 3}); // bottleneck
        g[2].push_back({3, 100});
        auto* adj = make_adj(g, n);
        Flow f(adj, n, 0, 3);
        ASSERT_EQ(f.maxFlow(), 3);
        delete[] adj;
    }

    // --- Two nodes, direct edge ---
    {
        int n = 2;
        WAdj g(n);
        g[0].push_back({1, 7});
        auto* adj = make_adj(g, n);
        Flow f(adj, n, 0, 1);
        ASSERT_EQ(f.maxFlow(), 7);
        delete[] adj;
    }

    // --- maxFlow() is idempotent (calling twice returns same value) ---
    {
        int n = 3;
        WAdj g(n);
        g[0].push_back({1, 4});
        g[1].push_back({2, 6});
        auto* adj = make_adj(g, n);
        Flow f(adj, n, 0, 2);
        long long first = f.maxFlow();
        long long second = f.maxFlow();
        ASSERT_EQ(first, second);
        delete[] adj;
    }

    // --- Stress test: compare against brute_max_flow ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 20; t++) {
            int n = 4 + rng() % 8;
            WAdj g = gen_flow_network(n, 20, rng);
            auto* adj = make_adj(g, n);
            Flow f(adj, n, 0, n - 1);
            long long got = f.maxFlow();
            long long expected = brute_max_flow(n, make_cap(g, n), 0, n - 1);
            if (got != expected) cerr << "Stress test failed (seed=" << seed << " t=" << t << ")\n";
            ASSERT_EQ(got, expected);
            delete[] adj;
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
