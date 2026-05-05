struct Edge{
    int index;
    int src, dest;
    ll val;
    int residualIndex;
};
struct Flow{
    int n;
    int src, dest;
    int iteration = 0;
    vector<Edge> edgesT;
    vector<vector<int>> edges;
    vector<int> visited;
    bool solved;
    ll flow;
    Flow(vector<pair<int, ll>>* edges1, int n1, int s, int d){
        n = n1, src = s, dest = d;
        solved = false;
        flow = 0, iteration = 1;
        visited.resize(n);
        fill(all(visited), 0);
        edges.resize(n);
        for(int i = 0; i < n; i++){
            for(auto j : edges1[i]){
                Edge e1 = {sz(edgesT), i, j.ff, j.ss, sz(edgesT) + 1};
                Edge e2 = {sz(edgesT) + 1, j.ff, i, 0, sz(edgesT)};
                edgesT.pb(e1);
                edgesT.pb(e2);
                edges[i].pb(e1.index);
                edges[j.ff].pb(e2.index);
            }
        }
    }
    ll dfs(int root, ll currValue){
        visited[root] = iteration;
        if(root == dest){
            return currValue;
        }
        for(auto i : edges[root]){
            Edge e1 = edgesT[i];
            Edge e2 = edgesT[e1.residualIndex];
            if(visited[e1.dest] != iteration && e1.val > 0){
                ll val = dfs(e1.dest, min(e1.val, currValue));
                if(val > 0){
                    e1.val -= val;
                    e2.val += val;
                    edgesT[i] = e1;
                    edgesT[e1.residualIndex] = e2;
                    return val;
                }
            }
        }
        return 0;
         
    }
    void FordFulkersonFlow(){
        while(true){ // random shuffle before every iteration to tackle specially constructed cases
            ll f = dfs(src, INF);
            if(f == 0)
                return;
            flow += f;
            iteration++;
        }
    }
    ll maxFlow(){
        if(!solved){
            solved = true;
            FordFulkersonFlow();
        }
        return flow;
    }
};