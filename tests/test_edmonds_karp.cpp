#include "common.h"
#include "../Graph Algorithms/EdmondsKarp.cpp"

using namespace std;

int run_tests() {
    // Same network as FordFulkerson test: max flow = 4
    int n = 4;
    vector<pair<int, long long>> edges[4];
    edges[0].push_back({1, 2}); edges[0].push_back({2, 3});
    edges[1].push_back({3, 3}); edges[2].push_back({3, 2});

    Flow f(edges, n, 0, 3);
    ASSERT_EQ(f.maxFlow(), 4LL);

    // Larger network: 0->1(10), 0->2(10), 1->3(10), 2->3(10), 1->2(1) → max flow = 20
    int n2 = 4;
    vector<pair<int, long long>> edges2[4];
    edges2[0].push_back({1, 10}); edges2[0].push_back({2, 10});
    edges2[1].push_back({3, 10}); edges2[2].push_back({3, 10});
    edges2[1].push_back({2, 1});
    Flow f2(edges2, n2, 0, 3);
    ASSERT_EQ(f2.maxFlow(), 20LL);

    TEST_PASS();
}

int main() { return run_tests(); }
