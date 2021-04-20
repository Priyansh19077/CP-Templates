// O(n ^ 3)
// All pair shortest paths
// Negative Cycle needs to be checked otherwise the answer can be very negative resulting in overflows
// Maintain p[][] for getting path.Recursively find path between i and p[i][j], p[i][j] and j.

void FloydWarshall(int n, vector<pair<int, ll>> *adj, vector<vector<ll>> &dist) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (auto j : adj[i]) {
			dist[i][j.ff] = min(dist[i][j.ff], j.ss);
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] < INF && dist[k][j] < INF) // for updating only when there is a path
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}