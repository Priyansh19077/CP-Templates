// Heavy-Light Decomposition — path queries/updates in O(log²N)
// Usage:
//   BinaryLifting bl(n, edges, n, root);
//   LCA lca(n, edges, root, &bl);
//   HLD<Node1, Update1> hld(n, edges, root, nodeValues, &lca);
//   hld.findAnswer(u, v)       — query over path u→v
//   hld.makeUpdateatIndex(u, val) — point update at node u
// Customise Node1 and Update1 for your query type (example: range-max below).
#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

// ── Binary Lifting ────────────────────────────────────────────────────────────
struct BinaryLifting {
    int n, maxLog;
    std::vector<int>* edges;
    std::vector<std::vector<int>> parent;

    BinaryLifting(int n, std::vector<int>* edges, long long maxK, int root)
        : n(n), edges(edges), maxLog((int)std::log2(maxK + 1) + 1),
          parent(n, std::vector<int>((int)std::log2(maxK + 1) + 2, -1)) {
        std::vector<bool> vis(n, false);
        _dfs(root, vis);
        for (int j = 1; j <= maxLog; j++)
            for (int u = 0; u < n; u++)
                if (parent[u][j - 1] != -1)
                    parent[u][j] = parent[parent[u][j - 1]][j - 1];
    }
    BinaryLifting() : n(0), maxLog(0), edges(nullptr) {}

    void _dfs(int u, std::vector<bool>& vis) {
        vis[u] = true;
        for (int v : edges[u])
            if (!vis[v]) { parent[v][0] = u; _dfs(v, vis); }
    }

    int kthParent(int u, int k) {
        for (int j = maxLog; j >= 0; j--)
            if (k >= (1 << j)) { u = parent[u][j]; k -= (1 << j); if (u == -1) return -1; }
        return u;
    }
};

// ── LCA ───────────────────────────────────────────────────────────────────────
struct LCA {
    int n;
    BinaryLifting* bl;
    std::vector<int>* edges;
    std::vector<int> level;

    LCA(int n, std::vector<int>* edges, int root, BinaryLifting* bl)
        : n(n), bl(bl), edges(edges), level(n, 0) {
        _dfs(root, -1);
    }
    LCA() : n(0), bl(nullptr), edges(nullptr) {}

    void _dfs(int u, int par) {
        for (int v : edges[u])
            if (v != par) { level[v] = level[u] + 1; _dfs(v, u); }
    }

    int getLCA(int a, int b) {
        if (level[a] < level[b]) std::swap(a, b);
        a = bl->kthParent(a, level[a] - level[b]);
        if (a == b) return a;
        for (int j = bl->maxLog; j >= 0; j--)
            if (bl->parent[a][j] != bl->parent[b][j]) {
                a = bl->parent[a][j]; b = bl->parent[b][j];
            }
        return bl->parent[a][0];
    }
};

// ── Segment Tree (point update, range query) ──────────────────────────────────
template<typename Node, typename Update>
struct SegTree {
    std::vector<Node> tree;
    int n, s;

    SegTree(int n, std::vector<long long>& a) : n(n), s(1) {
        while (s < 2 * n) s <<= 1;
        tree.resize(s, Node());
        _build(a, 0, n - 1, 1);
    }
    SegTree() : n(0), s(0) {}

    void _build(std::vector<long long>& a, int l, int r, int idx) {
        if (l == r) { tree[idx] = Node(a[l]); return; }
        int m = (l + r) / 2;
        _build(a, l, m, 2 * idx);
        _build(a, m + 1, r, 2 * idx + 1);
        tree[idx].merge(tree[2 * idx], tree[2 * idx + 1]);
    }

    void _update(int l, int r, int idx, int pos, Update& u) {
        if (l == r) { u.apply(tree[idx]); return; }
        int m = (l + r) / 2;
        if (pos <= m) _update(l, m, 2 * idx, pos, u);
        else _update(m + 1, r, 2 * idx + 1, pos, u);
        tree[idx].merge(tree[2 * idx], tree[2 * idx + 1]);
    }

