// O(N log N) preprocessing, O(log N) per LCA query — via Binary Lifting
// Build BinaryLifting first, then LCA. Call lca.getLCA(u, v).
#include <cmath>
#include <vector>

struct BinaryLifting {
    int n, maxLog;
    std::vector<std::vector<int>> parent;

    BinaryLifting(int n, std::vector<int>* edges, long long maxK, int root)
        : n(n), maxLog((int)std::log2(maxK + 1) + 1),
          parent(n, std::vector<int>((int)std::log2(maxK + 1) + 2, -1)) {
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

struct LCA {
    int n;
    BinaryLifting* bl;
    std::vector<int> depth;

    LCA(int n, std::vector<int>* edges, int root, BinaryLifting* bl)
        : n(n), bl(bl), depth(n, 0) {
        _dfs(root, -1, edges);
    }

    void _dfs(int u, int par, std::vector<int>* edges) {
        for (int v : edges[u])
            if (v != par) {
                depth[v] = depth[u] + 1;
                _dfs(v, u, edges);
            }
    }

    int getLCA(int a, int b) {
        if (depth[a] < depth[b]) std::swap(a, b);
        a = bl->kthParent(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int j = bl->maxLog; j >= 0; j--)
            if (bl->parent[a][j] != bl->parent[b][j]) {
                a = bl->parent[a][j];
                b = bl->parent[b][j];
            }
        return bl->parent[a][0];
    }
};
