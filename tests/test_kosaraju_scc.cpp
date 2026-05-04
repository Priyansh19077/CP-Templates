#include "common.h"
#include "../Graph Algorithms/KosarajuSCC.cpp"

using namespace std;

int run_tests() {
    // Graph: 0->1, 1->2, 2->0 (one SCC {0,1,2}), 3->4 (two singletons)
    int n = 5;
    vector<int> edges[5], edgesT[5];
    auto addEdge = [&](int u, int v) {
        edges[u].push_back(v);
        edgesT[v].push_back(u);
    };
    addEdge(0, 1); addEdge(1, 2); addEdge(2, 0);
    addEdge(3, 4);

    vector<vector<int>> scc = getSCC(n, edges, edgesT);
    ASSERT_EQ((int)scc.size(), 3);

    // Find the SCC of size 3
    bool foundTriple = false;
    for (auto& comp : scc) {
        if ((int)comp.size() == 3) {
            foundTriple = true;
            set<int> s(comp.begin(), comp.end());
            ASSERT_TRUE(s.count(0) && s.count(1) && s.count(2));
        }
    }
    ASSERT_TRUE(foundTriple);

    // Strongly connected graph: all in one SCC
    int n2 = 3;
    vector<int> edges2[3], edgesT2[3];
    auto addEdge2 = [&](int u, int v) {
        edges2[u].push_back(v); edgesT2[v].push_back(u);
    };
    addEdge2(0, 1); addEdge2(1, 2); addEdge2(2, 0);
    auto scc2 = getSCC(n2, edges2, edgesT2);
    ASSERT_EQ((int)scc2.size(), 1);
    ASSERT_EQ((int)scc2[0].size(), 3);

    TEST_PASS();
}

int main() { return run_tests(); }
