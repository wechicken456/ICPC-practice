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

vector<bool>zeros(200001, false);
vector<bool>twos(200001, false);
vector<bool>visited(200001, false);
vector<bool>has(200001, false);
vector<vector<pair<int, int>>>adj(200001);

ll ans = 0;

void solve(int node, int par) {
	
	if (zeros[node] && twos[node]) {
		cout << "impossible\n";
		exit(0);
	}
	else if (zeros[node] && has[node]) {
		cout << "impossible\n";
		return;
	}
	if (visited[node]) return;
	if (has[node]) {
		ans++;
	}
	visited[node] = true;
	if (twos[node]) has[node] = true;
	if (zeros[node]) {
		for (auto p : adj[node]) {
			if (p.first != par) {
				if (p.second == 2) {
					cout << "impossible\n";
					exit(0);
				}
				else if (p.second == 0) {
					solve(p.first, node);
				}
				else {
					has[p.first] = true;
					solve(p.first, node);
				}
			}
		}
	}
	else if (twos[node]) {
		for (auto p : adj[node]) {
			if (p.first != par) {
				if (p.second == 0) {
					cout << "impossible\n";
					exit(0);
				}
				else if (p.second == 2) {
					solve(p.first, node);
				}
				else {
					has[p.first] = false;
					zeros[p.first] = true;
					solve(p.first, node);
				}
			}
		}
	}
	else {
		
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	for (int i = 0 ; i < m ;i ++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (c == 0) {
			zeros[a] = true;
			zeros[b] = true;
		}
		else if (c == 2) {
			twos[a] = true;
			has[a] = true;
			twos[b] = true;
			has[b] = true;
		}
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}
	for (int i = 0 ; i < n; i++) {
		if (!visited[i]) {
			if (adj[i].size() > 0) {
				solve(i, i);
			}
		}
	}
	cout << ans << "\n";
}


