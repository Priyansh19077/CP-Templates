#include "common.h"
#include "../Tree Algorithms/HLD.cpp"

using namespace std;

int run_tests() {
    // Tree:    0(5)
    //         / \
    //       1(3) 2(7)
    //       / \
    //     3(2) 4(4)
    // Node values: [5, 3, 7, 2, 4]
    // HLD supports path max queries
    int n = 5;
    vector<long long> values = {5, 3, 7, 2, 4};
    vector<int> edges[5];
    auto addEdge = [&](int u, int v) {
        edges[u].push_back(v); edges[v].push_back(u);
    };
    addEdge(0, 1); addEdge(0, 2); addEdge(1, 3); addEdge(1, 4);

    BinaryLifting bl(n, edges, n, 0);
    LCA lca_obj(n, edges, 0, &bl);
    HLD<Node1, Update1> hld(n, edges, 0, values, &lca_obj);

    // Max on path 3->4: goes through 1 → max(2, 3, 4) = 4
    ASSERT_EQ(hld.findAnswer(3, 4), 4LL);

    // Max on path 3->2: 3->1->0->2 → max(2, 3, 5, 7) = 7
    ASSERT_EQ(hld.findAnswer(3, 2), 7LL);

    // Update node 1 value to 10, then max on path 3->4 = max(2, 10, 4) = 10
    hld.makeUpdateatIndex(1, 10);
    ASSERT_EQ(hld.findAnswer(3, 4), 10LL);

    TEST_PASS();
}

int main() { return run_tests(); }
