// O(V * E²) — Maximum flow via Edmonds-Karp (BFS augmenting paths)
// Usage: Flow f(adj, n, src, sink); long long result = f.maxFlow();
// adj[u] = list of {v, capacity} (directed edges)
#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;

struct Edge {
    int index;
    int src, dest;
    long long val;
    int residualIndex;
};

struct Flow {
    int n;
    int src, dest;
    int iteration;
    vector<Edge> edgesT;
    vector<vector<int>> edges;
    vector<int> visited;
    bool solved;
    long long flow;

    Flow(vector<pair<int, long long>>* adj, int n, int src, int dest) {
        this->n = n;
        this->src = src;
        this->dest = dest;
        solved = false;
        flow = 0;
        iteration = 1;
        visited.resize(n, 0);
        edges.resize(n);
        for (int i = 0; i < n; i++) {
            for (auto [v, cap] : adj[i]) {
                int idx = (int)edgesT.size();
                Edge e1 = {idx, i, v, cap, idx + 1};
                Edge e2 = {idx + 1, v, i, 0, idx};
                edgesT.push_back(e1);
                edgesT.push_back(e2);
                edges[i].push_back(e1.index);
                edges[v].push_back(e2.index);
            }
        }
    }

    long long bfs(int root) {
        queue<int> qu;
        qu.push(root);
        visited[root] = iteration;
        vector<int> prev(n, -1);
        while (!qu.empty()) {
            int node = qu.front();
            qu.pop();
            if (node == dest) break;
            for (int i : edges[node]) {
                Edge& e1 = edgesT[i];
                if (visited[e1.dest] != iteration && e1.val > 0) {
                    visited[e1.dest] = iteration;
                    prev[e1.dest] = e1.index;
                    qu.push(e1.dest);
                }
            }
        }
        if (prev[dest] == -1) return 0;
        long long finalValue = INF;
        for (int cur = dest; prev[cur] != -1; cur = edgesT[prev[cur]].src) {
            finalValue = min(finalValue, edgesT[prev[cur]].val);
        }
        for (int cur = dest; prev[cur] != -1; cur = edgesT[prev[cur]].src) {
            Edge& e1 = edgesT[prev[cur]];
            edgesT[e1.residualIndex].val += finalValue;
            e1.val -= finalValue;
        }
        return finalValue;
    }

    long long maxFlow() {
        if (!solved) {
            solved = true;
            while (true) {
                long long f = bfs(src);
                if (f == 0) break;
                flow += f;
                iteration++;
            }
        }
        return flow;
    }
};
