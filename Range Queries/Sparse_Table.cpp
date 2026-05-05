// Sparse Table — O(N log N) build; O(1) for idempotent queries (min/max), O(log N) for others
// Customise Node1 (merge, identity) for your query type. Example: XOR (non-idempotent).
#include <bits/stdc++.h>
using namespace std;

template<typename Node>
struct SparseTable {
    vector<vector<Node>> table;
    int n, maxLog;
    vector<long long> logVal;

    SparseTable(int n, vector<long long>& a) : n(n), logVal(n + 1, 0) {
        maxLog = n > 1 ? (int)log2(n) : 0;
        for (int i = 2; i <= n; i++) logVal[i] = logVal[i / 2] + 1;
        table.assign(n, vector<Node>(maxLog + 1, Node()));
        for (int i = 0; i < n; i++) table[i][0] = Node(a[i]);
        for (int j = 1; j <= maxLog; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[i][j].merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    // For non-idempotent operations (e.g. XOR, sum): O(log N)
    Node queryNormal(int l, int r) {
        Node ans;
        for (int j = logVal[r - l + 1]; j >= 0; j--) {
            if ((1 << j) <= r - l + 1) {
                ans.merge(ans, table[l][j]);
                l += (1 << j);
            }
        }
        return ans;
    }

    // For idempotent operations (e.g. min, max, gcd): O(1)
    Node queryIdempotent(int l, int r) {
        int j = logVal[r - l + 1];
        Node ans;
        ans.merge(table[l][j], table[r - (1 << j) + 1][j]);
        return ans;
    }
};

// Example: XOR aggregate (non-idempotent, use queryNormal)
struct Node1 {
    long long val = 0;
    Node1() = default;
    Node1(long long v) : val(v) {}
    void merge(const Node1& l, const Node1& r) { val = l.val ^ r.val; }
};
