// Lazy Segment Tree — O(N) build, O(log N) range update and range query
// Customise Node1 (merge, identity) and Update1 (apply, combine, identity) for your problem.
// Example below: range-assign with range-sum queries.
#include <bits/stdc++.h>
using namespace std;

template<typename Node, typename Update>
struct LazySGT {
    vector<Node> tree;
    vector<bool> lazy;
    vector<Update> updates;
    int n, s;

    LazySGT(int n, vector<long long>& a) {
        this->n = n;
        s = 1;
        while (s < 2 * n) s <<= 1;
        tree.resize(s, Node());
        lazy.resize(s, false);
        updates.resize(s, Update());
        _build(a, 0, n - 1, 1);
    }

    void _build(vector<long long>& a, int l, int r, int idx) {
        if (l == r) { tree[idx] = Node(a[l]); return; }
        int m = (l + r) / 2;
        _build(a, l, m, 2 * idx);
        _build(a, m + 1, r, 2 * idx + 1);
        tree[idx].merge(tree[2 * idx], tree[2 * idx + 1]);
    }

    void _apply(int idx, int l, int r, Update& u) {
        if (l != r) { lazy[idx] = true; updates[idx].combine(u, l, r); }
        u.apply(tree[idx], l, r);
    }

    void _pushdown(int idx, int l, int r) {
        if (lazy[idx]) {
            int m = (l + r) / 2;
            _apply(2 * idx, l, m, updates[idx]);
            _apply(2 * idx + 1, m + 1, r, updates[idx]);
            updates[idx] = Update();
            lazy[idx] = false;
        }
    }

    void _update(int l, int r, int idx, int ql, int qr, Update& u) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) { _apply(idx, l, r, u); return; }
        _pushdown(idx, l, r);
        int m = (l + r) / 2;
        _update(l, m, 2 * idx, ql, qr, u);
        _update(m + 1, r, 2 * idx + 1, ql, qr, u);
        tree[idx].merge(tree[2 * idx], tree[2 * idx + 1]);
    }

    Node _query(int l, int r, int idx, int ql, int qr) {
        if (l > qr || r < ql) return Node();
        if (l >= ql && r <= qr) { _pushdown(idx, l, r); return tree[idx]; }
        _pushdown(idx, l, r);
        int m = (l + r) / 2;
        Node left = _query(l, m, 2 * idx, ql, qr);
        Node right = _query(m + 1, r, 2 * idx + 1, ql, qr);
        Node ans;
        ans.merge(left, right);
        return ans;
    }

    void make_update(int l, int r, long long val) {
        Update u(val);
        _update(0, n - 1, 1, l, r, u);
    }

    Node make_query(int l, int r) {
        return _query(0, n - 1, 1, l, r);
    }
};

// Example: range-assign update, range-sum query
struct Node1 {
    long long val = 0;
    Node1() = default;
    Node1(long long v) : val(v) {}
    void merge(const Node1& l, const Node1& r) { val = l.val + r.val; }
};
struct Update1 {
    long long val = 0;
    Update1() = default;
    Update1(long long v) : val(v) {}
    void apply(Node1& a, int l, int r) { a.val = val * (r - l + 1); }
    void combine(const Update1& newer, int /*l*/, int /*r*/) { val = newer.val; }
};
