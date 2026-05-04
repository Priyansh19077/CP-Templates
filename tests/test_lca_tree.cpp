#include "common.h"
#include "../Tree Algorithms/LCA_tree.cpp"

using namespace std;

int run_tests() {
    // Tree:        0
    //            /   \
    //           1     2
    //          / \     \
    //         3   4     5
    int n = 6;
    vector<int> edges[6];
    auto addEdge = [&](int u, int v) {
        edges[u].push_back(v); edges[v].push_back(u);
    };
    addEdge(0, 1); addEdge(0, 2); addEdge(1, 3);
    addEdge(1, 4); addEdge(2, 5);

    BinaryLifting bl(n, edges, n, 0);
    LCA lca(n, edges, 0, &bl);

    ASSERT_EQ(lca.getLCA(3, 4), 1);  // siblings under 1
    ASSERT_EQ(lca.getLCA(3, 5), 0);  // 3 is under 1, 5 is under 2
    ASSERT_EQ(lca.getLCA(4, 5), 0);
    ASSERT_EQ(lca.getLCA(0, 3), 0);  // root is ancestor of all
    ASSERT_EQ(lca.getLCA(3, 3), 3);  // LCA of node with itself

    TEST_PASS();
}

int main() { return run_tests(); }
