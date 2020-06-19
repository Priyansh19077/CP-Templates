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
int const NMAX = 100010;
int const BMAX = 500;
ll arr[NMAX];
ll prefix[NMAX];
ll b2[BMAX];
int n, q, count1;
int bstart[BMAX];
int bend[BMAX];
int bid[BMAX];
unordered_map<ll, int> b1[BMAX];
void build()
{
	int BSIZE = 1;
	while (BSIZE * BSIZE < n)
		BSIZE++;
	prefix[0] = arr[0];
	for (int i = 1; i < n; i++)
		prefix[i] = prefix[i - 1] ^ arr[i];
	count1 = 0;
	for (int i = 0; i < n; i += BSIZE)
	{
		bstart[count1] = i;
		bend[count1] = i + BSIZE - 1;
		count1++;
	}
	bend[count1 - 1] = n - 1;
	for (int i = 0; i < count1; i++)
	{
		b2[i] = 0;
		for (int j = bstart[i]; j <= bend[i]; j++)
		{
			b1[i][prefix[j]]++;
			bid[j] = i;
		}
	}
}
void query()
{
	int type;
	cin >> type;
	int x;
	ll k;
	cin >> x >> k;
	x--;
	int id = bid[x];
	if (type == 1)
	{
		ll val = arr[x] ^ k;
		arr[x] = k;
		for (int i = x; i <= bend[id]; i++)
		{
			b1[id][prefix[i]]--;
			if (b1[id][prefix[i]] <= 0)
				b1[id].erase(prefix[i]);
			prefix[i] ^= val;
			b1[id][prefix[i]]++;
		}
		for (int i = id + 1; i < count1; i++)
			b2[i] ^= val;
	}
	else
	{
		ll ans = 0;
		for (int i = 0; i < id; i++)
		{
			ll val = k ^ b2[i];
			if (b1[i].find(val) == b1[i].end())
				continue;
			else
				ans += b1[i][val];
		}
		for (int i = bstart[id]; i <= x; i++)
		{
			if (prefix[i] == k ^ b2[i])
				ans++;
		}
		cout << ans << endl;
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
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	build();
	while (q--)
		query();
	return 0;
}