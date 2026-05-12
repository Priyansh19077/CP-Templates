// Sparse Table — Range Minimum Query (RMQ)
// Build:  O(n log n) time and space
// Query:  O(1) per query
// Usage:  static arrays only (no updates after construction).
//         Call query(l, r) for the minimum in arr[l..r] inclusive.

#include <vector>
#include <algorithm>

struct SparseTable {
    int n, LOG;
    std::vector<std::vector<long long>> st;
    std::vector<int> log2_floor;

    SparseTable() {}

    SparseTable(const std::vector<long long>& arr) {
        n = (int)arr.size();
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        st.assign(LOG, std::vector<long long>(n));
        log2_floor.resize(n + 1, 0);

        for (int i = 2; i <= n; i++)
            log2_floor[i] = log2_floor[i / 2] + 1;

        for (int i = 0; i < n; i++) st[0][i] = arr[i];

        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = std::min(st[j-1][i], st[j-1][i + (1 << (j-1))]);
    }

    long long query(int l, int r) {
        int k = log2_floor[r - l + 1];
        return std::min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};