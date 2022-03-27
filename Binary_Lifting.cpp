struct BinaryLifting {
    int n;
    int maxLog;
    ll maxRequirement;
    vector<vector<int>> parent;
    BinaryLifting(int n1, vector<int> *edges, ll requirement, int root) {
        n = n1;
        parent.resize(n1);
        maxLog = log2(requirement + 1);
        maxRequirement = requirement;
        for (int i = 0; i < n; i++) {
            parent[i].resize(maxLog + 1);
            for (int j = 0; j <= maxLog; j++) {
                parent[i][j] = -1;
            }
        }
        fillParentTable(root, edges);
    }
    void fillParentTable(int root, vector<int> *edges) {
        vector<bool> visited(n);
        dfsBinaryLifting(root, edges, visited);
        int intermediate = -1;
        for (int i = 1; i <= maxLog; i++) {
            for (int j = 0; j < n; j++) {
                intermediate = parent[j][i - 1];
                if (intermediate != -1) {
                    parent[j][i] = parent[intermediate][i - 1];
                }
            }
        }
    }
    void dfsBinaryLifting(int root, vector<int> *edges, vector<bool> &visited) {
        visited[root] = true;
        for (auto i : edges[root]) {
            if (!visited[i]) {
                parent[i][0] = root;
                dfsBinaryLifting(i, edges, visited);
            }
        }
    }
    int kthParent(int x, int k) {
        for(int i = 0; i <= maxLog; i++){
            if((k >> i) & 1){ 
                if(x == -1)
                    return x;
                x = parent[x][i];
            }
        }
        return x;
    }
};