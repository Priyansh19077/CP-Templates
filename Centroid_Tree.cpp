vector<pair<int, int>> edgeList;
vector<bool> deleted;
vector<int> subtree;
inline int getD(int index, int s){
    return edgeList[index].ff ^ edgeList[index].ss ^ s;
}
void computeSubtrees(int root, vector<int>* edges, int parent){
    subtree[root] = 1;
    for(auto i : edges[root]){
        int dest = getD(i, root);
        if(!deleted[i] && dest != parent){
            computeSubtrees(dest, edges, root);
            subtree[root] += subtree[dest];
        }
    }
}
int findCentroid(int root, vector<int>* edges, int n, int parent){
    for(auto i : edges[root]){
        int dest = getD(i, root);
        if(!deleted[i] && dest != parent && subtree[dest] > n / 2){
            return findCentroid(dest, edges, n, root);
        }
    }
    return root;
}
int decompose(int root, vector<int>* edges, vector<int>* edgesN, int parent){
    computeSubtrees(root, edges, -1);
    int n = subtree[root];
    root = findCentroid(root, edges, n, -1);
    if(parent != -1){
        edgesN[root].pb(parent);
        edgesN[parent].pb(root);
    }
    for(auto i : edges[root]){
        int dest = getD(i, root);
        if(deleted[i])
            continue;
        deleted[i] = true;
        decompose(dest, edges, edgesN, root);
    }
    return root;
}
void solve() {
    int n;
    cin >> n;
    edgeList.clear();
    deleted.clear();
    vector<int>* edges= new vector<int>[n];
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        edges[a].pb(sz(edgeList));
        edges[b].pb(sz(edgeList));
        edgeList.pb({a, b});
        deleted.pb(0);
    }
    vector<int>* edgesN = new vector<int>[n];
    subtree.resize(n);
    fill(all(subtree), 0);
    int root = 0;
    root = decompose(root, edges, edgesN, -1);
}