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

        ASSERT_EQ(sgt.make_query(0, 4).val, brute_sum(a, 0, 4));
        ASSERT_EQ(sgt.make_query(1, 3).val, brute_sum(a, 1, 3));

        // Assign [1,3] = 10 → [1, 10, 10, 10, 5]
        sgt.make_update(1, 3, 10);
        for (int i = 1; i <= 3; i++) a[i] = 10;
        ASSERT_EQ(sgt.make_query(0, 4).val, brute_sum(a, 0, 4));
        ASSERT_EQ(sgt.make_query(1, 3).val, brute_sum(a, 1, 3));
        ASSERT_EQ(sgt.make_query(0, 0).val, brute_sum(a, 0, 0));
        ASSERT_EQ(sgt.make_query(4, 4).val, brute_sum(a, 4, 4));

        // Assign entire array = 3
        sgt.make_update(0, 4, 3);
        for (int i = 0; i <= 4; i++) a[i] = 3;
        ASSERT_EQ(sgt.make_query(0, 4).val, brute_sum(a, 0, 4));
        ASSERT_EQ(sgt.make_query(2, 4).val, brute_sum(a, 2, 4));
    }

    // --- Single element array ---
    {
        vector<long long> a = {7};
        LazySGT<Node1, Update1> sgt(1, a);
        ASSERT_EQ(sgt.make_query(0, 0).val, brute_sum(a, 0, 0));
        sgt.make_update(0, 0, 100);
        a[0] = 100;
        ASSERT_EQ(sgt.make_query(0, 0).val, brute_sum(a, 0, 0));
        sgt.make_update(0, 0, 0);
        a[0] = 0;
        ASSERT_EQ(sgt.make_query(0, 0).val, brute_sum(a, 0, 0));
    }

    // --- All zeros, assign to non-zero ---
    {
        vector<long long> a(6, 0);
        LazySGT<Node1, Update1> sgt(6, a);
        ASSERT_EQ(sgt.make_query(0, 5).val, brute_sum(a, 0, 5));
        sgt.make_update(2, 4, 5);
        for (int i = 2; i <= 4; i++) a[i] = 5;
        ASSERT_EQ(sgt.make_query(0, 5).val, brute_sum(a, 0, 5));
        ASSERT_EQ(sgt.make_query(2, 4).val, brute_sum(a, 2, 4));
        ASSERT_EQ(sgt.make_query(0, 1).val, brute_sum(a, 0, 1));
        ASSERT_EQ(sgt.make_query(5, 5).val, brute_sum(a, 5, 5));
    }

    // --- Overlapping range updates ---
    {
        vector<long long> a(5, 0);
        LazySGT<Node1, Update1> sgt(5, a);
        sgt.make_update(0, 4, 10);
        for (int i = 0; i <= 4; i++) a[i] = 10;
        sgt.make_update(1, 3, 20);
        for (int i = 1; i <= 3; i++) a[i] = 20;
        // array = [10, 20, 20, 20, 10]
        ASSERT_EQ(sgt.make_query(0, 4).val, brute_sum(a, 0, 4));
        ASSERT_EQ(sgt.make_query(0, 0).val, brute_sum(a, 0, 0));
        ASSERT_EQ(sgt.make_query(1, 3).val, brute_sum(a, 1, 3));
        ASSERT_EQ(sgt.make_query(4, 4).val, brute_sum(a, 4, 4));
    }

    // --- Nested range updates: outer then inner then outer again ---
    {
        vector<long long> a(8, 1);
        LazySGT<Node1, Update1> sgt(8, a);
        sgt.make_update(0, 7, 5);
        for (int i = 0; i <= 7; i++) a[i] = 5;
        ASSERT_EQ(sgt.make_query(0, 7).val, brute_sum(a, 0, 7));
        sgt.make_update(2, 5, 3);
        for (int i = 2; i <= 5; i++) a[i] = 3;
        ASSERT_EQ(sgt.make_query(0, 7).val, brute_sum(a, 0, 7));
        ASSERT_EQ(sgt.make_query(2, 5).val, brute_sum(a, 2, 5));
        sgt.make_update(0, 7, 7);
        for (int i = 0; i <= 7; i++) a[i] = 7;
        ASSERT_EQ(sgt.make_query(0, 7).val, brute_sum(a, 0, 7));
        ASSERT_EQ(sgt.make_query(3, 3).val, brute_sum(a, 3, 3));
    }

    // --- Power-of-two size ---
    {
        vector<long long> a = {1, 2, 3, 4, 5, 6, 7, 8};
        LazySGT<Node1, Update1> sgt(8, a);
        ASSERT_EQ(sgt.make_query(0, 7).val, brute_sum(a, 0, 7));
        sgt.make_update(4, 7, 0);
        for (int i = 4; i <= 7; i++) a[i] = 0;
        ASSERT_EQ(sgt.make_query(0, 7).val, brute_sum(a, 0, 7));
        ASSERT_EQ(sgt.make_query(4, 7).val, brute_sum(a, 4, 7));
        ASSERT_EQ(sgt.make_query(0, 3).val, brute_sum(a, 0, 3));
    }

    // --- Consecutive full-array reassignments ---
    {
        vector<long long> a = {1, 2, 3, 4, 5, 6, 7};
        LazySGT<Node1, Update1> sgt(7, a);
        for (long long v = 1; v <= 10; v++) {
            sgt.make_update(0, 6, v);
            for (int i = 0; i <= 6; i++) a[i] = v;
            ASSERT_EQ(sgt.make_query(0, 6).val, brute_sum(a, 0, 6));
        }
    }

    // --- Point-level assigns via single-index range update ---
    {
        vector<long long> a(5, 0);
        LazySGT<Node1, Update1> sgt(5, a);
        sgt.make_update(2, 2, 99);
        a[2] = 99;
        ASSERT_EQ(sgt.make_query(2, 2).val, brute_sum(a, 2, 2));
        ASSERT_EQ(sgt.make_query(0, 4).val, brute_sum(a, 0, 4));
        sgt.make_update(0, 0, 1);
        a[0] = 1;
        sgt.make_update(4, 4, 1);
        a[4] = 1;
        ASSERT_EQ(sgt.make_query(0, 4).val, brute_sum(a, 0, 4));
    }

    // --- Stress test: n=300, random range-assign + range-sum queries ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
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
                long long got = sgt.make_query(l, r).val;
                long long expected = brute_sum(a, l, r);
                if (got != expected) cerr << "Stress test failed (seed=" << seed << ")\n";
                ASSERT_EQ(got, expected);
            }
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
