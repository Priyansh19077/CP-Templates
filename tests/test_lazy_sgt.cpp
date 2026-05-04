#include "common.h"
#include "../Range Queries/Lazy_SGT.cpp"

using namespace std;

int run_tests() {
    // Array [1, 2, 3, 4, 5], Node1 uses sum, Update1 is range assign
    vector<long long> a = {1, 2, 3, 4, 5};
    LazySGT<Node1, Update1> sgt(5, a);

    // Sum of [0,4] = 15
    ASSERT_EQ(sgt.make_query(0, 4).val, 15LL);

    // Sum of [1,3] = 2+3+4 = 9
    ASSERT_EQ(sgt.make_query(1, 3).val, 9LL);

    // Range assign [1,3] = 10 → array [1, 10, 10, 10, 5]
    sgt.make_update(1, 3, 10);
    ASSERT_EQ(sgt.make_query(0, 4).val, 36LL);  // 1+10+10+10+5
    ASSERT_EQ(sgt.make_query(1, 3).val, 30LL);  // 10+10+10
    ASSERT_EQ(sgt.make_query(0, 0).val, 1LL);   // unchanged
    ASSERT_EQ(sgt.make_query(4, 4).val, 5LL);   // unchanged

    // Range assign [0,4] = 3 → array [3, 3, 3, 3, 3]
    sgt.make_update(0, 4, 3);
    ASSERT_EQ(sgt.make_query(0, 4).val, 15LL);

    TEST_PASS();
}

int main() { return run_tests(); }
