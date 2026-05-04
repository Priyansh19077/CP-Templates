#include "common.h"
#include "../Tree Algorithms/Binary_Lifting.cpp"

using namespace std;

int run_tests() {
    // Linear chain: 0-1-2-3-4, rooted at 0
    int n = 5;
    vector<int> edges[5];
    for (int i = 0; i < 4; i++) {
        edges[i].push_back(i + 1);
        edges[i + 1].push_back(i);
    }

    BinaryLifting bl(n, edges, n, 0);

    ASSERT_EQ(bl.kthParent(4, 1), 3);
    ASSERT_EQ(bl.kthParent(4, 2), 2);
    ASSERT_EQ(bl.kthParent(4, 4), 0);
    ASSERT_EQ(bl.kthParent(4, 5), -1);  // beyond root
    ASSERT_EQ(bl.kthParent(0, 1), -1);  // root has no parent

    TEST_PASS();
}

int main() { return run_tests(); }
