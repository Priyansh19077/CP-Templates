#include "common.h"
#include "range_utils.h"
#include "../Range Queries/Mo_algo.cpp"

using namespace std;

// Range struct for counting distinct elements.
// Coordinate-compresses the array in its constructor so add/rem
// can work with a compact freq table instead of raw values.
struct Range2 {
    map<long long, int> compress; // may change
    vector<int> freq;             // may change
    int cur;                      // may change
    vector<int> ans;

    Range2(vector<long long>& arr, int q) { // may change
        int id = 0;
        for (long long x : arr) {
            if (!compress.count(x)) compress[x] = id++;
        }
        freq.assign((int)compress.size(), 0);
        cur = 0;
        ans.assign(q, 0);
    }

    void add(long long val) { // element enters window; may change
        if (++freq[compress[val]] == 1) cur++;
    }
    void rem(long long val) { // element leaves window; may change
        if (--freq[compress[val]] == 0) cur--;
    }
    void save(int idx) {      // save answer for query idx; may change
        ans[idx] = cur;
    }
};

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

    // --- Many queries on same range ---
    {
        vector<long long> arr = {1, 2, 3};
        vector<pair<int, int>> queries = {{0, 2}, {0, 2}, {0, 2}};
        auto r = moQuery<Range1>(3, arr, queries);
        ASSERT_EQ(r.ans[0], brute_sum(arr, 0, 2));
        ASSERT_EQ(r.ans[1], brute_sum(arr, 0, 2));
        ASSERT_EQ(r.ans[2], brute_sum(arr, 0, 2));
    }

    // --- Stress test (sum): n=500, q=200 ---
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

    // --- Stress test (sum): n=300, q=300, negative values ---
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

    // --- Distinct queries (Range2): small test ---
    {
        vector<long long> arr = {1, 2, 3, 2, 1, 4, 3};
        vector<pair<int, int>> queries = {{0, 2}, {1, 4}, {0, 6}, {3, 5}};
        auto r = moQuery<Range2>(7, arr, queries);
        vector<int> arrInt(arr.begin(), arr.end());
        ASSERT_EQ(r.ans[0], brute_distinct(arrInt, 0, 2));
        ASSERT_EQ(r.ans[1], brute_distinct(arrInt, 1, 4));
        ASSERT_EQ(r.ans[2], brute_distinct(arrInt, 0, 6));
        ASSERT_EQ(r.ans[3], brute_distinct(arrInt, 3, 5));
    }

    // --- Distinct queries (Range2): large values, no prior compression needed ---
    {
        vector<long long> arr = {1000000, 999999, 1000000, 999998, 999999};
        vector<pair<int, int>> queries = {{0, 4}, {0, 2}, {1, 3}};
        auto r = moQuery<Range2>(5, arr, queries);
        vector<int> arrInt(arr.begin(), arr.end());
        ASSERT_EQ(r.ans[0], brute_distinct(arrInt, 0, 4));
        ASSERT_EQ(r.ans[1], brute_distinct(arrInt, 0, 2));
        ASSERT_EQ(r.ans[2], brute_distinct(arrInt, 1, 3));
    }

    // --- Stress test (distinct): n=400, q=200 ---
    {
        auto seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937 rng(seed);
        const int n = 400;
        vector<long long> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rng() % 1000000;

        const int q = 200;
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            int l = rng() % n, r = rng() % n;
            if (l > r) swap(l, r);
            queries[i] = {l, r};
        }

        auto r = moQuery<Range2>(n, arr, queries);
        vector<int> arrInt(arr.begin(), arr.end());
        for (int i = 0; i < q; i++) {
            int expected = brute_distinct(arrInt, queries[i].first, queries[i].second);
            if (r.ans[i] != expected) cerr << "Distinct stress test failed (seed=" << seed << ")\n";
            ASSERT_EQ(r.ans[i], expected);
        }
    }

    TEST_PASS();
}

int main() { return run_tests(); }
