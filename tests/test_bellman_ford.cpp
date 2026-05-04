#include "common.h"
#include "../Graph Algorithms/BellmanFord.cpp"

using namespace std;

int run_tests() {
    // Graph: 0->1 (1), 0->2 (4), 1->2 (2), 1->3 (5), 2->3 (1)
    // Shortest from 0: [0, 1, 3, 4]
    int n = 4;
    vector<pair<int, long long>> edges[4];
    edges[0].push_back({1, 1}); edges[0].push_back({2, 4});
    edges[1].push_back({2, 2}); edges[1].push_back({3, 5});
    edges[2].push_back({3, 1});

    vector<long long> dist(n);
    set<int> negCycle;
    bellmanFord(n, 0, edges, dist, negCycle);

    ASSERT_EQ(dist[0], 0LL);
    ASSERT_EQ(dist[1], 1LL);
    ASSERT_EQ(dist[2], 3LL);
    ASSERT_EQ(dist[3], 4LL);
    ASSERT_TRUE(negCycle.empty());

    // Graph with negative cycle: 0->1 (1), 1->2 (-3), 2->1 (1)
    int n2 = 3;
    vector<pair<int, long long>> edges2[3];
    edges2[0].push_back({1, 1});
    edges2[1].push_back({2, -3});
    edges2[2].push_back({1, 1});

    vector<long long> dist2(n2);
    set<int> negCycle2;
    bellmanFord(n2, 0, edges2, dist2, negCycle2);
    ASSERT_FALSE(negCycle2.empty());

    TEST_PASS();
}

int main() { return run_tests(); }
