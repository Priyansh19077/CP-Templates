//Algorithm for finding all the strongly connected components
//Only valid for directed graph because in an undirected graph the vertexes in a connected component are the same as that in SCC
//First run dfs on the normal graph and push the vertices into stack after all their neighbours are discovered
//Then run dfs on the transposed graph and find out the SCC
//By pushing in stack we will make sure that we don't get the wrong answer for SCCs
//The Stack will contain those vertices at the top which can reach other vertices which would not be in their SCC at the top
//By doing this we don't pick the vertices together which are not in the SCC
//O(V+E)
//Input must be taken as usual in the adjacency list manner
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
void dfs(int start, vector<int>*edges, unordered_set<int>&visited, stack<int>&finishedVertices)
{
	visited.insert(start);
	for (int i = 0; i < edges[start].size(); i++)
		if (visited.count(edges[start][i]) == 0)
			dfs(edges[start][i], edges, visited, finishedVertices);
	finishedVertices.push(start);
}
void dfs1(int start, vector<int>*edges, unordered_set<int>&visited, unordered_set<int>* component)
{
	visited.insert(start);
	component->insert(start);
	for (int i = 0; i < edges[start].size(); i++)
		if (visited.count(edges[start][i]) == 0)
			dfs1(edges[start][i], edges, visited, component);
}
unordered_set<unordered_set<int>*>* getSCC(vector<int>*edges, vector<int>*edgesT, int n)
{
	unordered_set<int> visited;
	stack<int> finishedVertices;
	for (int i = 0; i < n; i++)
	{
		if (visited.count(i) == 0)
		{
			dfs(i, edges, visited, finishedVertices);
			finishedVertices.push(i);
		}
	}
	unordered_set<unordered_set<int>*>* components = new unordered_set<unordered_set<int>*>();
	visited.clear();
	while (finishedVertices.size() != 0)
	{
		int element = finishedVertices.top();
		finishedVertices.pop();
		if (visited.count(element) != 0)
			continue;
		unordered_set<int>* component = new unordered_set<int>();
		dfs1(element, edgesT, visited, component);
		components->insert(component);
	}
	return components;
}
int main()
{
	fastio();
#ifndef ONLINE_JUDGE
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
	freopen("Error.txt", "w", stderr);
#endif
	int n, e;
	cin >> n >> e;
	vector<int> *edges = new vector<int>[n];
	vector<int> *edgesT = new vector<int>[n];
	//Input taken considerting 1 based indexing
	for (int i = 0; i < e; i++)
	{
		int a, b;
		cin >> a >> b;
		edges[a - 1].pb(b - 1);
		edgesT[b - 1].pb(a - 1);
	}
	unordered_set<unordered_set<int>*>* components = getSCC(edges, edgesT, n);
	unordered_set<unordered_set<int>*>::iterator it = components->begin();
	while (it != components->end()) {
		unordered_set<int>* component = *it;
		unordered_set<int>::iterator it2 = component->begin();
		while (it2 != component->end()) {
			cout << *it2  + 1 << " ";
			it2++;
		}
		cout << endl;
		delete component;
		it++;
	}
	delete components;
	delete []edges;
	delete []edgesT;
	return 0;
}