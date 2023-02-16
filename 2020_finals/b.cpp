// https://open.kattis.com/problems/speedlimit2

#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define pii pair<unsigned int, unsigned int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define vb vector<bool>

using namespace std;

vector<vector<pair<unsigned int, unsigned int>>>edge;
vector<unsigned int>dist;
unsigned int n, c;

struct Node {
	unsigned int best = (unsigned int)4e9;
	vector<unsigned int>dp;
	unsigned int max_weight = 0;
	unsigned int put_sign = 0;
};

vector<Node>graph;

void solve(unsigned int node, unsigned int parent) {	
	for (auto &p : edge[node]) {
		if (p.second != parent) {
			solve(p.second, node);
		}
	}
	
	int s = dist.end() - lower_bound(dist.begin(), dist.end(), graph[node].max_weight);
	graph[node].dp.resize(s);
	
	
	for (unsigned int i = 0 ; i < s; i++) {
		int pos_in_dist = i + dist.size() - s;
		for (auto &p : edge[node]) {
			
			
			unsigned int weight_diff = dist[pos_in_dist] - p.first;
			graph[node].dp[i] += weight_diff;
			
			if (p.second != parent) {
				if (graph[p.second].max_weight > dist[pos_in_dist]) {
					graph[node].dp[i] += graph[p.second].put_sign;
					continue;
				}
				
				int pos_diff = graph[p.second].dp.size() - s;
				int pos_in_child = i + pos_diff;
				if (graph[p.second].dp[pos_in_child] - weight_diff <= graph[p.second].put_sign) {
					graph[node].dp[i] += graph[p.second].dp[pos_in_child] - weight_diff;
				}
				else {
					graph[node].dp[i] += graph[p.second].put_sign;
				}
			}
		}
		graph[node].best = min(graph[node].best, graph[node].dp[i]);
	}
	
	if (edge[node].size() > 1) {
		graph[node].put_sign = c*edge[node].size();
		for (auto &p : edge[node]) if (p.second != parent) graph[node].put_sign += graph[p.second].best;
		graph[node].best = min(graph[node].put_sign, graph[node].best);
	}
	//cout << node << " " << graph[node].best << "\n";
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> c;
	edge = vector<vector<pair<unsigned int, unsigned int>>>(n);
	graph = vector<Node>(n);
	set<unsigned int>st;
	for (unsigned int i = 0 ; i < n - 1; i++) {
		unsigned int u, v, s;
		cin >> u >> v >> s;
		u--;v--;
		edge[u].pb({s, v});
		graph[u].max_weight = max(graph[u].max_weight, s);
		edge[v].pb({s, u});
		graph[v].max_weight = max(graph[v].max_weight, s);
		st.insert(s);
	}
	if (n == 1) {
		cout << "0\n";
		return 0;
		
	}
	dist = vector<unsigned int>(st.size());
	int cnt = 0;
	for (auto it = st.begin(); it != st.end(); it++, cnt++) {
		dist[cnt] = *it;
	}
	st.clear();
	solve(0, 0);
	cout << graph[0].best << "\n";
}


