// O(E log E) — Eulerian circuit(s) via Hierholzer's algorithm
// edges[u] = directed neighbors to pass for undirected graph (each undirected edge from one side)
// Returns list of Eulerian circuits; empty if any node has odd degree
#include <bits/stdc++.h>
using namespace std;

void eulerDFS(int root, set<pair<int, int>>* edges, vector<int>& path) {
    while (!edges[root].empty()) {
        pair<int, int> p = *edges[root].begin();
        edges[root].erase(p);
        edges[p.first].erase({root, p.second});
        eulerDFS(p.first, edges, path);
    }
    path.push_back(root);
}

vector<vector<int>> eulerCircuits(int n, vector<int>* edges) {
    vector<vector<int>> circuits;
    int counter = 0;
    set<pair<int, int>>* newEdges = new set<pair<int, int>>[n];
    for (int i = 0; i < n; i++) {
        for (int j : edges[i]) {
            newEdges[i].insert({j, counter});
            newEdges[j].insert({i, counter});
            counter++;
        }
    }
    for (int i = 0; i < n; i++) {
        if ((int)newEdges[i].size() & 1) {
            delete[] newEdges;
            return circuits;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!newEdges[i].empty()) {
            vector<int> path;
            eulerDFS(i, newEdges, path);
            circuits.push_back(path);
        }
    }
    delete[] newEdges;
    return circuits;
}
