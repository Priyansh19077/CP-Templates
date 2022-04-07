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
ll expo(ll a, ll b, ll mod)
{ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
vector<int> sieve(int n) {int*arr = new int[n + 1](); vector<int> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
void swap(int &x, int &y) {int temp = x; x = y; y = temp;}
ll combination(ll n, ll r, ll m, ll* fact) {ll val1 = fact[n]; ll val2 = mminvprime(fact[r], m); ll val3 = mminvprime(fact[n - r], m); return ((val1 * val2) % m * val3) % m;}
/*--------------------------------------------------------------------------------------------------------------------------*/
void counting_sort(vector<int> &p, vector<int> &c, int n)
{
	vector<int> cnt(n);
	for (auto x : c)
		cnt[x]++;
	vector<int> p_new(n);
	vector<int> pos(n);
	pos[0] = 0;
	for (int i = 1; i < n; i++)
		pos[i] = pos[i - 1] + cnt[i - 1];
	for (auto x : p)
	{
		int i = c[x];
		p_new[pos[i]] = x;
		pos[i]++;
	}
	p = p_new;
}
int main()
{
	fastio();
#ifndef ONLINE_JUDGE
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
	freopen("Error.txt", "w", stderr);
#endif
	string s;
	cin >> s;
	s += '$';
	int n = s.length();
	vector<int> p(n), c(n);
	{
		vector<pair<char, int>> a(n);
		for (int i = 0; i < n; i++)
			a[i] = {s[i], i};
		sort(a.begin(), a.end());
		for (int i = 0; i < n; i++)
			p[i] = a[i].ss;
		c[p[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			if (a[i].ff == a[i - 1].ff)
				c[p[i]] = c[p[i - 1]];
			else
				c[p[i]] = c[p[i - 1]] + 1;
		}
	}
	int k = 0;
	while ((1 << k) < n)
	{
		for (int i = 0; i < n; i++)
			p[i] = (p[i] - (1 << k) + n) % n;
		counting_sort(p, c, n);
		vector<int> c_new(n);
		c_new[p[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
			pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
			if (now == prev)
				c_new[p[i]] = c_new[p[i - 1]];
			else
				c_new[p[i]] = c_new[p[i - 1]] + 1;
		}
		k++;
		c = c_new;
	}
	for (int i = 0; i < n; i++)
		cout << p[i] << " ";
	cout << endl;
	return 0;
}
