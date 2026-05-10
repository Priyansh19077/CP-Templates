// O(V + E) — Cycle detection via three-color DFS
// edges[u] = list of directed neighbors (0-indexed)
// Returns true if graph contains a cycle, false otherwise
#include <bits/stdc++.h>
using namespace std;

// Returns false if a cycle is detected (back edge to grey node)
bool cycleCheckDFS(int start, vector<int>* edges, vector<bool>& white, vector<bool>& grey, vector<bool>& black) {
    white[start] = false;
    grey[start] = true;
    for (int i : edges[start]) {
        if (grey[i]) return false;
        if (white[i]) {
            if (!cycleCheckDFS(i, edges, white, grey, black)) return false;
        }
    }
    grey[start] = false;
    black[start] = true;
    return true;
}

bool hasCycle(int n, vector<int>* edges) {
    vector<bool> white(n, true), grey(n, false), black(n, false);
    for (int i = 0; i < n; i++) {
        if (white[i]) {
            if (!cycleCheckDFS(i, edges, white, grey, black)) return true;
        }
    }
    return false;
}
