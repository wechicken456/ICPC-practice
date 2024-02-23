// https://open.kattis.com/problems/najkraci
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

#define SET(v, len, val) for (int i = 0 ; i < len; i++) v[i] = val;

using namespace std;

int n , m;
vector<ll>dist;
vector<vector<pair<int, pair<ll, int>>>>adj;
vector<ll>ans;
ll MOD = 1'000'000'007;
vector<ll>cntTo;
vector<ll>cntFrom;

void dijkstra(int start) {
	dist[start] = 0;
	cntTo[start] = 1;
	priority_queue<pair<ll, pair<int, ll>>>pq;
	pq.push({0, {start, 1}});
	while (!pq.empty()) {
		int node = pq.top().second.first;
		ll ways = pq.top().second.second;	// represents the number of ways to reach current node at the time it was pushed, NOT the ACCUMULATIVE/TOTAL ways.
		ll d = abs(pq.top().first);
		pq.pop();
		// second condition is always satisfied after the 1st vis it because we added the number of ways before we pushed
		if (d > dist[node] || ways < cntTo[node]) {
			continue;
		}
		
		for (auto &p : adj[node]) {
			ll w = p.second.first, nxt = p.first;
			if (d + w < dist[nxt]) {
				dist[nxt] = d + w;
				cntTo[nxt] = cntTo[node];	// num of ways to reach nxt node = num of ways to reach current node
				pq.push({-dist[nxt], {nxt, cntTo[nxt]}});
			}
			else if (d + w == dist[nxt]) {
				cntTo[nxt] += cntTo[node];	// // num of ways to reach nxt node += num of ways to reach current node
				pq.push({-dist[nxt], {nxt, cntTo[nxt]}}); 
				// push cntTo[nxt] and not ways because cntTo[nxt] = sum of all ways, 
				//if we push `ways`, the if condition above will pass and we will never process the pushed node.
			}
		}
	}
}

ll dp(int node) {
	
	// this meets when we have already visited this node
	if (cntFrom[node] != 0) return cntFrom[node];
	ll ways = 1;
	
	for (auto &p : adj[node]) {
		ll w = p.second.first, nxt = p.first;
		if (w + dist[node] == dist[nxt]) { 		// # of shortest paths from this node = sum of # of shortest paths from its incident neighbors
			ways += dp(nxt);
		}
	}
	return cntFrom[node] = ways;
}

void solve(int start) {
	SET(dist, n, (ll)1e9);
	SET(cntTo, n, 0);
	SET(cntFrom, n, 0);
	
	dijkstra(start);
	/*
	for (int i = 0 ; i < n; i++) {
		cout << cntTo[i] << " " ;
	}
	cout << "\n";
	*/
	dp(start);
	/*
	for (int i = 0 ; i < n; i++) {
		cout << cntFrom[i] << " " ;
	}
	cout << "\n";
	*/
	for (int i = 0 ; i < n ;i++) {
		if (cntFrom[i] != 0){
			for (auto &p : adj[i]) {
				int id = p.second.second, nxt = p.first;
				ll w = p.second.first;
				if (dist[i] + w == dist[nxt]) {
					ans[id] += cntTo[i]*cntFrom[nxt];
					ans[id] %= MOD;
				}
			}
		}
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	adj = vector<vector<pair<int, pair<ll, int>>>>(n);
	ans = vector<ll>(m, 0);
	dist = vector<ll>(n, 0);
	cntTo = vector<ll>(n, 0);
	cntFrom = vector<ll>(n, 0);
	for (int i = 0 ; i < m ; i++) {
		ll a, b , c;
		cin >> a >> b >> c;
		a--; b--;
		adj[a].pb({b, {c, i}});
	}
	
	for (int i = 0 ;i < n; i++) {
		solve(i);
	}
	for (int i = 0 ; i< m; i++) {
		cout << ans[i] << "\n";
	}
}


