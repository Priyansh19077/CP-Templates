// O(V+E) — Detect cycle in a directed graph using DFS three-color marking
// edges[u] = adjacency list; returns true if a cycle exists
#include <vector>

static bool _cycle_dfs(int u, std::vector<int>* edges,
                        std::vector<bool>& white, std::vector<bool>& grey, std::vector<bool>& black) {
    white[u] = false;
    grey[u] = true;
    for (int v : edges[u]) {
        if (grey[v]) return true;
        if (white[v] && _cycle_dfs(v, edges, white, grey, black)) return true;
    }
    grey[u] = false;
    black[u] = true;
    return false;
}

bool check_cycle(int n, std::vector<int>* edges) {
    std::vector<bool> white(n, true), grey(n, false), black(n, false);
    for (int i = 0; i < n; i++)
        if (white[i] && _cycle_dfs(i, edges, white, grey, black))
            return true;
    return false;
}
