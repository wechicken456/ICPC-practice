#include<bits/stdc++.h>
#include<algorithm>

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
vector<vector<pair<ll, int>>>adj(200001);
vector<vector<ll>>dist(9, vector<ll>(200001, 1e16));
map<int, int>mm;

void solve(int start) {
	vector<bool>visited(200001, false);
	dist[mm[start]][start] = 0;
	priority_queue<pair<ll, int>>pq;
	pq.push({0, start});
	while (!pq.empty()) {
		ll d = abs(pq.top().first);
		int node = pq.top().second;
		pq.pop();
		
		if (visited[node]) continue;
		visited[node] = true;
		for (auto &p : adj[node]) {
			ll w = p.first;
			int nxt = p.second;
			if (d + w < dist[mm[start]][nxt]) {
				dist[mm[start]][nxt] = d + w;
				pq.push({-dist[mm[start]][nxt], nxt});
			}
		}
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	for (int i = 0 ; i  < m ; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		adj[a].pb({c, b});
		adj[b].pb({c, a});
	}
	
	mm[1] = 0;
	solve(1);
	
	set<int>s;
	int cnt = 1;
	for (int i = 0 ; i < 7 ;i++) {
		int x;
		cin >> x;
		if (mm[x] == 0) {
			mm[x] = cnt;
			cnt++;
		}
		s.insert(x);
	}
	vector<int>v;
	for (int x : s){ 
		solve(x);
		v.pb(x);
	}
	ll ans = 1e18;
	do {
		ll sum = dist[0][v[0]];
		for (int i = 1 ; i < v.size(); i++) {
			sum += dist[ mm[v[i-1]] ][v[i]];
		}
		ans = min(ans, sum);
	} while(next_permutation(v.begin(), v.end()));
	cout << ans << "\n";
}


