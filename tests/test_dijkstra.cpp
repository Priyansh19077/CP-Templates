#include "common.h"
#include "../Graph Algorithms/Dijkstra.cpp"

using namespace std;

int run_tests() {
    // Graph: 0->1 (1), 0->2 (4), 1->2 (2), 1->3 (5), 2->3 (1)
    // Shortest from 0: [0, 1, 3, 4]
    int n = 4;
    vector<pair<int, long long>> adj[4];
    adj[0].push_back({1, 1}); adj[0].push_back({2, 4});
    adj[1].push_back({2, 2}); adj[1].push_back({3, 5});
    adj[2].push_back({3, 1});

    vector<long long> dist;
    vector<int> parent;
    dijkstra(0, n, dist, parent, adj);

    ASSERT_EQ(dist[0], 0LL);
    ASSERT_EQ(dist[1], 1LL);
    ASSERT_EQ(dist[2], 3LL);
    ASSERT_EQ(dist[3], 4LL);
    ASSERT_EQ(parent[0], -1);
    ASSERT_EQ(parent[1], 0);
    ASSERT_EQ(parent[2], 1);
    ASSERT_EQ(parent[3], 2);

    // Disconnected node
    int n2 = 3;
    vector<pair<int, long long>> adj2[3];
    adj2[0].push_back({1, 5});
    // node 2 is disconnected from source

    vector<long long> dist2;
    vector<int> parent2;
    dijkstra(0, n2, dist2, parent2, adj2);
    ASSERT_EQ(dist2[0], 0LL);
    ASSERT_EQ(dist2[1], 5LL);
    ASSERT_TRUE(dist2[2] > 1e17);  // effectively INF

    TEST_PASS();
}

int main() { return run_tests(); }
