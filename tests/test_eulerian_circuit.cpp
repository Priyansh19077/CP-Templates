#include "common.h"
#include "../Graph Algorithms/EulerianCircuit.cpp"

using namespace std;

int run_tests() {
    // Triangle: 0-1, 1-2, 2-0 — each vertex degree 2 (even), Eulerian circuit exists
    // Edges stored one-sided (as per the function's comment)
    int n = 3;
    vector<int> edges[3];
    edges[0].push_back(1);
    edges[1].push_back(2);
    edges[2].push_back(0);

    vector<vector<int>> circuits = EulerCircuits(n, edges);
    ASSERT_EQ((int)circuits.size(), 1);
    // Circuit visits all 3 edges -> path length 4 (returns to start)
    ASSERT_EQ((int)circuits[0].size(), 4);

    // Graph with odd-degree vertices — no Eulerian circuit, returns empty
    int n2 = 3;
    vector<int> edges2[3];
    edges2[0].push_back(1);  // 0: degree 1 (odd), no circuit
    vector<vector<int>> circuits2 = EulerCircuits(n2, edges2);
    ASSERT_TRUE(circuits2.empty());

    TEST_PASS();
}

int main() { return run_tests(); }
