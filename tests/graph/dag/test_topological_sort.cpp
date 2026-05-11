#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/DAG/TopologicalSort.cpp"

using namespace std;

vector<int>* make_adj(const Adj& g, int n) {
    auto* adj = new vector<int>[n];
    for (int u = 0; u < n; u++) adj[u] = g[u];
    return adj;
}

int run_tests() {
    // --- Simple linear chain: 0→1→2→3 ---
    {
        int n = 4;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(2); g[2].push_back(3);
        auto* adj = make_adj(g, n);
        auto order = topoSort(n, adj);
        ASSERT_TRUE(is_valid_topo_order(g, n, order));
        delete[] adj;
    }

    // --- Diamond: 0→1, 0→2, 1→3, 2→3 ---
    {
        int n = 4;
        Adj g(n);
        g[0].push_back(1); g[0].push_back(2);
        g[1].push_back(3); g[2].push_back(3);
        auto* adj = make_adj(g, n);
        auto order = topoSort(n, adj);
        ASSERT_TRUE(is_valid_topo_order(g, n, order));
        delete[] adj;
    }

    // --- Single node ---
    {
        int n = 1;
        Adj g(n);
        auto* adj = make_adj(g, n);
        auto order = topoSort(n, adj);
        ASSERT_EQ((int)order.size(), 1);
        ASSERT_EQ(order[0], 0);
        delete[] adj;
    }

    // --- No edges: any permutation is valid ---
    {
        int n = 5;
        Adj g(n);
        auto* adj = make_adj(g, n);
        auto order = topoSort(n, adj);
        ASSERT_EQ((int)order.size(), n);
        ASSERT_TRUE(is_valid_topo_order(g, n, order));
        delete[] adj;
    }

    // --- Stress test: random DAGs produce valid topological orders ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 30; t++) {
            int n = 5 + rng() % 15;
            Adj g = gen_dag(n, n + rng() % (n * 2), rng);
            auto* adj = make_adj(g, n);
            auto order = topoSort(n, adj);
            ASSERT_EQ((int)order.size(), n);
            if (!is_valid_topo_order(g, n, order))
                cerr << "Stress test failed (seed=" << seed << " t=" << t << ")\n";
            ASSERT_TRUE(is_valid_topo_order(g, n, order));
            delete[] adj;
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
