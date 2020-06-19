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
#define debug(x) cout << #x << " " << x <<endl;
#define set_bits __builtin_popcount
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
void build_tree(ll *arr, ll*tree, int start, int end, int index)
{
	if (start == end)
	{
		tree[index] = arr[start];
		return;
	}
	int mid = (start + end) / 2;
	build_tree(arr, tree, start, mid, 2 * index);
	build_tree(arr, tree, mid + 1, end, 2 * index + 1);
	tree[index] = tree[2 * index] + tree[2 * index + 1];
}
void update(ll *arr, ll*tree, int start, int end, int index, int query_index, ll value)
{
	if (start == end)
	{
		tree[index] = value;
		arr[start] = value;
		return;
	}
	int mid = (start + end) / 2;
	if (mid >= query_index)
		update(arr, tree, start, mid, 2 * index, query_index, value);
	else
		update(arr, tree, mid + 1, end, 2 * index + 1, query_index, value);
	tree[index] = tree[2 * index] + tree[2 * index + 1];
}
ll query(ll *tree, int start, int end, int index, int left, int right)
{
	if (start > right || end < left)
		return 0;
	if (start >= left && end <= right)
		return tree[index];
	int mid = (start + end) / 2;
	int val1 = query(tree, start, mid, 2 * index, left, right);
	int val2 = query(tree, mid + 1, end, 2 * index + 1, left, right);
	return val1 + val2;
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
	ll *arr = new ll[n]();
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	ll *tree = new ll[4 * n]();
	build_tree(arr, tree, 0, n - 1, 1);
	cout << ans << endl;
	return 0;
}