#include "common.h"
#include "../Range Queries/Segment_tree.cpp"

using namespace std;

long long brute_xor(vector<long long>& a, int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; i++) res ^= a[i];
    return res;
}

int run_tests() {
    // --- Small test: [1, 2, 3, 4, 5], XOR merge, point-set update ---
    {
        vector<long long> a = {1, 2, 3, 4, 5};
        SegTree<Node1, Update1> st(5, a);

        ASSERT_EQ(st.make_query(0, 4).val, 1LL);   // 1^2^3^4^5 = 1
        ASSERT_EQ(st.make_query(1, 3).val, 5LL);   // 2^3^4 = 5
        ASSERT_EQ(st.make_query(0, 0).val, 1LL);
        ASSERT_EQ(st.make_query(4, 4).val, 5LL);

        // Point update: set index 2 → 7; array = [1, 2, 7, 4, 5]
        st.make_update(2, 7);
        ASSERT_EQ(st.make_query(0, 4).val, 5LL);   // 1^2^7^4^5 = 5
        ASSERT_EQ(st.make_query(2, 2).val, 7LL);
        ASSERT_EQ(st.make_query(1, 3).val, 1LL);   // 2^7^4 = 1
    }

    // --- Single element array ---
    {
        vector<long long> a = {42};
        SegTree<Node1, Update1> st(1, a);
        ASSERT_EQ(st.make_query(0, 0).val, 42LL);
        st.make_update(0, 99);
        ASSERT_EQ(st.make_query(0, 0).val, 99LL);
    }

    // --- Two element array ---
    {
        vector<long long> a = {5, 3};
        SegTree<Node1, Update1> st(2, a);
        ASSERT_EQ(st.make_query(0, 1).val, 6LL);   // 5^3 = 6
        ASSERT_EQ(st.make_query(0, 0).val, 5LL);
        ASSERT_EQ(st.make_query(1, 1).val, 3LL);
        st.make_update(0, 3);
        ASSERT_EQ(st.make_query(0, 1).val, 0LL);   // 3^3 = 0
    }

    // --- All-same values ---
    {
        vector<long long> a(8, 7);
        SegTree<Node1, Update1> st(8, a);
        ASSERT_EQ(st.make_query(0, 7).val, 0LL);   // 7^7^7^7^7^7^7^7 = 0 (even count)
        ASSERT_EQ(st.make_query(0, 6).val, 7LL);   // odd count → 7
        ASSERT_EQ(st.make_query(2, 4).val, 7LL);   // 7^7^7 = 7
    }

    // --- All zeros ---
    {
        vector<long long> a(6, 0);
        SegTree<Node1, Update1> st(6, a);
        ASSERT_EQ(st.make_query(0, 5).val, 0LL);
        st.make_update(3, 15);
        ASSERT_EQ(st.make_query(0, 5).val, 15LL);
        ASSERT_EQ(st.make_query(3, 3).val, 15LL);
        ASSERT_EQ(st.make_query(0, 2).val, 0LL);
    }

    // --- Power-of-two size (n=8) ---
    {
        vector<long long> a = {1, 2, 4, 8, 16, 32, 64, 128};
        SegTree<Node1, Update1> st(8, a);
        ASSERT_EQ(st.make_query(0, 7).val, brute_xor(a, 0, 7));
        ASSERT_EQ(st.make_query(3, 6).val, brute_xor(a, 3, 6));
        st.make_update(5, 0);
        a[5] = 0;
        ASSERT_EQ(st.make_query(0, 7).val, brute_xor(a, 0, 7));
    }

    // --- Stress test: n=300, random point updates and range XOR queries ---
    {
        mt19937 rng(7);
        const int n = 300;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) a[i] = rng() % 1000000;

        SegTree<Node1, Update1> st(n, a);

        for (int iter = 0; iter < 600; iter++) {
            if (rng() % 2 == 0) {
                // Random point update
                int pos = rng() % n;
                long long val = rng() % 1000000;
                a[pos] = val;
                st.make_update(pos, val);
            } else {
                // Random range XOR query
                int l = rng() % n;
                int r = rng() % n;
                if (l > r) swap(l, r);
                long long expected = brute_xor(a, l, r);
                ASSERT_EQ(st.make_query(l, r).val, expected);
            }
        }
    }

    // --- Stress test: n=1 repeatedly updated ---
    {
        mt19937 rng(13);
        vector<long long> a = {0};
        SegTree<Node1, Update1> st(1, a);
        for (int i = 0; i < 100; i++) {
            long long v = rng() % 100000;
            st.make_update(0, v);
            ASSERT_EQ(st.make_query(0, 0).val, v);
        }
    }

    // --- Consecutive updates to same position ---
    {
        vector<long long> a = {10, 20, 30};
        SegTree<Node1, Update1> st(3, a);
        st.make_update(1, 5);
        ASSERT_EQ(st.make_query(1, 1).val, 5LL);
        st.make_update(1, 100);
        ASSERT_EQ(st.make_query(1, 1).val, 100LL);
        ASSERT_EQ(st.make_query(0, 2).val, (10LL ^ 100LL ^ 30LL));
    }

    TEST_PASS();
}

int main() { return run_tests(); }
