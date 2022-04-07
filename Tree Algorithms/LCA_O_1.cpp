template<typename Node>
struct SparseTable {
    vector<vector<Node>> table;
    vector<int> logValues;
    int n;
    int maxLog;
    vector<int> a;
    SparseTable(int n1, vector<int> &arr) {
        n = n1;
        a = arr;
        table.resize(n);
        logValues.resize(n + 1);
        maxLog = log2(n);
        logValues[1] = 0;
        for (int i = 2; i <= n; i++) {
            logValues[i] = logValues[i / 2] + 1;
        }
        for (int i = 0; i < n; i++) {
            table[i].resize(maxLog + 1);
            fill(all(table[i]), Node());
        }
        build();
    }
    void build() {
        for (int i = 0; i < n; i++) {
            table[i][0] = Node(a[i], i);
        }
        for (int i = 1; i <= maxLog; i++) {
            for (int j = 0; (j + (1 << i)) <= n; j++) {
                table[j][i].merge(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    Node queryNormal(int left, int right) {
        Node ans = Node();
        for (int j = logValues[right - left + 1]; j >= 0; j--) {
            if ((1 << j) <= right - left + 1) {
                ans.merge(ans, table[left][j]);
                left += (1 << j);
            }
        }
        return ans;
    }
    Node queryIdempotent(int left, int right) {
        int j = logValues[right - left + 1];
        Node ans = Node();
        ans.merge(table[left][j], table[right - (1 << j) + 1][j]);
        return ans;
    }
};
struct Node1 {
    int val; // store more info if required
    int index;
    Node1() { // Identity Element
        val = 1e9;
        index = -1;
    }
    Node1(int v, int ind) {
        val = v;
        index = ind;
    }
    void merge(Node1 &l, Node1 &r) {
        if(l.val < r.val){
            val = l.val;
            index = l.index;
        }else{
            val = r.val;
            index = r.index;
        }
    }
};
struct LCA_O_1{
    int n;
    vector<int> eulerTour, index;
    vector<int> node;
    SparseTable<Node1> sp = SparseTable<Node1>(0, eulerTour);
    LCA_O_1(int n1, vector<int>* edges, int root){
        n = n1;
        index.resize(n);
        dfs(root, edges, -1, 0);
        sp = SparseTable<Node1>(sz(eulerTour), eulerTour);
        debug(sz(eulerTour))
    }
    void dfs(int root, vector<int>* edges, int parent, int height){
        eulerTour.pb(height);
        node.pb(root);
        index[root] = sz(eulerTour) - 1;
        for(auto i : edges[root]){
            if(i != parent){
                dfs(i, edges, root, height + 1);
                eulerTour.pb(height);
                node.pb(root);
            }
        }
    }
    inline int query(int a, int b){
        return node[sp.queryIdempotent(min(index[a], index[b]), max(index[a], index[b])).index];
    }
    inline int getDepth(int a){
        return eulerTour[index[a]];
    }
};