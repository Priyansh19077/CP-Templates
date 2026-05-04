#include "common.h"
#include "../Graph Algorithms/Prims.cpp"

using namespace std;

int run_tests() {
    // Same graph as Kruskals test for cross-verification:
    // 0-1(1), 0-2(4), 1-2(2), 1-3(5), 2-3(1) → MST weight = 4
    int n = 4;
    vector<pair<int, long long>> edges[4];
    auto addEdge = [&](int u, int v, long long w) {
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    };
    addEdge(0, 1, 1); addEdge(0, 2, 4);
    addEdge(1, 2, 2); addEdge(1, 3, 5);
    addEdge(2, 3, 1);

    long long mstWeight = prims(n, edges);
    ASSERT_EQ(mstWeight, 4LL);

    // Single-node graph
    int n2 = 1;
    vector<pair<int, long long>> edges2[1];
    ASSERT_EQ(prims(n2, edges2), 0LL);

    TEST_PASS();
}

int main() { return run_tests(); }
