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

        ASSERT_EQ(st.make_query(0, 4).val, brute_xor(a, 0, 4));
        ASSERT_EQ(st.make_query(1, 3).val, brute_xor(a, 1, 3));
        ASSERT_EQ(st.make_query(0, 0).val, brute_xor(a, 0, 0));
        ASSERT_EQ(st.make_query(4, 4).val, brute_xor(a, 4, 4));

        // Point update: set index 2 → 7
        st.make_update(2, 7);
        a[2] = 7;
        ASSERT_EQ(st.make_query(0, 4).val, brute_xor(a, 0, 4));
        ASSERT_EQ(st.make_query(2, 2).val, brute_xor(a, 2, 2));
        ASSERT_EQ(st.make_query(1, 3).val, brute_xor(a, 1, 3));
    }

    // --- Single element array ---
    {
        vector<long long> a = {42};
        SegTree<Node1, Update1> st(1, a);
        ASSERT_EQ(st.make_query(0, 0).val, brute_xor(a, 0, 0));
        st.make_update(0, 99);
        a[0] = 99;
        ASSERT_EQ(st.make_query(0, 0).val, brute_xor(a, 0, 0));
    }

    // --- Two element array ---
    {
        vector<long long> a = {5, 3};
        SegTree<Node1, Update1> st(2, a);
        ASSERT_EQ(st.make_query(0, 1).val, brute_xor(a, 0, 1));
        ASSERT_EQ(st.make_query(0, 0).val, brute_xor(a, 0, 0));
        ASSERT_EQ(st.make_query(1, 1).val, brute_xor(a, 1, 1));
        st.make_update(0, 3);
        a[0] = 3;
        ASSERT_EQ(st.make_query(0, 1).val, brute_xor(a, 0, 1));
    }

    // --- All-same values ---
    {
        vector<long long> a(8, 7);
        SegTree<Node1, Update1> st(8, a);
        ASSERT_EQ(st.make_query(0, 7).val, brute_xor(a, 0, 7));
        ASSERT_EQ(st.make_query(0, 6).val, brute_xor(a, 0, 6));
        ASSERT_EQ(st.make_query(2, 4).val, brute_xor(a, 2, 4));
    }

    // --- All zeros ---
    {
        vector<long long> a(6, 0);
        SegTree<Node1, Update1> st(6, a);
        ASSERT_EQ(st.make_query(0, 5).val, brute_xor(a, 0, 5));
        st.make_update(3, 15);
        a[3] = 15;
        ASSERT_EQ(st.make_query(0, 5).val, brute_xor(a, 0, 5));
        ASSERT_EQ(st.make_query(3, 3).val, brute_xor(a, 3, 3));
        ASSERT_EQ(st.make_query(0, 2).val, brute_xor(a, 0, 2));
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

    // --- Consecutive updates to same position ---
    {
        vector<long long> a = {10, 20, 30};
        SegTree<Node1, Update1> st(3, a);
        st.make_update(1, 5);
        a[1] = 5;
        ASSERT_EQ(st.make_query(1, 1).val, brute_xor(a, 1, 1));
        st.make_update(1, 100);
        a[1] = 100;
        ASSERT_EQ(st.make_query(1, 1).val, brute_xor(a, 1, 1));
        ASSERT_EQ(st.make_query(0, 2).val, brute_xor(a, 0, 2));
    }

    // --- Stress test: n=300, random point updates and range XOR queries ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 300;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) a[i] = rng() % 1000000;

        SegTree<Node1, Update1> st(n, a);

        for (int iter = 0; iter < 600; iter++) {
            if (rng() % 2 == 0) {
                int pos = rng() % n;
                long long val = rng() % 1000000;
                a[pos] = val;
                st.make_update(pos, val);
            } else {
                int l = rng() % n;
                int r = rng() % n;
                if (l > r) swap(l, r);
                long long got = st.make_query(l, r).val;
                long long expected = brute_xor(a, l, r);
                if (got != expected) cerr << "Stress test failed (seed=" << seed << ")\n";
                ASSERT_EQ(got, expected);
            }
        }
    }

    // --- Stress test: n=1 repeatedly updated ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        vector<long long> a = {0};
        SegTree<Node1, Update1> st(1, a);
        for (int i = 0; i < 100; i++) {
            long long v = rng() % 100000;
            st.make_update(0, v);
            a[0] = v;
            long long got = st.make_query(0, 0).val;
            if (got != a[0]) cerr << "Stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(got, brute_xor(a, 0, 0));
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
