#pragma once
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <functional>
#include <climits>
#include <random>

// Weighted adjacency list: adj[u] = {{v, weight}, ...}
using WAdj = std::vector<std::vector<std::pair<int, long long>>>;
// Unweighted adjacency list: adj[u] = {v, ...}
using Adj  = std::vector<std::vector<int>>;

static const long long GRAPH_INF = 2e18;

// =========================================================
// Graph generators
// =========================================================

// Random connected undirected weighted graph.
// Builds a random spanning tree first, then adds extra_edges more.
inline WAdj gen_connected_weighted(int n, int extra_edges, long long max_w, std::mt19937& rng) {
    WAdj adj(n);
    std::vector<int> nodes(n);
    std::iota(nodes.begin(), nodes.end(), 0);
    std::shuffle(nodes.begin(), nodes.end(), rng);
    for (int i = 1; i < n; i++) {
        long long w = rng() % max_w + 1;
        int u = nodes[i];
        int v = nodes[rng() % i];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    for (int i = 0; i < extra_edges; i++) {
        int u = rng() % n;
        int v = rng() % n;
        if (u == v) {
            i--;
            continue;
        }
        long long w = rng() % max_w + 1;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    return adj;
}

// Random DAG: edges only go from lower to higher index in a permuted labelling.
inline Adj gen_dag(int n, int m, std::mt19937& rng) {
    Adj adj(n);
    std::set<std::pair<int,int>> added;
    int attempts = 0;
    while ((int)added.size() < m && attempts < m * 20) {
        int u = rng() % (n - 1);
        int v = u + 1 + rng() % (n - 1 - u);
        if (!added.count({u, v})) {
            adj[u].push_back(v);
            added.insert({u, v});
        }
        attempts++;
    }
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), rng);
    Adj result(n);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            result[perm[u]].push_back(perm[v]);
        }
    }
    return result;
}

// Random directed graph; may contain cycles.
inline Adj gen_directed(int n, int m, std::mt19937& rng) {
    Adj adj(n);
    for (int i = 0; i < m; i++) {
        int u = rng() % n;
        int v = rng() % n;
        adj[u].push_back(v);
    }
    return adj;
}

// Flow network: guaranteed path src→sink, plus random extra edges.
inline WAdj gen_flow_network(int n, long long max_cap, std::mt19937& rng) {
    WAdj adj(n);
    for (int i = 0; i < n - 1; i++) {
        long long cap = rng() % max_cap + 1;
        adj[i].push_back({i + 1, cap});
    }
    for (int i = 0; i < n; i++) {
        int u = rng() % n;
        int v = rng() % n;
        if (u != v) {
            long long cap = rng() % max_cap + 1;
            adj[u].push_back({v, cap});
        }
    }
    return adj;
}

// =========================================================
// Reachability
// =========================================================

inline std::vector<bool> reachable_from(const Adj& adj, int n, int src) {
    std::vector<bool> vis(n, false);
    std::queue<int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    return vis;
}

inline std::vector<bool> reachable_from_weighted(const WAdj& adj, int n, int src) {
    std::vector<bool> vis(n, false);
    std::queue<int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    return vis;
}

// =========================================================
// Brute-force reference implementations
// =========================================================

// Bellman-Ford SSSP — reference for Dijkstra.
// Returns dist[i] = shortest distance from src; GRAPH_INF if unreachable.
inline std::vector<long long> brute_sssp(const WAdj& adj, int n, int src) {
    std::vector<long long> dist(n, GRAPH_INF);
    dist[src] = 0;
    for (int iter = 0; iter < n - 1; iter++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == GRAPH_INF) {
                continue;
            }
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    return dist;
}

// All-pairs shortest paths via brute_sssp — reference for Floyd-Warshall.
inline std::vector<std::vector<long long>> brute_apsp(const WAdj& adj, int n) {
    std::vector<std::vector<long long>> dist(n);
    for (int i = 0; i < n; i++) {
        dist[i] = brute_sssp(adj, n, i);
    }
    return dist;
}

// MST weight via Kruskal with simple path-compression DSU.
// edges: vector of {weight, u, v}. Returns -1 if graph is disconnected.
inline long long brute_mst_weight(int n, std::vector<std::tuple<long long,int,int>> edges) {
    std::sort(edges.begin(), edges.end());
    std::vector<int> par(n);
    std::iota(par.begin(), par.end(), 0);
    std::function<int(int)> find = [&](int x) {
        return par[x] == x ? x : par[x] = find(par[x]);
    };
    long long total = 0;
    int count = 0;
    for (auto [w, u, v] : edges) {
        int pu = find(u), pv = find(v);
        if (pu != pv) {
            par[pu] = pv;
            total += w;
            count++;
        }
    }
    return count == n - 1 ? total : -1LL;
}

