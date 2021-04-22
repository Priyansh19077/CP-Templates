
int main()
{
	fastio();
#ifndef ONLINE_JUDGE
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
	freopen("Error.txt", "w", stderr);
#endif
	int n;
	cin >> n;
	vector<int> *edges = new vector<int>[n];
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		edges[u - 1].pb(v - 1);
		edges[v - 1].pb(u - 1);
	}
	int **parent = new int*[n];
	int *level = new int[n]();
	int limit = log2(n) + 1;

	bool *visited = new bool[n]();
	dfs(0, edges, parent, visited);
	visited = new bool[n]();
	dfs1(0, edges, level, visited);
	for (int i = 1; i < limit; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int x = parent[j][i - 1];
			if (x == -1)
				parent[j][i] = -1;
			else
				parent[j][i] = parent[x][i - 1];
		}
	}
	return 0;
}