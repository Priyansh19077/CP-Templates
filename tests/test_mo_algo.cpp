#include "common.h"
#include "../Range Queries/Mo_algo.cpp"

using namespace std;

int brute_distinct(vector<int>& arr, int l, int r) {
    set<int> s(arr.begin() + l, arr.begin() + r + 1);
    return (int)s.size();
}

int run_tests() {
    // --- Small test: [1, 2, 3, 2, 1, 4, 3] ---
    {
        vector<int> arr = {1, 2, 3, 2, 1, 4, 3};
        vector<pair<int, int>> queries = {{0, 2}, {1, 4}, {0, 6}, {3, 5}};
        vector<int> ans = moDistinctQueries(7, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 2));
        ASSERT_EQ(ans[1], brute_distinct(arr, 1, 4));
        ASSERT_EQ(ans[2], brute_distinct(arr, 0, 6));
        ASSERT_EQ(ans[3], brute_distinct(arr, 3, 5));
    }

    // --- Single element queries ---
    {
        vector<int> arr = {5, 5, 5, 5};
        vector<pair<int, int>> queries = {{0, 0}, {1, 1}, {2, 3}};
        vector<int> ans = moDistinctQueries(4, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 0));
        ASSERT_EQ(ans[1], brute_distinct(arr, 1, 1));
        ASSERT_EQ(ans[2], brute_distinct(arr, 2, 3));
    }

    // --- All distinct elements ---
    {
        vector<int> arr = {10, 20, 30, 40, 50};
        vector<pair<int, int>> queries = {{0, 4}, {0, 2}, {2, 4}, {1, 3}};
        vector<int> ans = moDistinctQueries(5, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 4));
        ASSERT_EQ(ans[1], brute_distinct(arr, 0, 2));
        ASSERT_EQ(ans[2], brute_distinct(arr, 2, 4));
        ASSERT_EQ(ans[3], brute_distinct(arr, 1, 3));
    }

    // --- All same elements ---
    {
        vector<int> arr = {7, 7, 7, 7, 7, 7};
        vector<pair<int, int>> queries = {{0, 5}, {0, 0}, {2, 4}, {1, 5}};
        vector<int> ans = moDistinctQueries(6, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 5));
        ASSERT_EQ(ans[1], brute_distinct(arr, 0, 0));
        ASSERT_EQ(ans[2], brute_distinct(arr, 2, 4));
        ASSERT_EQ(ans[3], brute_distinct(arr, 1, 5));
    }

    // --- Two elements alternating ---
    {
        vector<int> arr = {1, 2, 1, 2, 1, 2};
        vector<pair<int, int>> queries = {{0, 5}, {0, 0}, {0, 1}, {1, 4}};
        vector<int> ans = moDistinctQueries(6, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 5));
        ASSERT_EQ(ans[1], brute_distinct(arr, 0, 0));
        ASSERT_EQ(ans[2], brute_distinct(arr, 0, 1));
        ASSERT_EQ(ans[3], brute_distinct(arr, 1, 4));
    }

    // --- Large values (coordinate compression must handle these) ---
    {
        vector<int> arr = {1000000, 999999, 1000000, 999998, 999999};
        vector<pair<int, int>> queries = {{0, 4}, {0, 2}, {1, 3}};
        vector<int> ans = moDistinctQueries(5, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 4));
        ASSERT_EQ(ans[1], brute_distinct(arr, 0, 2));
        ASSERT_EQ(ans[2], brute_distinct(arr, 1, 3));
    }

    // --- Single query spanning full array ---
    {
        vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
        vector<pair<int, int>> queries = {{0, 7}};
        vector<int> ans = moDistinctQueries(8, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 7));
    }

    // --- Many queries on same range (order preserved) ---
    {
        vector<int> arr = {1, 2, 3};
        vector<pair<int, int>> queries = {{0, 2}, {0, 2}, {0, 2}};
        vector<int> ans = moDistinctQueries(3, arr, queries);
        ASSERT_EQ(ans[0], brute_distinct(arr, 0, 2));
        ASSERT_EQ(ans[1], brute_distinct(arr, 0, 2));
        ASSERT_EQ(ans[2], brute_distinct(arr, 0, 2));
    }

    // --- Stress test: n=500, q=200, values in [0,49] ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 500;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rng() % 50;

        const int q = 200;
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            queries[i] = {l, r};
        }

        vector<int> ans = moDistinctQueries(n, arr, queries);
        for (int i = 0; i < q; i++) {
            int expected = brute_distinct(arr, queries[i].first, queries[i].second);
            if (ans[i] != expected) cerr << "Stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(ans[i], expected);
        }
    }

    // --- Stress test: n=300, q=300, large value range ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 300;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rng() % 1000000;

        const int q = 300;
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            queries[i] = {l, r};
        }

        vector<int> ans = moDistinctQueries(n, arr, queries);
        for (int i = 0; i < q; i++) {
            int expected = brute_distinct(arr, queries[i].first, queries[i].second);
            if (ans[i] != expected) cerr << "Stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(ans[i], expected);
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
