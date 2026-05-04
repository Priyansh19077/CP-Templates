// O(N log N) preprocessing, O(log N) per kth-ancestor query
// Build BinaryLifting(n, edges, maxK, root) where maxK is the max k you'll query
// kthParent(u, k) returns the k-th ancestor of u, or -1 if it doesn't exist
#include <cmath>
#include <vector>

struct BinaryLifting {
    int n, maxLog;
    std::vector<std::vector<int>> parent;

    BinaryLifting(int n, std::vector<int>* edges, long long maxK, int root)
        : n(n), maxLog((int)std::log2(maxK + 1) + 1), parent(n, std::vector<int>((int)std::log2(maxK + 1) + 2, -1)) {
        _dfs(root, -1, edges);
        for (int j = 1; j <= maxLog; j++)
            for (int u = 0; u < n; u++)
                if (parent[u][j - 1] != -1)
                    parent[u][j] = parent[parent[u][j - 1]][j - 1];
    }

    void _dfs(int u, int par, std::vector<int>* edges) {
        parent[u][0] = par;
        for (int v : edges[u])
            if (v != par)
                _dfs(v, u, edges);
    }

    int kthParent(int u, int k) {
        for (int j = maxLog; j >= 0; j--) {
            if (k >= (1 << j)) {
                u = parent[u][j];
                k -= (1 << j);
                if (u == -1) return -1;
            }
        }
        return u;
    }
};
