// O((N+Q)√N) — Mo's Algorithm for offline range queries (distinct count example)
// arr: input array (0-indexed); queries: list of {l, r} inclusive ranges
// Returns answer[i] = number of distinct elements in arr[queries[i].l .. queries[i].r]
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

std::vector<int> moDistinctQueries(int n, std::vector<int> arr,
                                   std::vector<std::pair<int, int>>& queries) {
    const int block = std::max(1, (int)std::sqrt(n));
    int q = (int)queries.size();

    // Coordinate compress arr
    std::map<int, int> compress;
    int id = 0;
    for (int& x : arr) {
        if (!compress.count(x)) compress[x] = id++;
        x = compress[x];
    }

    // Tag queries with original index, then sort by Mo's order
    std::vector<std::pair<std::pair<int, int>, int>> indexed(q);
    for (int i = 0; i < q; i++) indexed[i] = {{queries[i].first, queries[i].second}, i};
    std::sort(indexed.begin(), indexed.end(),
        [&](auto& a, auto& b) {
            int ba = a.first.first / block, bb = b.first.first / block;
            if (ba != bb) return ba < bb;
            return (ba & 1) ? a.first.second > b.first.second
                            : a.first.second < b.first.second;
        });

    std::vector<int> freq(n, 0), ans(q);
    int cur = 0, lo = 0, hi = -1;

    auto add = [&](int pos) { if (++freq[arr[pos]] == 1) cur++; };
    auto rem = [&](int pos) { if (--freq[arr[pos]] == 0) cur--; };

    for (auto& [range, origIdx] : indexed) {
        auto [l, r] = range;
        while (hi < r) add(++hi);
        while (lo > l) add(--lo);
        while (hi > r) rem(hi--);
        while (lo < l) rem(lo++);
        ans[origIdx] = cur;
    }
    return ans;
}
