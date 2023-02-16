// https://open.kattis.com/problems/abridgedreading

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

int n, m;
int levels;

struct Node {
	vector<int>ancestor;
	int total;
	int depth;
};

vector<Node>graph;

vector<pair<int , int>>dest;

vector<int>chapter;
vector<vector<pair<int, int>>>from; // from[i] = all paths start from i and the total pages so far.
vector<int>to;		// to[i] = node that leads to i (since there is only 1 node leading to i from the constraints, we dont need a vector)

void create_tree(int node, int sum, int origin, int depth) {
	
	sum += chapter[node];
	
	graph[node].total = sum;
	graph[node].ancestor.resize(levels);
	graph[node].ancestor[0] = to[node];
	graph[node].depth = depth;
	for (int i = 1 ; i < levels; i++) {
		graph[node].ancestor[i] = graph[ graph[node].ancestor[i-1] ].ancestor[i-1];
	}
	
	// reaches one destination
	if (from[node].size() == 0) { 
		dest.pb({node, origin});
		return;
	}
	
	for (auto &p : from[node]) {
		create_tree(p.second, sum, origin, depth + 1);
	}
}

int lca(int a, int b){ 
	if (graph[a].depth < graph[b].depth) swap(a, b);
	
	int diff = graph[a].depth - graph[b].depth;
	for (int i = levels - 1; i >= 0; i--) {
		if (diff & (1 << i)) {
			a = graph[a].ancestor[i];
		}
	}
	
	// this only happens if b is ancestor of a
	if (a == b) {
		return a;
	}
	
	for (int i = levels - 1; i >= 0; i--) {
		// as long as a and b have the same ancestor (beside the lca), we can find a lower ancestor
		if (graph[a].ancestor[i] != graph[b].ancestor[i]) {
			a = graph[a].ancestor[i];
			b = graph[b].ancestor[i];
		}
	}
	return graph[a].ancestor[0];
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	from.resize(n);
	chapter.resize(n);
	to.resize(n);
	graph.resize(n);
	levels = log2(n);
	for (int i = 0 ; i < n; i++) {
		cin >> chapter[i];
		to[i] = i;
	}
	for (int i = 0 ; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		from[a].pb({0, b});
		to[b] = a;
	}
	for (int i = 0 ; i < n; i++) {
		if (to[i] == i) {
			create_tree(i, 0, i, 0);
		}
	}
	int best = 1e9;
	for (int i = 0 ; i < dest.size() - 1; i++) {
		for (int j = i + 1; j < dest.size(); j++) {
			auto p1 = dest[i];
			auto p2 = dest[j];
			if (p1.second == p2.second) {
				best = min(best, graph[p1.first].total + graph[p2.first].total - graph[lca(p1.first, p2.first)].total);
			}
			else {
				best = min(best, graph[p1.first].total + graph[p2.first].total);
			}
		}
	}
	cout << best << "\n";
}


