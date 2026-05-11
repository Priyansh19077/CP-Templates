#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/DAG/CycleInDAG.cpp"

using namespace std;

vector<int>* make_adj(const Adj& g, int n) {
    auto* adj = new vector<int>[n];
    for (int u = 0; u < n; u++) adj[u] = g[u];
    return adj;
}

int run_tests() {
    // --- Acyclic: linear chain ---
    {
        int n = 4;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(2); g[2].push_back(3);
        auto* adj = make_adj(g, n);
        ASSERT_FALSE(hasCycle(n, adj));
        delete[] adj;
    }

    // --- Simple cycle: 0→1→2→0 ---
    {
        int n = 3;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(2); g[2].push_back(0);
        auto* adj = make_adj(g, n);
        ASSERT_TRUE(hasCycle(n, adj));
        delete[] adj;
    }

    // --- Self-loop ---
    {
        int n = 3;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(1); // self-loop on 1
        auto* adj = make_adj(g, n);
        ASSERT_TRUE(hasCycle(n, adj));
        delete[] adj;
    }

    // --- Diamond (DAG): no cycle ---
    {
        int n = 4;
        Adj g(n);
        g[0].push_back(1); g[0].push_back(2);
        g[1].push_back(3); g[2].push_back(3);
        auto* adj = make_adj(g, n);
        ASSERT_FALSE(hasCycle(n, adj));
        delete[] adj;
    }

    // --- Single node, no edges ---
    {
        int n = 1;
        Adj g(n);
        auto* adj = make_adj(g, n);
        ASSERT_FALSE(hasCycle(n, adj));
        delete[] adj;
    }

    // --- Stress test: random DAGs should have no cycle ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 30; t++) {
            int n = 5 + rng() % 15;
            Adj g = gen_dag(n, n + rng() % (n * 2), rng);
            auto* adj = make_adj(g, n);
            bool got = hasCycle(n, adj);
            bool expected = brute_has_cycle(g, n);
            if (got != expected)
                cerr << "Stress test failed (seed=" << seed << " t=" << t << ")\n";
            ASSERT_EQ(got, expected);
            delete[] adj;
        }
    }

    // --- Stress test: random directed graphs, compare with brute_has_cycle ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 30; t++) {
            int n = 5 + rng() % 15;
            Adj g = gen_directed(n, n + rng() % (n * 2), rng);
            auto* adj = make_adj(g, n);
            bool got = hasCycle(n, adj);
            bool expected = brute_has_cycle(g, n);
            if (got != expected)
                cerr << "Stress test failed (seed=" << seed << " t=" << t << ")\n";
            ASSERT_EQ(got, expected);
            delete[] adj;
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