// BFS-augmenting max flow — reference for Ford-Fulkerson and Edmonds-Karp.
// cap[u][v] = capacity (adjacency matrix form).
inline long long brute_max_flow(int n, std::vector<std::vector<long long>> cap, int src, int sink) {
    long long flow = 0;
    while (true) {
        std::vector<int> parent(n, -1);
        std::queue<int> q;
        q.push(src);
        parent[src] = src;
        while (!q.empty() && parent[sink] == -1) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
                if (parent[v] == -1 && cap[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        if (parent[sink] == -1) {
            break;
        }
        long long pushed = LLONG_MAX;
        for (int v = sink; v != src; v = parent[v]) {
            pushed = std::min(pushed, cap[parent[v]][v]);
        }
        for (int v = sink; v != src; v = parent[v]) {
            cap[parent[v]][v] -= pushed;
            cap[v][parent[v]] += pushed;
        }
        flow += pushed;
    }
    return flow;
}

// SCC count via pairwise BFS reachability check — reference for Kosaraju.
inline int brute_scc_count(const Adj& adj, int n) {
    Adj radj(n);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            radj[v].push_back(u);
        }
    }
    auto bfs = [&](const Adj& g, int src) {
        std::vector<bool> vis(n, false);
        std::queue<int> q;
        q.push(src);
        vis[src] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        return vis;
    };
    std::vector<int> comp(n, -1);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (comp[i] != -1) {
            continue;
        }
        comp[i] = cnt;
        auto fwd = bfs(adj, i);
        auto bwd = bfs(radj, i);
        for (int j = i + 1; j < n; j++) {
            if (comp[j] == -1 && fwd[j] && bwd[j]) {
                comp[j] = cnt;
            }
        }
        cnt++;
    }
    return cnt;
}

// Three-color DFS cycle detection — reference for CycleInDAG.
inline bool brute_has_cycle(const Adj& adj, int n) {
    std::vector<int> color(n, 0);
    std::function<bool(int)> dfs = [&](int u) -> bool {
        color[u] = 1;
        for (int v : adj[u]) {
            if (color[v] == 1) {
                return true;
            }
            if (color[v] == 0 && dfs(v)) {
                return true;
            }
        }
        color[u] = 2;
        return false;
    };
    for (int i = 0; i < n; i++) {
        if (color[i] == 0 && dfs(i)) {
            return true;
        }
    }
    return false;
}

// =========================================================
// Property checkers
// =========================================================

// Verify a set of edges forms a spanning tree of n nodes (n-1 edges, connected, acyclic).
inline bool is_spanning_tree(int n, const std::vector<std::pair<int,int>>& edges) {
    if ((int)edges.size() != n - 1) {
        return false;
    }
    std::vector<int> par(n);
    std::iota(par.begin(), par.end(), 0);
    std::function<int(int)> find = [&](int x) {
        return par[x] == x ? x : par[x] = find(par[x]);
    };
    for (auto [u, v] : edges) {
        int pu = find(u), pv = find(v);
        if (pu == pv) {
            return false;
        }
        par[pu] = pv;
    }
    int root = find(0);
    for (int i = 1; i < n; i++) {
        if (find(i) != root) {
            return false;
        }
    }
    return true;
}

// Verify every directed edge u→v has u appearing before v in order.
inline bool is_valid_topo_order(const Adj& adj, int n, const std::vector<int>& order) {
    if ((int)order.size() != n) {
        return false;
    }
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[order[i]] = i;
    }
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (pos[u] >= pos[v]) {
                return false;
            }
        }
    }
    return true;
}

// Verify Eulerian circuit: uses every edge exactly once and returns to start.
// orig_adj is an undirected adjacency list (each undirected edge appears once per side).
inline bool is_valid_euler_circuit(int n, const std::vector<std::vector<int>>& orig_adj, const std::vector<int>& circuit) {
    if (circuit.empty() || circuit.front() != circuit.back()) {
        return false;
    }
    std::map<std::pair<int,int>, int> avail;
    for (int u = 0; u < n; u++) {
        for (int v : orig_adj[u]) {
            avail[{std::min(u,v), std::max(u,v)}]++;
        }
    }
    for (auto& [e, cnt] : avail) {
        cnt /= 2;
    }
    int total = 0;
    for (auto& [e, cnt] : avail) {
        total += cnt;
    }
    if ((int)circuit.size() != total + 1) {
        return false;
    }
    for (int i = 0; i + 1 < (int)circuit.size(); i++) {
        int u = circuit[i], v = circuit[i + 1];
        auto key = std::make_pair(std::min(u,v), std::max(u,v));
        if (avail[key] <= 0) {
            return false;
        }
        avail[key]--;
    }
    return true;
}

// Verify SCC decomposition: every node in exactly one SCC, each SCC internally strongly connected.
inline bool is_valid_scc(const Adj& adj, int n, const std::vector<std::vector<int>>& sccs) {
    std::vector<int> comp(n, -1);
    for (int i = 0; i < (int)sccs.size(); i++) {
        for (int u : sccs[i]) {
            if (comp[u] != -1) {
                return false;
            }
            comp[u] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            return false;
        }
    }
    Adj radj(n);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            radj[v].push_back(u);
        }
    }
    auto bfs_within = [&](const Adj& g, int src, int scc_id, const std::vector<int>& comp_map) {
        std::vector<bool> vis(n, false);
        std::queue<int> q;
        q.push(src);
        vis[src] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!vis[v] && comp_map[v] == scc_id) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        return vis;
    };
    for (int i = 0; i < (int)sccs.size(); i++) {
        if (sccs[i].empty()) {
            continue;
        }
        int src = sccs[i][0];
        auto fwd = bfs_within(adj, src, i, comp);
        auto bwd = bfs_within(radj, src, i, comp);
        for (int u : sccs[i]) {
            if (!fwd[u] || !bwd[u]) {
                return false;
            }
        }
    }
    return true;
}
