#include "common.h"
#include "../Tree Algorithms/LCA_O_1.cpp"

using namespace std;

int run_tests() {
    // Same tree as LCA_tree test:
    //        0
    //       / \
    //      1   2
    //     / \   \
    //    3   4   5
    int n = 6;
    vector<int> edges[6];
    auto addEdge = [&](int u, int v) {
        edges[u].push_back(v); edges[v].push_back(u);
    };
    addEdge(0, 1); addEdge(0, 2); addEdge(1, 3);
    addEdge(1, 4); addEdge(2, 5);

    LCA_O_1 lca(n, edges, 0);

    ASSERT_EQ(lca.query(3, 4), 1);
    ASSERT_EQ(lca.query(3, 5), 0);
    ASSERT_EQ(lca.query(4, 5), 0);
    ASSERT_EQ(lca.query(0, 3), 0);
    ASSERT_EQ(lca.query(3, 3), 3);

    // Verify depths
    ASSERT_EQ(lca.getDepth(0), 0);
    ASSERT_EQ(lca.getDepth(1), 1);
    ASSERT_EQ(lca.getDepth(3), 2);

    TEST_PASS();
}

int main() { return run_tests(); }
