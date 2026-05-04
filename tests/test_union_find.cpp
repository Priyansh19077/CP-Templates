#include "common.h"
#include "../Graph Algorithms/UnionFind.cpp"

using namespace std;

int run_tests() {
    UnionFind uf(5);

    // Initially all nodes are their own component
    ASSERT_EQ(uf.get(0), 0);
    ASSERT_EQ(uf.get(1), 1);
    ASSERT_EQ(uf.get(2), 2);

    uf.merge(0, 1);
    ASSERT_EQ(uf.get(0), uf.get(1));

    uf.merge(2, 3);
    ASSERT_EQ(uf.get(2), uf.get(3));
    ASSERT_TRUE(uf.get(0) != uf.get(2));

    uf.merge(1, 3);
    ASSERT_EQ(uf.get(0), uf.get(3));
    ASSERT_EQ(uf.get(1), uf.get(2));

    // Node 4 stays separate
    ASSERT_TRUE(uf.get(4) != uf.get(0));

    TEST_PASS();
}

int main() { return run_tests(); }
