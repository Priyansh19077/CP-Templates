// O(E * maxFlow) — Maximum flow via Ford-Fulkerson (DFS augmenting paths)
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

    long long dfs(int root, long long currValue) {
        visited[root] = iteration;
        if (root == dest) {
            return currValue;
        }
        for (int i : edges[root]) {
            Edge& e1 = edgesT[i];
            if (visited[e1.dest] != iteration && e1.val > 0) {
                long long val = dfs(e1.dest, min(e1.val, currValue));
                if (val > 0) {
                    edgesT[e1.residualIndex].val += val;
                    e1.val -= val;
                    return val;
                }
            }
        }
        return 0;
    }

    long long maxFlow() {
        if (!solved) {
            solved = true;
            while (true) {
                long long f = dfs(src, INF);
                if (f == 0) break;
                flow += f;
                iteration++;
            }
        }
        return flow;
    }
};
