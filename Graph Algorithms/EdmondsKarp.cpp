// O(VE²) — Maximum Network Flow via Edmonds-Karp (BFS-based Ford-Fulkerson)
// Build Flow(edges, n, source, sink), then call maxFlow()
// edges[u] = list of {v, capacity}
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int index, src, dest, residualIndex;
    long long val;
};

struct Flow {
    int n, src, dest, iteration = 0;
    vector<Edge> edgesT;
    vector<vector<int>> edges;
    vector<int> visited;
    bool solved = false;
    long long flow = 0;

    Flow(vector<pair<int, long long>>* adj, int n, int s, int d)
        : n(n), src(s), dest(d), edges(n), visited(n, 0), iteration(1) {
        for (int u = 0; u < n; u++) {
            for (auto [v, cap] : adj[u]) {
                Edge e1 = {(int)edgesT.size(), u, v, (int)edgesT.size() + 1, cap};
                Edge e2 = {(int)edgesT.size() + 1, v, u, (int)edgesT.size(), 0};
                edges[u].push_back(e1.index);
                edges[v].push_back(e2.index);
                edgesT.push_back(e1);
                edgesT.push_back(e2);
            }
        }
    }

    long long bfs() {
        const long long INF = LLONG_MAX / 2;
        queue<int> q;
        q.push(src);
        visited[src] = iteration;
        vector<int> prev(n, -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == dest) break;
            for (int i : edges[u]) {
                Edge& e = edgesT[i];
                if (visited[e.dest] != iteration && e.val > 0) {
                    visited[e.dest] = iteration;
                    prev[e.dest] = e.index;
                    q.push(e.dest);
                }
            }
        }
        if (prev[dest] == -1) return 0;

        long long pushed = INF;
        for (int u = dest; prev[u] != -1; u = edgesT[prev[u]].src)
            pushed = min(pushed, edgesT[prev[u]].val);
        for (int u = dest; prev[u] != -1; u = edgesT[prev[u]].src) {
            edgesT[prev[u]].val -= pushed;
            edgesT[edgesT[prev[u]].residualIndex].val += pushed;
        }
        return pushed;
    }

    long long maxFlow() {
        if (!solved) {
            solved = true;
            while (true) {
                long long f = bfs();
                if (f == 0) break;
                flow += f;
                iteration++;
            }
        }
        return flow;
    }
};
