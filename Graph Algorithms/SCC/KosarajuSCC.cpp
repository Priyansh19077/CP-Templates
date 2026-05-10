// O(V + E) — Strongly Connected Components via Kosaraju's algorithm
// edges: forward adjacency list; edgesT: reversed adjacency list (both raw arrays of size n)
// Returns list of SCCs; each SCC is a list of 0-indexed node IDs
#include <bits/stdc++.h>
using namespace std;

void topoSort(int start, vector<int>* edges, vector<int>& topo, vector<bool>& visited) {
    visited[start] = true;
    for (int i : edges[start]) {
        if (!visited[i]) {
            topoSort(i, edges, topo, visited);
        }
    }
    topo.push_back(start);
}

void getComponent(int start, vector<int>* edges, vector<int>& currComponent, vector<bool>& visited) {
    currComponent.push_back(start);
    visited[start] = true;
    for (int i : edges[start]) {
        if (!visited[i]) {
            getComponent(i, edges, currComponent, visited);
        }
    }
}

vector<vector<int>> getSCC(int n, vector<int>* edges, vector<int>* edgesT) {
    vector<bool> visited(n, false);
    vector<int> topo;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topoSort(i, edges, topo, visited);
        }
    }
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> SCC;
    for (int i = (int)topo.size() - 1; i >= 0; i--) {
        if (!visited[topo[i]]) {
            vector<int> comp;
            getComponent(topo[i], edgesT, comp, visited);
            SCC.push_back(comp);
        }
    }
    return SCC;
}
