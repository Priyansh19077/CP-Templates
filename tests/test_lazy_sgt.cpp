#include "common.h"
#include "../Range Queries/Lazy_SGT.cpp"

using namespace std;

long long brute_sum(vector<long long>& a, int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; i++) res += a[i];
    return res;
}

int run_tests() {
    // --- Small test: [1, 2, 3, 4, 5], range-assign, range-sum ---
    {
        vector<long long> a = {1, 2, 3, 4, 5};
        LazySGT<Node1, Update1> sgt(5, a);

        ASSERT_EQ(sgt.make_query(0, 4).val, 15LL);
        ASSERT_EQ(sgt.make_query(1, 3).val, 9LL);

        // Assign [1,3] = 10 → [1, 10, 10, 10, 5]
        sgt.make_update(1, 3, 10);
        ASSERT_EQ(sgt.make_query(0, 4).val, 36LL);
        ASSERT_EQ(sgt.make_query(1, 3).val, 30LL);
        ASSERT_EQ(sgt.make_query(0, 0).val, 1LL);
        ASSERT_EQ(sgt.make_query(4, 4).val, 5LL);

        // Assign entire array = 3
        sgt.make_update(0, 4, 3);
        ASSERT_EQ(sgt.make_query(0, 4).val, 15LL);
        ASSERT_EQ(sgt.make_query(2, 4).val, 9LL);
    }

    // --- Single element array ---
    {
        vector<long long> a = {7};
        LazySGT<Node1, Update1> sgt(1, a);
        ASSERT_EQ(sgt.make_query(0, 0).val, 7LL);
        sgt.make_update(0, 0, 100);
        ASSERT_EQ(sgt.make_query(0, 0).val, 100LL);
        sgt.make_update(0, 0, 0);
        ASSERT_EQ(sgt.make_query(0, 0).val, 0LL);
    }

    // --- All zeros, assign to non-zero ---
    {
        vector<long long> a(6, 0);
        LazySGT<Node1, Update1> sgt(6, a);
        ASSERT_EQ(sgt.make_query(0, 5).val, 0LL);
        sgt.make_update(2, 4, 5);
        ASSERT_EQ(sgt.make_query(0, 5).val, 15LL);
        ASSERT_EQ(sgt.make_query(2, 4).val, 15LL);
        ASSERT_EQ(sgt.make_query(0, 1).val, 0LL);
        ASSERT_EQ(sgt.make_query(5, 5).val, 0LL);
    }

    // --- Overlapping range updates ---
    {
        vector<long long> a = {0, 0, 0, 0, 0};
        LazySGT<Node1, Update1> sgt(5, a);
        sgt.make_update(0, 4, 10);
        sgt.make_update(1, 3, 20);  // overwrites [1,3]
        // array = [10, 20, 20, 20, 10]
        ASSERT_EQ(sgt.make_query(0, 4).val, 80LL);
        ASSERT_EQ(sgt.make_query(0, 0).val, 10LL);
        ASSERT_EQ(sgt.make_query(1, 3).val, 60LL);
        ASSERT_EQ(sgt.make_query(4, 4).val, 10LL);
    }

    // --- Nested range updates: outer then inner then outer again ---
    {
        vector<long long> a(8, 1);
        LazySGT<Node1, Update1> sgt(8, a);
        sgt.make_update(0, 7, 5);   // all = 5, sum = 40
        ASSERT_EQ(sgt.make_query(0, 7).val, 40LL);
        sgt.make_update(2, 5, 3);   // [2,5]=3, sum = 5+5+3+3+3+3+5+5 = 32
        ASSERT_EQ(sgt.make_query(0, 7).val, 32LL);
        ASSERT_EQ(sgt.make_query(2, 5).val, 12LL);
        sgt.make_update(0, 7, 7);   // all = 7, sum = 56
        ASSERT_EQ(sgt.make_query(0, 7).val, 56LL);
        ASSERT_EQ(sgt.make_query(3, 3).val, 7LL);
    }

    // --- Power-of-two size ---
    {
        vector<long long> a = {1, 2, 3, 4, 5, 6, 7, 8};
        LazySGT<Node1, Update1> sgt(8, a);
        ASSERT_EQ(sgt.make_query(0, 7).val, 36LL);
        sgt.make_update(4, 7, 0);
        ASSERT_EQ(sgt.make_query(0, 7).val, 10LL);
        ASSERT_EQ(sgt.make_query(4, 7).val, 0LL);
        ASSERT_EQ(sgt.make_query(0, 3).val, 10LL);
    }

    // --- Stress test: n=300, random range-assign + range-sum queries ---
    {
        mt19937 rng(42);
        const int n = 300;
        vector<long long> a(n, 0);
        LazySGT<Node1, Update1> sgt(n, a);

        for (int iter = 0; iter < 600; iter++) {
            int l = rng() % n;
            int r = rng() % n;
            if (l > r) swap(l, r);
            if (rng() % 2 == 0) {
                long long val = rng() % 1000;
                for (int i = l; i <= r; i++) a[i] = val;
                sgt.make_update(l, r, val);
            } else {
                long long expected = brute_sum(a, l, r);
                ASSERT_EQ(sgt.make_query(l, r).val, expected);
            }
        }
    }

    // --- Consecutive full-array reassignments ---
    {
        vector<long long> a = {1, 2, 3, 4, 5, 6, 7};
        LazySGT<Node1, Update1> sgt(7, a);
        for (long long v = 1; v <= 10; v++) {
            sgt.make_update(0, 6, v);
            ASSERT_EQ(sgt.make_query(0, 6).val, v * 7);
        }
    }

    // --- Point-level assigns via single-index range update ---
    {
        vector<long long> a = {0, 0, 0, 0, 0};
        LazySGT<Node1, Update1> sgt(5, a);
        sgt.make_update(2, 2, 99);
        ASSERT_EQ(sgt.make_query(2, 2).val, 99LL);
        ASSERT_EQ(sgt.make_query(0, 4).val, 99LL);
        sgt.make_update(0, 0, 1);
        sgt.make_update(4, 4, 1);
        ASSERT_EQ(sgt.make_query(0, 4).val, 101LL);
    }

    TEST_PASS();
}

int main() { return run_tests(); }
