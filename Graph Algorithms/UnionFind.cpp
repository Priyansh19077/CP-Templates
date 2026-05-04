// O(α(N)) per operation — Disjoint Set Union with path compression and union by rank
#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    int n;
    vector<int> rank;
    vector<int> parent;

    UnionFind(int n) : n(n), rank(n, 0), parent(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int get(int a) {
        return parent[a] = (parent[a] == a ? a : get(parent[a]));
    }

    void merge(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return;
        if (rank[a] == rank[b]) rank[a]++;
        if (rank[a] > rank[b]) parent[b] = a;
        else parent[a] = b;
    }
};
