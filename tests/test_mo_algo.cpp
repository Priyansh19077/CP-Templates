#include "common.h"
#include "range_utils.h"
#include "../Range Queries/Mo_algo.cpp"

using namespace std;

int run_tests() {
    // --- Small test: [1, 2, 3, 4, 5], sum queries ---
    {
        vector<long long> arr = {1, 2, 3, 4, 5};
        vector<pair<int, int>> queries = {{0, 2}, {1, 3}, {0, 4}, {2, 4}};
        auto r = moQuery<Range1>(5, arr, queries);
        ASSERT_EQ(r.ans[0], brute_sum(arr, 0, 2));
        ASSERT_EQ(r.ans[1], brute_sum(arr, 1, 3));
        ASSERT_EQ(r.ans[2], brute_sum(arr, 0, 4));
        ASSERT_EQ(r.ans[3], brute_sum(arr, 2, 4));
    }

    // --- Single element queries ---
    {
        vector<long long> arr = {10, 20, 30, 40};
        vector<pair<int, int>> queries = {{0, 0}, {1, 1}, {3, 3}};
        auto r = moQuery<Range1>(4, arr, queries);
        ASSERT_EQ(r.ans[0], brute_sum(arr, 0, 0));
        ASSERT_EQ(r.ans[1], brute_sum(arr, 1, 1));
        ASSERT_EQ(r.ans[2], brute_sum(arr, 3, 3));
    }

    // --- All zeros ---
    {
        vector<long long> arr(6, 0);
        vector<pair<int, int>> queries = {{0, 5}, {1, 4}, {2, 3}};
        auto r = moQuery<Range1>(6, arr, queries);
        ASSERT_EQ(r.ans[0], brute_sum(arr, 0, 5));
        ASSERT_EQ(r.ans[1], brute_sum(arr, 1, 4));
        ASSERT_EQ(r.ans[2], brute_sum(arr, 2, 3));
    }

    // --- All same values ---
    {
        vector<long long> arr(8, 7);
        vector<pair<int, int>> queries = {{0, 7}, {0, 3}, {4, 7}, {2, 5}};
        auto r = moQuery<Range1>(8, arr, queries);
        ASSERT_EQ(r.ans[0], brute_sum(arr, 0, 7));
        ASSERT_EQ(r.ans[1], brute_sum(arr, 0, 3));
        ASSERT_EQ(r.ans[2], brute_sum(arr, 4, 7));
        ASSERT_EQ(r.ans[3], brute_sum(arr, 2, 5));
    }

    // --- Single query spanning full array ---
    {
        vector<long long> arr = {3, 1, 4, 1, 5, 9, 2, 6};
        vector<pair<int, int>> queries = {{0, 7}};
        auto r = moQuery<Range1>(8, arr, queries);
        ASSERT_EQ(r.ans[0], brute_sum(arr, 0, 7));
    }

    // --- Many queries on same range (order preserved) ---
    {
        vector<long long> arr = {1, 2, 3};
        vector<pair<int, int>> queries = {{0, 2}, {0, 2}, {0, 2}};
        auto r = moQuery<Range1>(3, arr, queries);
        ASSERT_EQ(r.ans[0], brute_sum(arr, 0, 2));
        ASSERT_EQ(r.ans[1], brute_sum(arr, 0, 2));
        ASSERT_EQ(r.ans[2], brute_sum(arr, 0, 2));
    }

    // --- Stress test: n=500, q=200 ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 500;
        vector<long long> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rng() % 1000000;

        const int q = 200;
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            queries[i] = {l, r};
        }

        auto r = moQuery<Range1>(n, arr, queries);
        for (int i = 0; i < q; i++) {
            long long expected = brute_sum(arr, queries[i].first, queries[i].second);
            if (r.ans[i] != expected) cerr << "Stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(r.ans[i], expected);
        }
    }

    // --- Stress test: n=300, q=300, negative values ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 300;
        vector<long long> arr(n);
        for (int i = 0; i < n; i++) arr[i] = (long long)(rng() % 2000000) - 1000000;

        const int q = 300;
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            queries[i] = {l, r};
        }

        auto r = moQuery<Range1>(n, arr, queries);
        for (int i = 0; i < q; i++) {
            long long expected = brute_sum(arr, queries[i].first, queries[i].second);
            if (r.ans[i] != expected) cerr << "Stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(r.ans[i], expected);
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
