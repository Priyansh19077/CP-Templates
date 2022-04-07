/* Priyansh Agarwal*/
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<unordered_set>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<map>
#include<chrono>
using namespace std;
using namespace __gnu_pbds;
using namespace chrono;
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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > pbds;
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
vector<int> sieve(int n) {int*arr = new int[n + 1](); vector<int> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
/*--------------------------------------------------------------------------------------------------------------------------*/
const int block_size = 450;
bool compare(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2)
{
	int b1 = p1.ff.ff / block_size;
	int b2 = p2.ff.ff / block_size;
	if (b1 == b2)
		return b1 % 2 == 0 ? (p1.ff.ss < p2.ff.ss) : (p1.ff.ss > p2.ff.ss);
	return b1 < b2;
}
int main()
{
	fastio();
#ifndef ONLINE_JUDGE
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
	freopen("Error.txt", "w", stderr);
#endif
	auto start1 = high_resolution_clock::now();
	int n, q;
	cin >> n >> q;
	// block_size = int(sqrt(n + 0.0) + 1);
	int *arr = new int[n];
	int *freq = new int[n + 1]();
	int number = 1;
	map<int, int> coordinate_compression;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		if (coordinate_compression.find(arr[i]) == coordinate_compression.end())
		{
			coordinate_compression[arr[i]] = number;
			arr[i] = number;
			number++;
		}
		else
			arr[i] = coordinate_compression[arr[i]];
	}
	int start = 0;
	int end = -1;
	vector<pair<pair<int, int>, int>> ans(q);
	for (int i = 0; i < q; i ++)
	{
		int a, b;
		cin >> a >> b;
		ans[i] = {{a, b}, i};
	}
	sort(ans.begin(), ans.end(), compare);
	int *ans1 = new int[q];
	int count = 0;
	for (auto i : ans)
	{
		pair<pair<int, int>, int> p1 = i;
		int right = p1.ff.ss - 1;
		int left = p1.ff.ff - 1;
		while (start < left)
		{
			int x = arr[start];
			freq[x]--;
			if (freq[x] == 0)
				count--;
			start++;
		}
		while (start > left)
		{
			start--;
			int x = arr[start];
			freq[x]++;
			if (freq[x] == 1)
				count++;
		}
		while (end < right)
		{
			end++;
			int x = arr[end];
			freq[x]++;
			if (freq[x] == 1)
				count++;
		}
		while (end > right)
		{
			int x = arr[end];
			freq[x]--;
			if (freq[x] == 0)
				count--;
			end--;
		}
		ans1[p1.ss] = count;
	}
	for (int i = 0; i < q; i++)
		cout << ans1[i] << "\n";
	auto stop1 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop1 - start1);
#ifndef ONLINE_JUDGE
	cerr << "Time: " << duration.count() / 1000.0 << endl;
#endif
	return 0;
}