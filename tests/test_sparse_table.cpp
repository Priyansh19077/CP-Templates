#include "common.h"
#include "../Range Queries/Sparse_Table.cpp"

using namespace std;

long long brute_xor(vector<long long>& a, int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; i++) res ^= a[i];
    return res;
}

// Min node for idempotent queryIdempotent tests
struct NodeMin {
    long long val = LLONG_MAX;
    NodeMin() = default;
    NodeMin(long long v) : val(v) {}
    void merge(const NodeMin& l, const NodeMin& r) { val = min(l.val, r.val); }
};

long long brute_min(vector<long long>& a, int l, int r) {
    long long res = LLONG_MAX;
    for (int i = l; i <= r; i++) res = min(res, a[i]);
    return res;
}

int run_tests() {
    // --- Small test: [3, 1, 4, 1, 5, 9, 2, 6], XOR (non-idempotent) ---
    {
        vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
        SparseTable<Node1> sp(8, a);

        ASSERT_EQ(sp.queryNormal(0, 2).val, brute_xor(a, 0, 2));
        ASSERT_EQ(sp.queryNormal(0, 0).val, brute_xor(a, 0, 0));
        ASSERT_EQ(sp.queryNormal(2, 5).val, brute_xor(a, 2, 5));
        ASSERT_EQ(sp.queryNormal(5, 7).val, brute_xor(a, 5, 7));
        ASSERT_EQ(sp.queryNormal(0, 7).val, brute_xor(a, 0, 7));
        ASSERT_EQ(sp.queryNormal(1, 6).val, brute_xor(a, 1, 6));
    }

    // --- Single element ---
    {
        vector<long long> a = {42};
        SparseTable<Node1> sp(1, a);
        ASSERT_EQ(sp.queryNormal(0, 0).val, brute_xor(a, 0, 0));
    }

    // --- Two elements ---
    {
        vector<long long> a = {10, 7};
        SparseTable<Node1> sp(2, a);
        ASSERT_EQ(sp.queryNormal(0, 0).val, brute_xor(a, 0, 0));
        ASSERT_EQ(sp.queryNormal(1, 1).val, brute_xor(a, 1, 1));
        ASSERT_EQ(sp.queryNormal(0, 1).val, brute_xor(a, 0, 1));
    }

    // --- All same values (XOR) ---
    {
        vector<long long> a(8, 5);
        SparseTable<Node1> sp(8, a);
        ASSERT_EQ(sp.queryNormal(0, 7).val, brute_xor(a, 0, 7));  // even count → 0
        ASSERT_EQ(sp.queryNormal(0, 6).val, brute_xor(a, 0, 6));  // odd count → 5
        ASSERT_EQ(sp.queryNormal(0, 0).val, brute_xor(a, 0, 0));
    }

    // --- All zeros ---
    {
        vector<long long> a(5, 0);
        SparseTable<Node1> sp(5, a);
        for (int l = 0; l < 5; l++)
            for (int r = l; r < 5; r++)
                ASSERT_EQ(sp.queryNormal(l, r).val, brute_xor(a, l, r));
    }

    // --- Power-of-two size (n=16), exhaustive queryNormal ---
    {
        vector<long long> a = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
        SparseTable<Node1> sp(16, a);
        for (int l = 0; l < 16; l++)
            for (int r = l; r < 16; r++)
                ASSERT_EQ(sp.queryNormal(l, r).val, brute_xor(a, l, r));
    }

    // --- Idempotent query (range min) ---
    {
        vector<long long> a = {5, 3, 8, 1, 9, 2, 7, 4};
        SparseTable<NodeMin> sp(8, a);
        for (int l = 0; l < 8; l++)
            for (int r = l; r < 8; r++)
                ASSERT_EQ(sp.queryIdempotent(l, r).val, brute_min(a, l, r));
    }

    // --- Idempotent: all same values ---
    {
        vector<long long> a(6, 3);
        SparseTable<NodeMin> sp(6, a);
        ASSERT_EQ(sp.queryIdempotent(0, 5).val, brute_min(a, 0, 5));
        ASSERT_EQ(sp.queryIdempotent(2, 4).val, brute_min(a, 2, 4));
    }

    // --- Idempotent: single element ---
    {
        vector<long long> a = {99};
        SparseTable<NodeMin> sp(1, a);
        ASSERT_EQ(sp.queryIdempotent(0, 0).val, brute_min(a, 0, 0));
    }

    // --- Stress test: n=500, random XOR range queries ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 500;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) a[i] = rng() % 1000000;
        SparseTable<Node1> sp(n, a);

        for (int iter = 0; iter < 1000; iter++) {
            int l = rng() % n;
            int r = rng() % n;
            if (l > r) swap(l, r);
            long long got = sp.queryNormal(l, r).val;
            long long expected = brute_xor(a, l, r);
            if (got != expected) cerr << "XOR stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(got, expected);
        }
    }

    // --- Stress test: n=500, random min queries (idempotent) ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 500;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) a[i] = (long long)(rng() % 1000000);
        SparseTable<NodeMin> sp(n, a);

        for (int iter = 0; iter < 1000; iter++) {
            int l = rng() % n;
            int r = rng() % n;
            if (l > r) swap(l, r);
            long long got = sp.queryIdempotent(l, r).val;
            long long expected = brute_min(a, l, r);
            if (got != expected) cerr << "Min stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(got, expected);
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
