#include "common.h"
#include "../Range Queries/SparseTable_RMQ.cpp"

int main() {
    // Typical case
    std::vector<long long> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    SparseTable rmq(arr);

    ASSERT_EQ(rmq.query(0, 7), 1LL);  // full array
    ASSERT_EQ(rmq.query(2, 6), 1LL);  // subarray spanning the second 1
    ASSERT_EQ(rmq.query(4, 7), 2LL);  // right half, min is 2
    ASSERT_EQ(rmq.query(0, 1), 1LL);  // leftmost pair

    // Edge: single element queries
    ASSERT_EQ(rmq.query(0, 0), 3LL);
    ASSERT_EQ(rmq.query(5, 5), 9LL);

    // Edge: array of size 1
    std::vector<long long> single = {42};
    SparseTable rmq2(single);
    ASSERT_EQ(rmq2.query(0, 0), 42LL);

    TEST_PASS();
}