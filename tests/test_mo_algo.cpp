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
        ASSERT_EQ(ans[0], 3);  // {1,2,3}
        ASSERT_EQ(ans[1], 3);  // {1,2,3}
        ASSERT_EQ(ans[2], 4);  // {1,2,3,4}
        ASSERT_EQ(ans[3], 3);  // {1,2,4}
    }

    // --- Single element queries ---
    {
        vector<int> arr = {5, 5, 5, 5};
        vector<pair<int, int>> queries = {{0, 0}, {1, 1}, {2, 3}};
        vector<int> ans = moDistinctQueries(4, arr, queries);
        ASSERT_EQ(ans[0], 1);
        ASSERT_EQ(ans[1], 1);
        ASSERT_EQ(ans[2], 1);
    }

    // --- All distinct elements ---
    {
        vector<int> arr = {10, 20, 30, 40, 50};
        vector<pair<int, int>> queries = {{0, 4}, {0, 2}, {2, 4}, {1, 3}};
        vector<int> ans = moDistinctQueries(5, arr, queries);
        ASSERT_EQ(ans[0], 5);
        ASSERT_EQ(ans[1], 3);
        ASSERT_EQ(ans[2], 3);
        ASSERT_EQ(ans[3], 3);
    }

    // --- All same elements ---
    {
        vector<int> arr = {7, 7, 7, 7, 7, 7};
        vector<pair<int, int>> queries = {{0, 5}, {0, 0}, {2, 4}, {1, 5}};
        vector<int> ans = moDistinctQueries(6, arr, queries);
        ASSERT_EQ(ans[0], 1);
        ASSERT_EQ(ans[1], 1);
        ASSERT_EQ(ans[2], 1);
        ASSERT_EQ(ans[3], 1);
    }

    // --- Two elements alternating ---
    {
        vector<int> arr = {1, 2, 1, 2, 1, 2};
        vector<pair<int, int>> queries = {{0, 5}, {0, 0}, {0, 1}, {1, 4}};
        vector<int> ans = moDistinctQueries(6, arr, queries);
        ASSERT_EQ(ans[0], 2);
        ASSERT_EQ(ans[1], 1);
        ASSERT_EQ(ans[2], 2);
        ASSERT_EQ(ans[3], 2);
    }

    // --- Large values (no coordinate compression issues) ---
    {
        vector<int> arr = {1000000, 999999, 1000000, 999998, 999999};
        vector<pair<int, int>> queries = {{0, 4}, {0, 2}, {1, 3}};
        vector<int> ans = moDistinctQueries(5, arr, queries);
        ASSERT_EQ(ans[0], 3);  // {999998, 999999, 1000000}
        ASSERT_EQ(ans[1], 2);  // {999999, 1000000}
        ASSERT_EQ(ans[2], 3);  // {999998, 999999, 1000000}
    }

    // --- Single query spanning full array ---
    {
        vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
        vector<pair<int, int>> queries = {{0, 7}};
        vector<int> ans = moDistinctQueries(8, arr, queries);
        ASSERT_EQ(ans[0], 7);  // {1,2,3,4,5,6,9}
    }

    // --- Many queries on same range (order preserved) ---
    {
        vector<int> arr = {1, 2, 3};
        vector<pair<int, int>> queries = {{0, 2}, {0, 2}, {0, 2}};
        vector<int> ans = moDistinctQueries(3, arr, queries);
        ASSERT_EQ(ans[0], 3);
        ASSERT_EQ(ans[1], 3);
        ASSERT_EQ(ans[2], 3);
    }

    // --- Stress test: n=500, q=200, random queries verified by brute force ---
    {
        mt19937 rng(99);
        const int n = 500;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rng() % 50;  // values in [0,49]

        const int q = 200;
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            int l = rng() % n;
            int r = rng() % n;
            if (l > r) swap(l, r);
            queries[i] = {l, r};
        }

        vector<int> ans = moDistinctQueries(n, arr, queries);
        for (int i = 0; i < q; i++) {
            int expected = brute_distinct(arr, queries[i].first, queries[i].second);
            ASSERT_EQ(ans[i], expected);
        }
    }

    // --- Stress test: n=300, q=300, large value range ---
    {
        mt19937 rng(77);
        const int n = 300;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rng() % 1000000;

        const int q = 300;
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            int l = rng() % n;
            int r = rng() % n;
            if (l > r) swap(l, r);
            queries[i] = {l, r};
        }

        vector<int> ans = moDistinctQueries(n, arr, queries);
        for (int i = 0; i < q; i++) {
            int expected = brute_distinct(arr, queries[i].first, queries[i].second);
            ASSERT_EQ(ans[i], expected);
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
