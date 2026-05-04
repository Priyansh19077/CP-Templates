#include "common.h"
#include "../Range Queries/Segment_tree.cpp"

using namespace std;

int run_tests() {
    // Array [1, 2, 3, 4, 5], Node1 uses XOR merge, Update1 sets value
    vector<long long> a = {1, 2, 3, 4, 5};
    SegTree<Node1, Update1> st(5, a);

    // XOR of [0,4] = 1^2^3^4^5 = 1
    ASSERT_EQ(st.make_query(0, 4).val, 1LL);

    // XOR of [1,3] = 2^3^4 = 5
    ASSERT_EQ(st.make_query(1, 3).val, 5LL);

    // Point update: set index 2 to 7
    // Array becomes [1, 2, 7, 4, 5], XOR = 1^2^7^4^5 = 5
    st.make_update(2, 7);
    ASSERT_EQ(st.make_query(0, 4).val, 5LL);
    ASSERT_EQ(st.make_query(2, 2).val, 7LL);

    // Single element query
    ASSERT_EQ(st.make_query(0, 0).val, 1LL);
    ASSERT_EQ(st.make_query(4, 4).val, 5LL);

    TEST_PASS();
}

int main() { return run_tests(); }
