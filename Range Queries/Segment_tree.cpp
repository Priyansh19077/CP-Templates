// Segment Tree — O(N) build, O(log N) point update and range query
// Customise Node1 (merge logic, identity) and Update1 (apply logic) for your problem.
// Example below: XOR with point-set updates.
#include <bits/stdc++.h>
using namespace std;

template<typename Node, typename Update>
struct SegTree {
    vector<Node> tree;
    int n, s;

    SegTree(int n, vector<long long>& a) {
        this->n = n;
        s = 1;
        while (s < 2 * n) s <<= 1;
        tree.resize(s, Node());
        _build(a, 0, n - 1, 1);
    }

    void _build(vector<long long>& a, int l, int r, int idx) {
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
        Node left = _query(l, m, 2 * idx, ql, qr);
        Node right = _query(m + 1, r, 2 * idx + 1, ql, qr);
        Node ans;
        ans.merge(left, right);
        return ans;
    }

    void make_update(int pos, long long val) {
        Update u(val);
        _update(0, n - 1, 1, pos, u);
    }

    Node make_query(int l, int r) {
        return _query(0, n - 1, 1, l, r);
    }
};

// Example: XOR aggregate, point-set update
struct Node1 {
    long long val = 0;  // identity for XOR
    Node1() = default;
    Node1(long long v) : val(v) {}
    void merge(const Node1& l, const Node1& r) { val = l.val ^ r.val; }
};
struct Update1 {
    long long val;
    Update1(long long v) : val(v) {}
    void apply(Node1& a) { a.val = val; }
};
