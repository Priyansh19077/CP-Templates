void BellmanFord(int n, int src, vector<pair<int, ll>> *edges, vector<ll>& dist, set<int>& negCycle) {
	fill(all(dist), INF);
	dist[src] = 0;
	vector<pair<ll, pair<int, int>>> e;
	for (int i = 0; i < n; i++) {
		for (auto j : edges[i]) {
			e.pb({j.ss, {i, j.ff}});
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (auto j : e) {
			dist[j.ss.ss] = min(dist[j.ss.ss], dist[j.ss.ff] + j.ff);
		}
	}
	//checking negative cycle
	for (int i = 0; i < n; i++) {
		for (auto j : e) {
			if (dist[j.ss.ss] > dist[j.ss.ff] + j.ff) {
				dist[j.ss.ss] = dist[j.ss.ff] + j.ff;
				negCycle.insert(j.ss.ss);
			}
		}
	}
}