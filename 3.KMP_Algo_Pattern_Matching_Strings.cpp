//KMP Algorithm to check pattern is present as a substring in the original string or not
//Frist find out the longest prefix which is also a suffix and ends at the ith index
//store this in the form of an array
//O(N+M)
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
typedef long long ll;
typedef unsigned long long ull;
typedef priority_queue<int, vector<int>, function<bool(int, int)>> pq_func;
void longest_prefix_suffix(int* lps, string pattern, int m)
{
	lps[0] = 0;
	int i = 1;
	int j = 0;
	while (i < m)
	{
		if (pattern[i] == pattern[j])
		{
			lps[i] = j + 1;
			j++;
			i++;
		}
		else
		{
			if (j != 0)
				j = lps[j - 1];
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
	return;
}
bool kmp(string a, string pattern, int n, int m)
{
	int *lps = new int[m];
	longest_prefix_suffix(lps, pattern, m);
	//longest_prefix_suffix array has been calculated now
	int i = 0;
	int j = 0;
	while (i < n && j < m)
	{
		if (pattern[j] == a[i])
		{
			i++;
			j++;
		}
		else
		{
			if (j != 0)
				j = lps[j - 1];
			else
				i++;
		}
	}
	return j == m;
}
int main()
{
	fastio();
#ifndef ONLINE_JUDGE
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
	freopen("Error.txt", "w", stderr);
#endif
	string s, pattern;
	cin >> s >> pattern;
	//make the prefix-suffix array
	int n = s.length();
	int m = pattern.length();
	bool search = kmp(s, pattern, n, m);
	//search variable stores the answer to the search according to kmp algorithm
	return 0;
}