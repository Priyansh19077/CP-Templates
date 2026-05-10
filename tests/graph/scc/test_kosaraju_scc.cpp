#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/SCC/KosarajuSCC.cpp"

using namespace std;

vector<int>* make_fwd(const Adj& g, int n) {
    auto* adj = new vector<int>[n];
    for (int u = 0; u < n; u++) adj[u] = g[u];
    return adj;
}

vector<int>* make_rev(const Adj& g, int n) {
    auto* radj = new vector<int>[n];
    for (int u = 0; u < n; u++) {
        for (int v : g[u]) radj[v].push_back(u);
    }
    return radj;
}

int run_tests() {
    // --- Two SCCs connected by a bridge ---
    // 0⇆1 → 2⇆3 — two SCCs: {0,1} and {2,3}
    {
        int n = 4;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(0);  // SCC: {0,1}
        g[1].push_back(2);                       // bridge
        g[2].push_back(3); g[3].push_back(2);  // SCC: {2,3}
        auto* fwd = make_fwd(g, n);
        auto* rev = make_rev(g, n);
        auto sccs = getSCC(n, fwd, rev);
        ASSERT_EQ((int)sccs.size(), 2);
        ASSERT_TRUE(is_valid_scc(g, n, sccs));
        ASSERT_EQ(brute_scc_count(g, n), 2);
        delete[] fwd; delete[] rev;
    }

    // --- Each node is its own SCC (linear DAG) ---
    {
        int n = 4;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(2); g[2].push_back(3);
        auto* fwd = make_fwd(g, n);
        auto* rev = make_rev(g, n);
        auto sccs = getSCC(n, fwd, rev);
        ASSERT_EQ((int)sccs.size(), 4);
        ASSERT_TRUE(is_valid_scc(g, n, sccs));
        delete[] fwd; delete[] rev;
    }

    // --- Entire graph is one SCC (cycle) ---
    {
        int n = 4;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(2);
        g[2].push_back(3); g[3].push_back(0);
        auto* fwd = make_fwd(g, n);
        auto* rev = make_rev(g, n);
        auto sccs = getSCC(n, fwd, rev);
        ASSERT_EQ((int)sccs.size(), 1);
        ASSERT_TRUE(is_valid_scc(g, n, sccs));
        delete[] fwd; delete[] rev;
    }

    // --- Single node ---
    {
        int n = 1;
        Adj g(n);
        auto* fwd = make_fwd(g, n);
        auto* rev = make_rev(g, n);
        auto sccs = getSCC(n, fwd, rev);
        ASSERT_EQ((int)sccs.size(), 1);
        ASSERT_TRUE(is_valid_scc(g, n, sccs));
        delete[] fwd; delete[] rev;
    }

    // --- Three SCCs: {0,1,2}, {3,4}, {5} ---
    {
        int n = 6;
        Adj g(n);
        g[0].push_back(1); g[1].push_back(2); g[2].push_back(0); // SCC {0,1,2}
        g[2].push_back(3);                                          // bridge
        g[3].push_back(4); g[4].push_back(3);                     // SCC {3,4}
        g[4].push_back(5);                                          // bridge
        // node 5 is isolated sink, SCC {5}
        auto* fwd = make_fwd(g, n);
        auto* rev = make_rev(g, n);
        auto sccs = getSCC(n, fwd, rev);
        ASSERT_EQ((int)sccs.size(), 3);
        ASSERT_TRUE(is_valid_scc(g, n, sccs));
        ASSERT_EQ(brute_scc_count(g, n), 3);
        delete[] fwd; delete[] rev;
    }

    // --- Stress test: SCC count matches brute, decomposition is valid ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        for (int t = 0; t < 30; t++) {
            int n = 5 + rng() % 15;
            Adj g = gen_directed(n, n + rng() % (n * 2), rng);
            auto* fwd = make_fwd(g, n);
            auto* rev = make_rev(g, n);
            auto sccs = getSCC(n, fwd, rev);
            int got = (int)sccs.size();
            int expected = brute_scc_count(g, n);
            if (got != expected) cerr << "Stress test failed (seed=" << seed << " t=" << t << ")\n";
            ASSERT_EQ(got, expected);
            ASSERT_TRUE(is_valid_scc(g, n, sccs));
            delete[] fwd; delete[] rev;
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
