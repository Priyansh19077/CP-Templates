#include "common.h"
#include "../Graph Algorithms/Kruskals.cpp"

using namespace std;

int run_tests() {
    // Undirected weighted graph (4 nodes):
    // 0-1(1), 0-2(4), 1-2(2), 1-3(5), 2-3(1)
    // MST edges: 0-1(1), 2-3(1), 1-2(2) → total weight = 4
    int n = 4;
    vector<tuple<long long, int, int>> edges = {
        {1, 0, 1}, {4, 0, 2}, {2, 1, 2}, {5, 1, 3}, {1, 2, 3}
    };

    long long mstWeight = kruskals(n, edges);
    ASSERT_EQ(mstWeight, 4LL);

    // Single edge graph
    int n2 = 2;
    vector<tuple<long long, int, int>> edges2 = {{7, 0, 1}};
    ASSERT_EQ(kruskals(n2, edges2), 7LL);

    TEST_PASS();
}

int main() { return run_tests(); }
