#include "common.h"
#include "../Graph Algorithms/Cycle_in_DAG.cpp"

using namespace std;

int run_tests() {
    // Acyclic DAG: 0->1, 0->2, 1->3, 2->3
    int n = 4;
    vector<int> edges[4];
    edges[0].push_back(1); edges[0].push_back(2);
    edges[1].push_back(3); edges[2].push_back(3);
    ASSERT_FALSE(check_cycle(n, edges));

    // Cyclic graph: 0->1->2->0
    int n2 = 3;
    vector<int> edges2[3];
    edges2[0].push_back(1); edges2[1].push_back(2); edges2[2].push_back(0);
    ASSERT_TRUE(check_cycle(n2, edges2));

    // Single node, no edges: acyclic
    int n3 = 1;
    vector<int> edges3[1];
    ASSERT_FALSE(check_cycle(n3, edges3));

    TEST_PASS();
}

int main() { return run_tests(); }
