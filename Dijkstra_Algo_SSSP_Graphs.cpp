// Dijkstra's Algorithm to find shortest paths form a paritcular vertex to all the other vertices
// O(ElogV)
// Just like Prim's Alorithm.
// Better to use a set here instead of a Priority Queue becuase Priority Queue does not support updating
// Implement Prim's Algorithm also through a set only
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
typedef priority_queue<int, vector<int>, function<bool(int, int)>> pq_func;
/*---------------------------------------------------------------------------------------------------------------------------*/
int gcd(int a, int b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
vector<int> sieve(int n) {int*arr = new int[n + 1](); vector<int> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
void swap(int &x, int &y) {int temp = x; x = y; y = temp;}
/*--------------------------------------------------------------------------------------------------------------------------*/
void Dijkstra(int start, vector<pair<int, ll>>* edges, ll *arr, int n, bool* visited)
{
	set<pair<ll, int>> s;
	s.insert({ll(start), 0});
	while (!s.empty())
	{
		//pop out the first element and finalize its distance
		pair<ll, int> top = *s.begin();
		int element = top.ss;
		visited[element] = true;
		int distance = top.ff;
		arr[element] = distance;
		s.erase(s.begin());
		//update all the other neighbours of that element
		for (int i = 0; i < edges[element].size(); i++)
		{
			// debug(distance);
			if (visited[edges[element][i].ff])
				continue;
			if (distance + edges[element][i].ss < arr[edges[element][i].ff])
			{
				auto f = s.find({arr[edges[element][i].ff], edges[element][i].ff});
				if (f != s.end())
					// cout << 1 << endl;
					s.erase(f);
				s.insert({distance + edges[element][i].ss, edges[element][i].ff});
				arr[edges[element][i].ff] = distance + edges[element][i].ss;
			}
		}
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
	int n, m;
	cin >> n >> m;
	vector<pair<int, ll>> *edges = new vector<pair<int, ll>>[n];
	for (int i = 0; i < m; i++)
	{
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--; b--; 	//considering bidirectional edges
		edges[a].pb({b, c});
		edges[b].pb({a, c});
	}
	ll* shortest_paths = new ll[n]; // from the vertex 0
	for (int i = 0; i < n; i++)
		shortest_paths[i] = 1e18;
	shortest_paths[0] = 0;
	int start = 0;
	bool *visited = new bool[n]();
	Dijkstra(start, edges, shortest_paths, n, visited);
	for (int i = 0; i < n; i++)
		cout << shortest_paths[i] << " ";
	cout << endl;
	return 0;
}