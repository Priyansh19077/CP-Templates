#include "common.h"
#include "../Graph Algorithms/FloydWarshall.cpp"

using namespace std;

int run_tests() {
    // 4-node graph: 0->1(3), 0->3(7), 1->0(8), 1->2(2), 2->0(5), 3->0(2), 2->3(1)
    // Expected shortest paths verified manually
    int n = 4;
    vector<pair<int, long long>> adj[4];
    adj[0].push_back({1, 3}); adj[0].push_back({3, 7});
    adj[1].push_back({0, 8}); adj[1].push_back({2, 2});
    adj[2].push_back({0, 5}); adj[2].push_back({3, 1});
    adj[3].push_back({0, 2});

    vector<vector<long long>> dist(n, vector<long long>(n));
    floydWarshall(n, adj, dist);

    ASSERT_EQ(dist[0][0], 0LL);
    ASSERT_EQ(dist[0][1], 3LL);  // direct
    ASSERT_EQ(dist[0][2], 5LL);  // 0->1->2
    ASSERT_EQ(dist[0][3], 6LL);  // 0->1->2->3
    ASSERT_EQ(dist[3][1], 5LL);  // 3->0->1
    ASSERT_EQ(dist[2][0], 3LL);  // 2->3->0 (shorter than direct 2->0 via weight 5)

    TEST_PASS();
}

int main() { return run_tests(); }
