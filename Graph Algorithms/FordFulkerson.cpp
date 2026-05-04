// O(E * max_flow) — Maximum Network Flow via Ford-Fulkerson with DFS augmentation
// Build Flow(edges, n, source, sink), then call maxFlow()
// edges[u] = list of {v, capacity}
#include <climits>
#include <vector>

struct Edge {
    int index, src, dest, residualIndex;
    long long val;
};

struct Flow {
    int n, src, dest, iteration = 0;
    std::vector<Edge> edgesT;
    std::vector<std::vector<int>> edges;
    std::vector<int> visited;
    bool solved = false;
    long long flow = 0;

    Flow(std::vector<std::pair<int, long long>>* adj, int n, int s, int d)
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

    long long dfs(int u, long long pushed) {
        visited[u] = iteration;
        if (u == dest) return pushed;
        for (int i : edges[u]) {
            Edge& e = edgesT[i];
            if (visited[e.dest] != iteration && e.val > 0) {
                long long val = dfs(e.dest, std::min(e.val, pushed));
                if (val > 0) {
                    e.val -= val;
                    edgesT[e.residualIndex].val += val;
                    return val;
                }
            }
        }
        return 0;
    }

    long long maxFlow() {
        if (!solved) {
            solved = true;
            const long long INF = LLONG_MAX / 2;
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
