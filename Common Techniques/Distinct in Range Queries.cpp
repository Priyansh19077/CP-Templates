// O((N+Q) log N) — Count distinct elements in ranges via offline processing + BIT
// arr: input array (0-indexed, modified in place for coordinate compression)
// queries: list of {l, r} inclusive ranges (0-indexed)
// Returns ans[i] = count of distinct values in arr[queries[i].l .. queries[i].r]
#include <bits/stdc++.h>
using namespace std;

void _bit_update(int i, vector<int>& bit, int val) {
    for (i++; i < (int)bit.size(); i += i & -i) bit[i] += val;
}
int _bit_query(int i, vector<int>& bit) {
    int s = 0;
    for (i++; i > 0; i -= i & -i) s += bit[i];
    return s;
}

vector<int> distinctQueries(int n, int q, vector<int> arr, vector<pair<int, int>>& queries) {
    // Coordinate compress
    map<int, int> compress;
    int uid = 0;
    for (int& x : arr) {
        if (!compress.count(x)) compress[x] = uid++;
        x = compress[x];
    }

    // Tag and sort queries by right endpoint
    vector<pair<pair<int, int>, int>> tagged(q);
    for (int i = 0; i < q; i++) tagged[i] = {{queries[i].first + 1, queries[i].second + 1}, i};
    sort(tagged.begin(), tagged.end(),
              [](auto& a, auto& b) { return a.first.second < b.first.second; });

    vector<int> lastSeen(uid, -1), bit(n + 1, 0), ans(q);
    int qi = 0;
    for (int i = 0; i < n; i++) {
        if (lastSeen[arr[i]] != -1) _bit_update(lastSeen[arr[i]], bit, -1);
        lastSeen[arr[i]] = i;
        _bit_update(i, bit, 1);
        while (qi < q && tagged[qi].first.second == i + 1) {
            int l = tagged[qi].first.first - 1;
            int r = tagged[qi].first.second - 1;
            ans[tagged[qi].second] = _bit_query(r, bit) - (l > 0 ? _bit_query(l - 1, bit) : 0);
            qi++;
        }
    }
    return ans;
}
