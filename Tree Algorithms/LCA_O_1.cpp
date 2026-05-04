// O(N log N) preprocessing, O(1) per LCA query — via Euler tour + Sparse Table
// Build LCA_O_1(n, edges, root), then call query(u, v). getDepth(u) returns depth.
#include <algorithm>
#include <cmath>
#include <vector>

template<typename Node>
struct SparseTable {
    std::vector<std::vector<Node>> table;
    std::vector<int> logVal;
    int n, maxLog;

    SparseTable(int n, std::vector<int>& arr) : n(n), logVal(n + 1, 0) {
        maxLog = n > 1 ? (int)std::log2(n) : 0;
        logVal[1] = 0;
        for (int i = 2; i <= n; i++) logVal[i] = logVal[i / 2] + 1;
        table.assign(n, std::vector<Node>(maxLog + 1, Node()));
        for (int i = 0; i < n; i++) table[i][0] = Node(arr[i], i);
        for (int j = 1; j <= maxLog; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[i][j].merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    Node queryIdempotent(int l, int r) {
        int j = logVal[r - l + 1];
        Node ans;
        ans.merge(table[l][j], table[r - (1 << j) + 1][j]);
        return ans;
    }
};

struct MinNode {
    int val = 1e9, idx = -1;
    MinNode() = default;
    MinNode(int v, int i) : val(v), idx(i) {}
    void merge(const MinNode& l, const MinNode& r) {
        if (l.val <= r.val) { val = l.val; idx = l.idx; }
        else { val = r.val; idx = r.idx; }
    }
};

struct LCA_O_1 {
    int n;
    std::vector<int> eulerDepth, nodeAt, firstOccurrence;
    SparseTable<MinNode> sp;

    LCA_O_1(int n, std::vector<int>* edges, int root)
        : n(n), firstOccurrence(n), sp(0, eulerDepth) {
        _dfs(root, -1, edges, 0);
        sp = SparseTable<MinNode>((int)eulerDepth.size(), eulerDepth);
    }

    void _dfs(int u, int par, std::vector<int>* edges, int depth) {
        firstOccurrence[u] = (int)eulerDepth.size();
        eulerDepth.push_back(depth);
        nodeAt.push_back(u);
        for (int v : edges[u]) {
            if (v != par) {
                _dfs(v, u, edges, depth + 1);
                eulerDepth.push_back(depth);
                nodeAt.push_back(u);
            }
        }
    }

    int query(int u, int v) {
        int l = std::min(firstOccurrence[u], firstOccurrence[v]);
        int r = std::max(firstOccurrence[u], firstOccurrence[v]);
        return nodeAt[sp.queryIdempotent(l, r).idx];
    }

    int getDepth(int u) { return eulerDepth[firstOccurrence[u]]; }
};
