//Input should be in Edge List type array
//O(N^2) algorithm
//Can be optimised using Union-find by rank and path algorithm
//Sorting the array of edges in terms of ascending order of the weights
//Output as n-1 edges which do not form a cycle
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
class Edge {
public:
	int source;
	int dest;
	ll weight;
};
bool compare1(Edge e1, Edge e2)
{
	//sorting the array of edges in terms of ascending order of weight
	return e1.weight < e2.weight;
}
int getParent(int v, int *parent)
{
	if (parent[v] == v)
		return v;
	else
		return getParent(parent[v], parent);
}
Edge* kruskals(Edge* edges, int n, int e)
{
	sort(edges, edges + e, compare1);
	int* parent = new int[n];
	Edge* output = new Edge[n - 1];
	for (int i = 0; i < n; i++)
		parent[i] = i;
	int count = 0;
	int i = 0;
	while (count < n - 1)
	{
		Edge currentEdge = edges[i];
		//check the topmost parent of v1 and v2
		//v1 and v2 are verices of the current edge
		int srcParent = getParent(currentEdge.source, parent);
		int destParent = getParent(currentEdge.dest, parent);
		if (srcParent != destParent)
		{
			output[count++] = currentEdge;
			parent[srcParent] = destParent;
		}
		i++;
	}
	delete[] parent;
	return output;
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
	Edge *edges = new Edge[e];
	//The input is taken considering 0-based indexing
	//Change to 1 based as per the question
	for (int i = 0; i < e; i++)
		cin >> edges[i].source >> edges[i].dest >> edges[i].weight;
	Edge *output = kruskals(edges, n, e);
	for (int i = 0; i < n - 1; i++)
		cout << output[i].source << " " << output[i].dest << " " << output[i].weight << endl;
	delete[] output;
	return 0;
}