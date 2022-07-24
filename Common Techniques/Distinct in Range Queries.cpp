bool compare(pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b){
    return a.ff.ss < b.ff.ss;
}
void update(int index, vector<int>& bit, int value){
    for(; index < sz(bit); index += (index & (-index))){
        bit[index] += value;
    }
}
int query(int index, vector<int>& bit){
    int sum = 0;
    for(; index > 0; index -= (index & (-index))){
        sum += bit[index];
    }
    return sum;
}
vector<int> distinctQueries(int n, int q, vector<int>& arr, vector<pair<int, int>>& queries){
    map<int, int> compression;
    int prev = 0;
    for(auto &i : arr){
        if(compression.find(i) == compression.end()){
            compression[i] = prev;
            prev++;
        }
        i = compression[i];
    }
    vector<int> lastIndex(sz(compression), -1);
    vector<pair<pair<int, int>, int>> tempQueries(q);
    for(int i = 0; i < q; i++){
        tempQueries[i].ff.ff = queries[i].ff + 1;
        tempQueries[i].ff.ss = queries[i].ss + 1;
        tempQueries[i].ss = i;
    }
    vector<int> ans(q);
    sort(all(tempQueries), compare);
    int num = 0;
    vector<int> bit(n + 1);
    for(int i = 0; i < n; i++){
        if(lastIndex[arr[i]] != -1){
            update(lastIndex[arr[i]] + 1, bit, -1);
        }
        lastIndex[arr[i]] = i;
        update(i + 1, bit, 1);
        while(num < q && tempQueries[num].ff.ss == i + 1){
            int index = tempQueries[num].ss;
            ans[index] = query(i + 1, bit) - query(tempQueries[num].ff.ff - 1, bit);
            num++;
        }
    }
    return ans;
}