#include "common.h"
#include "../Range Queries/Sparse_Table.cpp"

using namespace std;

int run_tests() {
    // Array [3, 1, 4, 1, 5, 9, 2, 6], Node1 uses XOR merge
    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    SparseTable<Node1> sp(8, a);

    // XOR of [0,2] = 3^1^4 = 6
    ASSERT_EQ(sp.queryNormal(0, 2).val, 6LL);

    // XOR of [0,0] = 3
    ASSERT_EQ(sp.queryNormal(0, 0).val, 3LL);

    // XOR of [2,5] = 4^1^5^9 = 9
    // 4^1=5, 5^5=0, 0^9=9
    ASSERT_EQ(sp.queryNormal(2, 5).val, 9LL);

    // XOR of [5,7] = 9^2^6 = 13
    // 9^2=11, 11^6=13
    ASSERT_EQ(sp.queryNormal(5, 7).val, 13LL);

    TEST_PASS();
}

int main() { return run_tests(); }
