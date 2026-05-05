// O((N+Q)√N) — Mo's Algorithm for offline range queries
// Supports multiple query types with just a change in Range
// Very few changes required each time
#include <bits/stdc++.h>
using namespace std;

template<typename Range>
Range moQuery(int n, vector<long long>& arr, vector<pair<int, int>>& queries) { // Never change this
    int q = (int)queries.size();
    Range range(arr, q);
    const int block = max(1, (int)sqrt(n));

    // Tag queries with original index, then sort by Mo's order
    vector<pair<pair<int, int>, int>> indexed(q);
    for (int i = 0; i < q; i++) indexed[i] = {{queries[i].first, queries[i].second}, i};

    // Sort: primary key = block of l; secondary key = r, alternating direction
    // per block (odd blocks descending) to reduce total pointer movement
    auto moCmp = [&](const auto& a, const auto& b) {
        int ba = a.first.first / block;
        int bb = b.first.first / block;
        if (ba != bb) return ba < bb;
        return (ba & 1) ? a.first.second > b.first.second
                        : a.first.second < b.first.second;
    };
    sort(indexed.begin(), indexed.end(), moCmp);

    int lo = 0, hi = -1;
    for (auto& [bounds, origIdx] : indexed) {
        auto [l, r] = bounds;
        while (hi < r) range.add(arr[++hi]);
        while (lo > l) range.add(arr[--lo]);
        while (hi > r) range.rem(arr[hi--]);
        while (lo < l) range.rem(arr[lo++]);
        range.save(origIdx);
    }
    return range;
}

// Example: sum of elements in each query range
struct Range1 {
    long long cur;         // store current window aggregate; may change
    vector<long long> ans;

    Range1(vector<long long>&, int q) { // Identity state; may change
        cur = 0;
        ans.assign(q, 0);
    }

    void add(long long val) { // element enters window; may change
        cur += val;
    }
    void rem(long long val) { // element leaves window; may change
        cur -= val;
    }
    void save(int idx) {      // save answer for query idx; may change
        ans[idx] = cur;
    }
};
