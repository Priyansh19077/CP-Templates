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
ll substring_hash_value(int i, int j, ll hash[], ll m)
{
	ll val1 = ((m + hash[j] - ((i > 0) ? hash[i - 1] : 0)) % m);
	return val1;
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
	ll m = 1000000009;
	int n = s.length();
	int p = 31; // 53 if both uppercase and lowercase are to be considered
	ll *hash = new ll[n];
	//this hash array will store the hash of prefix substrings;
	ll hash_value = 0;
	ll *power_of_p = new ll[n];
	power_of_p[0] = 1;
	for (int i = 0; i < n; i++)
	{
		char ch = s[i];
		ll val1 = ((ch - 'a' + 1) * power_of_p[i]) % m;
		hash_value += val1;
		hash[i] = hash_value;
		if (i != n - 1)
			power_of_p[i + 1] = (power_of_p[i] * p) % m;
	}
	int q;
	cin >> q;
	while (q--)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;
		b--;
		c--;
		d--;
		ll f = substring_hash_value(a, b, hash, m);
		ll g = substring_hash_value(c, d, hash, m);
		f = (f * power_of_p[c - a]) % m;
		if (f == g)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}