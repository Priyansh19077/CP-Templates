#include "common.h"
#include "../Graph Algorithms/FordFulkerson.cpp"

using namespace std;

int run_tests() {
    // Flow network: source=0, sink=3
    // 0->1 (cap 2), 0->2 (cap 3), 1->3 (cap 3), 2->3 (cap 2)
    // Max flow = 4
    int n = 4;
    vector<pair<int, long long>> edges[4];
    edges[0].push_back({1, 2}); edges[0].push_back({2, 3});
    edges[1].push_back({3, 3}); edges[2].push_back({3, 2});

    Flow f(edges, n, 0, 3);
    ASSERT_EQ(f.maxFlow(), 4LL);

    // Single path: 0->1->2, cap 5 and 3 → max flow = 3
    int n2 = 3;
    vector<pair<int, long long>> edges2[3];
    edges2[0].push_back({1, 5}); edges2[1].push_back({2, 3});
    Flow f2(edges2, n2, 0, 2);
    ASSERT_EQ(f2.maxFlow(), 3LL);

    TEST_PASS();
}

int main() { return run_tests(); }
