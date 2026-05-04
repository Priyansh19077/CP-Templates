// O(N log N) — Centroid Decomposition
// Edges stored as index pairs in edgeList; edges[u] holds edge indices.
// Call decompose(root, edges, centroidTree, -1) to build centroid tree.
// centroidTree[u] = neighbours of u in the centroid decomposition tree.
// Returns the centroid of the initial component.
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> edgeList;
vector<bool> deleted;
vector<int> subtree;

int _getOther(int edgeIdx, int u) {
    return edgeList[edgeIdx].first ^ edgeList[edgeIdx].second ^ u;
}

void _computeSubtrees(int u, vector<int>* edges, int parent) {
    subtree[u] = 1;
    for (int i : edges[u]) {
        int v = _getOther(i, u);
        if (!deleted[i] && v != parent) {
            _computeSubtrees(v, edges, u);
            subtree[u] += subtree[v];
        }
    }
}

int _findCentroid(int u, vector<int>* edges, int treeSize, int parent) {
    for (int i : edges[u]) {
        int v = _getOther(i, u);
        if (!deleted[i] && v != parent && subtree[v] > treeSize / 2)
            return _findCentroid(v, edges, treeSize, u);
    }
    return u;
}

int decompose(int root, vector<int>* edges, vector<int>* centroidTree, int parent) {
    _computeSubtrees(root, edges, -1);
    int n = subtree[root];
    root = _findCentroid(root, edges, n, -1);
    if (parent != -1) {
        centroidTree[root].push_back(parent);
        centroidTree[parent].push_back(root);
    }
    for (int i : edges[root]) {
        if (deleted[i]) continue;
        deleted[i] = true;
        decompose(_getOther(i, root), edges, centroidTree, root);
    }
    return root;
}
