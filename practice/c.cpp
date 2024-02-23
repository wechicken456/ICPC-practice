// https://open.kattis.com/problems/onewayroads?tab=metadata


/*
https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

The idea is that if for an edge (v,u), if index[v] < low[u], then it means that
a path starting at u doesn't loop/go to any earlier node, which means that it's a 
dead end so the answer is NO.

*/
#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define vb vector<bool>

using namespace std;

vector<vector<bool>>edge;
vector<int>low;
vector<int>idx;
int n, m;
static int t = 0; // time each node is visited

void dfs(int node, int par) {
	idx[node] = low[node] = t++;
	for (int i = 0 ;i < n; i++) {
		if (edge[node][i] == true) {
			edge[i][node] = false;
			if (i == par) continue;
			
			if (idx[i] == -1) {	// node hasn't been visited  yet
				dfs(i, node);
				low[node] = min(low[node], low[i]);
			}
			else {					// "already visited" == "found a loop"
				low[node] = min(low[node], idx[i]);	// there could be multiple loops, find the earliest one.
													// not using low[i] here because we haven't returned to i yet, so low[i] hasn't been updated
			}
			if (idx[node] < low[i]) {	// explained at the header
				cout << "NO\n";
				exit(0);
			}
		}
	}
}

int main () {
	cin >> n >> m;
	edge.assign(n, vector<bool>(n, false));
	low.resize(n);
	idx.assign(n, -1);
	for (int i = 0 ;i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;b--;
		edge[a][b] = true;
		edge[b][a] = true;
	}
	dfs(0, -1);
	cout << "YES\n";
	for (int i = 0 ;i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (edge[i][j]) cout << i + 1 << " " << j + 1 << "\n";
		}
	}
}