    Node _query(int l, int r, int idx, int ql, int qr) {
        if (l > qr || r < ql) return Node();
        if (l >= ql && r <= qr) return tree[idx];
        int m = (l + r) / 2;
        Node left, right, ans;
        left = _query(l, m, 2 * idx, ql, qr);
        right = _query(m + 1, r, 2 * idx + 1, ql, qr);
        ans.merge(left, right);
        return ans;
    }

    void make_update(int pos, long long val) { Update u(val); _update(0, n - 1, 1, pos, u); }
    Node make_query(int l, int r) { return _query(0, n - 1, 1, l, r); }
};

// ── Example Node/Update: range-max with point set ─────────────────────────────
struct Node1 {
    long long val;
    Node1() : val(LLONG_MIN / 2) {}
    Node1(long long v) : val(v) {}
    void merge(const Node1& l, const Node1& r) { val = std::max(l.val, r.val); }
};
struct Update1 {
    long long val;
    Update1(long long v) : val(v) {}
    void apply(Node1& a) { a.val = val; }
};

// ── HLD ───────────────────────────────────────────────────────────────────────
template<typename Node, typename Update>
struct HLD {
    int n, root;
    std::vector<int>* edges;
    std::vector<int> bigChild, subtreeSize, chainHead, label;
    std::vector<long long> values;
    SegTree<Node, Update> seg;
    LCA* lca;
    BinaryLifting* bl;

    HLD(int n, std::vector<int>* edges, int root, std::vector<long long>& vals, LCA* lca)
        : n(n), root(root), edges(edges), bigChild(n, -1), subtreeSize(n),
          chainHead(n), label(n), values(vals), lca(lca), bl(lca->bl) {
        _precompute(root, -1);
        int t = 0;
        _labelDfs(root, -1, t);
        for (int i = 0; i < n; i++) chainHead[i] = i;
        _chainDfs(root, -1);
        seg = SegTree<Node, Update>(n, values);
        for (int i = 0; i < n; i++) seg.make_update(label[i], values[i]);
    }

    void _precompute(int u, int par) {
        subtreeSize[u] = 1; bigChild[u] = -1;
        int best = -1;
        for (int v : edges[u]) if (v != par) {
            _precompute(v, u);
            subtreeSize[u] += subtreeSize[v];
            if (subtreeSize[v] > best) { best = subtreeSize[v]; bigChild[u] = v; }
        }
    }

    void _labelDfs(int u, int par, int& t) {
        label[u] = t++;
        if (bigChild[u] != -1) _labelDfs(bigChild[u], u, t);
        for (int v : edges[u]) if (v != par && v != bigChild[u]) _labelDfs(v, u, t);
    }

    void _chainDfs(int u, int par) {
        if (bigChild[u] != -1) chainHead[bigChild[u]] = chainHead[u];
        for (int v : edges[u]) if (v != par) _chainDfs(v, u);
    }

    Node _queryChain(int u, int ancestor) {
        Node res;
        while (lca->level[u] > lca->level[ancestor]) {
            int top = chainHead[u];
            if (lca->level[top] <= lca->level[ancestor])
                top = bl->kthParent(u, lca->level[u] - lca->level[ancestor] - 1);
            Node a = res, b = seg.make_query(label[top], label[u]);
            res.merge(a, b);
            u = bl->parent[top][0];
        }
        return res;
    }

    long long findAnswer(int u, int v) {
        int anc = lca->getLCA(u, v);
        Node a = _queryChain(u, anc);
        Node b = _queryChain(v, anc);
        Node c = seg.make_query(label[anc], label[anc]);
        Node ab, ans;
        ab.merge(a, b);
        ans.merge(ab, c);
        return ans.val;
    }

    void makeUpdateatIndex(int u, long long val) { seg.make_update(label[u], val); }
};
