#include "common.h"
#include "../Graph Algorithms/Topological_sorting.cpp"

using namespace std;

int run_tests() {
    // DAG: 0->1, 0->2, 1->3, 2->3
    // Valid topo orders: 0,1,2,3 or 0,2,1,3
    int n = 4;
    vector<int> edges[4];
    edges[0].push_back(1); edges[0].push_back(2);
    edges[1].push_back(3); edges[2].push_back(3);

    vector<int> order = topo_sort(n, edges);
    ASSERT_EQ((int)order.size(), 4);

    // Verify: for each edge u->v, u appears before v in order
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[order[i]] = i;
    ASSERT_TRUE(pos[0] < pos[1]);
    ASSERT_TRUE(pos[0] < pos[2]);
    ASSERT_TRUE(pos[1] < pos[3]);
    ASSERT_TRUE(pos[2] < pos[3]);

    // Linear chain: 0->1->2->3->4
    int n2 = 5;
    vector<int> edges2[5];
    for (int i = 0; i < 4; i++) edges2[i].push_back(i + 1);
    vector<int> order2 = topo_sort(n2, edges2);
    for (int i = 0; i < n2; i++) ASSERT_EQ(order2[i], i);

    TEST_PASS();
}

int main() { return run_tests(); }
