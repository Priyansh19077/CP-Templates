void dfs(int root, set<pair<int, int>>* edges, vector<int>& path){
    while(sz(edges[root])){
        pair<int, int> p = *edges[root].begin();
        edges[root].erase(p);
        edges[p.ff].erase({root, p.ss});
        dfs(p.ff, edges, path);
    }
    path.pb(root);
}
vector<vector<int>> EulerCircuits(int n, vector<int>* edges){
    // when sending an undirected graph don't add the edges in the edgesVector on both sides
    // for undirected graph
    // modify it for directed graph by starting at node with outdegree odd and ending at indegree odd
    // undirected -> circuit - all even, path - 2 odd
    // directed -> circuit -> all even, path - 1 out > in, 1 in > out
    vector<vector<int>> circuits;
    int counter = 0;
    set<pair<int, int>> *newEdges = new set<pair<int, int>>[n];
    for(int i = 0; i < n; i++){
        for(auto j : edges[i]){
            newEdges[i].insert({j, counter});
            newEdges[j].insert({i, counter});
            counter++;
        }
    }
    for(int i = 0; i < n; i++){
        if(sz(newEdges[i]) & 1)
            return circuits;
    }
    for(int i = 0; i < n; i++){
        if(sz(newEdges[i])){
            vector<int> path;
            dfs(i, newEdges, path);
            circuits.pb(path);
        }
    }
    return circuits;
}
