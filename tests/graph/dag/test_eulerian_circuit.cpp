#include "common.h"
#include "graph_utils.h"
#include "Graph Algorithms/DAG/EulerianCircuit.cpp"

using namespace std;

int run_tests() {
    // --- Simple 4-cycle: 0-1-2-3-0 ---
    {
        int n = 4;
        // Pass each undirected edge from one side
        vector<int>* edges = new vector<int>[n];
        edges[0].push_back(1);
        edges[1].push_back(2);
        edges[2].push_back(3);
        edges[3].push_back(0);
        // orig_adj has both directions for is_valid_euler_circuit
        vector<vector<int>> orig(n);
        orig[0] = {1, 3}; orig[1] = {0, 2};
        orig[2] = {1, 3}; orig[3] = {2, 0};
        auto circuits = eulerCircuits(n, edges);
        ASSERT_EQ((int)circuits.size(), 1);
        ASSERT_TRUE(is_valid_euler_circuit(n, orig, circuits[0]));
        delete[] edges;
    }

    // --- Graph with an odd-degree node: no Euler circuit ---
    {
        int n = 3;
        vector<int>* edges = new vector<int>[n];
        edges[0].push_back(1);
        edges[0].push_back(2);
        // node 0 has degree 2, node 1 has degree 1 (odd) → no Euler circuit
        auto circuits = eulerCircuits(n, edges);
        ASSERT_TRUE(circuits.empty());
        delete[] edges;
    }

    // --- Two-edge graph (triangle): 0-1-2-0 ---
    {
        int n = 3;
        vector<int>* edges = new vector<int>[n];
        edges[0].push_back(1);
        edges[1].push_back(2);
        edges[2].push_back(0);
        vector<vector<int>> orig(n);
        orig[0] = {1, 2}; orig[1] = {0, 2}; orig[2] = {1, 0};
        auto circuits = eulerCircuits(n, edges);
        ASSERT_EQ((int)circuits.size(), 1);
        ASSERT_TRUE(is_valid_euler_circuit(n, orig, circuits[0]));
        delete[] edges;
    }

    // --- More complex: two triangles sharing a node (0-1-2-0, 0-3-4-0) ---
    {
        int n = 5;
        vector<int>* edges = new vector<int>[n];
        edges[0].push_back(1); edges[1].push_back(2); edges[2].push_back(0);
        edges[0].push_back(3); edges[3].push_back(4); edges[4].push_back(0);
        vector<vector<int>> orig(n);
        orig[0] = {1, 2, 3, 4};
        orig[1] = {0, 2}; orig[2] = {1, 0};
        orig[3] = {0, 4}; orig[4] = {3, 0};
        auto circuits = eulerCircuits(n, edges);
        ASSERT_EQ((int)circuits.size(), 1);
        ASSERT_TRUE(is_valid_euler_circuit(n, orig, circuits[0]));
        delete[] edges;
    }

    // --- No edges: no circuits ---
    {
        int n = 3;
        vector<int>* edges = new vector<int>[n];
        auto circuits = eulerCircuits(n, edges);
        ASSERT_TRUE(circuits.empty());
        delete[] edges;
    }

    TEST_PASS();
}

int main() { return run_tests(); }
