// O(VlogV + ElogV)
// Single Source Shortest Path

void Dijkstra(int s, int n, vector<ll> &dist, vector<int> &parent, vector<pair<int, ll>> *adj) {
	dist.assign(n, INF);
	parent.assign(n, -1);
	dist[s] = 0;
	priority_queue <pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
	q.push({0, s});
	while (!q.empty()) {
		pair<ll, int> here = q.top();
		q.pop();
		int v = here.ss;
		ll d_v = here.ff;
		if (d_v != dist[v])
			continue;
		for (auto edge : adj[v]) {
			if (dist[v] + edge.ss < dist[edge.ff]) {
				dist[edge.ff] = dist[v] + edge.ss;
				parent[edge.ff] = v;
				q.push({dist[edge.ff], edge.ff});
			}
		}
	}
}