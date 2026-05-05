/* Priyansh Agarwal*/
#include<bits/stdc++.h>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<unordered_set>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<map>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define nline "\n"
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define debug(x) cout << #x << " " << x <<endl;
#define set_bits __builtin_popcount
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
void swap(int &x, int &y) {int temp = x; x = y; y = temp;}
ll combination(ll n, ll r, ll m, ll* fact) {ll val1 = fact[n]; ll val2 = mminvprime(fact[r], m); ll val3 = mminvprime(fact[n - r], m); return ((val1 * val2) % m * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
/*--------------------------------------------------------------------------------------------------------------------------*/
void dfs(int start, vector<int>*edges, bool *visited, vector<int>& ans)
{
	visited[start] = true;
	for (auto i : edges[start])
	{
		if (visited[i])
			continue;
		dfs(i, edges, visited, ans);
	}
	ans.pb(start);
}
vector<int> topo_sort(int n, vector<int>*edges)
{
	vector<int> v1;
	bool *visited = new bool[n]();
	for (int i = 0; i < n; i++)
	{
		if (visited[i])
			continue;
		dfs(i, edges, visited, v1);
	}
	reverse(v1.begin(), v1.end());
	return v1;
}
int main()
{
	fastio();
#ifndef ONLINE_JUDGE
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
	freopen("Error.txt", "w", stderr);
#endif
	int n, m;
	cin >> n >> m;
	vector<int>*edges = new vector<int>[n];
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		edges[u].pb(v);
	}
	vector<int> v1 = topo_sort(n, edges);
	for (int i = 0; i < n; i++)
		cout << v1[i] + 1 << " ";
	cout << endl;
	return 0;
}