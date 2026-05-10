#include "common.h"
#include "graph_utils.h"
#include "DSU/UnionFind.cpp"

using namespace std;

int run_tests() {
    // --- Basic connectivity ---
    {
        UnionFind uf(5);
        ASSERT_TRUE(!uf.connected(0, 1));
        uf.merge(0, 1);
        ASSERT_TRUE(uf.connected(0, 1));
        ASSERT_TRUE(!uf.connected(0, 2));
        uf.merge(1, 2);
        ASSERT_TRUE(uf.connected(0, 2));
        ASSERT_TRUE(!uf.connected(3, 4));
        uf.merge(3, 4);
        ASSERT_TRUE(!uf.connected(0, 3));
        uf.merge(2, 3);
        ASSERT_TRUE(uf.connected(0, 4));
    }

    // --- Self-connectivity ---
    {
        UnionFind uf(4);
        for (int i = 0; i < 4; i++) {
            ASSERT_TRUE(uf.connected(i, i));
        }
    }

    // --- Idempotent merge: merging same pair twice changes nothing ---
    {
        UnionFind uf(3);
        uf.merge(0, 1);
        int r0 = uf.get(0);
        uf.merge(0, 1);
        ASSERT_EQ(uf.get(0), r0);
        ASSERT_TRUE(uf.connected(0, 1));
        ASSERT_TRUE(!uf.connected(0, 2));
    }

    // --- Transitivity: chain merges ---
    {
        UnionFind uf(6);
        for (int i = 0; i < 5; i++) {
            uf.merge(i, i + 1);
        }
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                ASSERT_TRUE(uf.connected(i, j));
            }
        }
    }

    // --- Two separate components ---
    {
        UnionFind uf(6);
        uf.merge(0, 1); uf.merge(1, 2);
        uf.merge(3, 4); uf.merge(4, 5);
        ASSERT_TRUE(uf.connected(0, 2));
        ASSERT_TRUE(uf.connected(3, 5));
        ASSERT_TRUE(!uf.connected(0, 3));
        ASSERT_TRUE(!uf.connected(2, 4));
    }

    // --- Single node ---
    {
        UnionFind uf(1);
        ASSERT_TRUE(uf.connected(0, 0));
    }

    // --- Two nodes ---
    {
        UnionFind uf(2);
        ASSERT_TRUE(!uf.connected(0, 1));
        uf.merge(0, 1);
        ASSERT_TRUE(uf.connected(0, 1));
    }

    // --- Path compression: repeated get() returns same root ---
    {
        UnionFind uf(8);
        for (int i = 0; i < 7; i++) {
            uf.merge(i, i + 1);
        }
        int root = uf.get(0);
        for (int i = 1; i < 8; i++) {
            ASSERT_EQ(uf.get(i), root);
        }
    }

    // --- Stress test: random merges verified against naive component labels ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 500;
        UnionFind uf(n);
        vector<int> comp(n);
        iota(comp.begin(), comp.end(), 0);

        auto brute_find = [&](int x) {
            while (comp[x] != x) x = comp[x];
            return x;
        };

        for (int iter = 0; iter < 1000; iter++) {
            int a = rng() % n;
            int b = rng() % n;
            bool before = (brute_find(a) == brute_find(b));
            ASSERT_EQ(uf.connected(a, b), before);
            if (!before) {
                uf.merge(a, b);
                int ra = brute_find(a), rb = brute_find(b);
                comp[ra] = rb;
                ASSERT_TRUE(uf.connected(a, b));
            }
        }
        // Final: verify all connectivity matches
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j += (n / 20 + 1)) {
                bool expected = (brute_find(i) == brute_find(j));
                if (uf.connected(i, j) != expected) {
                    cerr << "Stress test failed (seed=" << seed << ")\n";
                }
                ASSERT_EQ(uf.connected(i, j), expected);
            }
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
