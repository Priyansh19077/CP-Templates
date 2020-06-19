//finding the LCA in NlogN time for the given tree
//program is written considering 0 as the root. Make changes whenever required
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
#define debug(x) cout << #x << " " << x <<endl;
typedef long long ll;
typedef unsigned long long ull;
/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
vector<int> sieve(int n) {int*arr = new int[n + 1](); vector<int> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
void swap(int &x, int &y) {int temp = x; x = y; y = temp;}
ll combination(ll n, ll r, ll m, ll* fact) {ll val1 = fact[n]; ll val2 = mminvprime(fact[r], m); ll val3 = mminvprime(fact[n - r], m); return ((val1 * val2) % m * val3) % m;}
/*--------------------------------------------------------------------------------------------------------------------------*/
int find_lca(int a, int b, int **parent, int *level, int limit)
{
	if (level[a] > level[b])
		swap(a, b);
	int d = level[b] - level[a];
	while (d > 0)
	{
		int i = int(log2(d));
		b = parent[b][i];
		d -= (1 << i);
	}
	if (a == b)
		return a;
	for (int i = limit - 1; i >= 0; i--)
	{
		if (parent[a][i] != -1 && (parent[a][i] != parent[b][i]))
		{
			a = parent[a][i];
			b = parent[b][i];
		}
	}
	return parent[a][0];
}
void dfs(int start, vector<int>*edges, int **parent , bool * visited)
{
	visited[start] = true;
	for (int i = 0; i < edges[start].size(); i++)
	{
		int x = edges[start][i];
		if (visited[x])
			continue;
		parent[x][0] = start;
		visited[x] = true;
		dfs(x, edges, parent, visited);
	}
}
void dfs1(int start, vector<int>*edges, int *level, bool * visited)
{
	visited[start] = true;
	for (int i = 0; i < edges[start].size(); i++)
	{
		int x = edges[start][i];
		if (visited[x])
			continue;
		level[x] = level[start] + 1;
		visited[x] = true;
		dfs1(x, edges, level, visited);
	}
}
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
	for (int i = 0; i < n; i++)
	{
		parent[i] = new int[limit];
		for (int j = 0; j < limit; j++)
			parent[i][j] = - 1;
	}
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