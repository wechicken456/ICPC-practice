// https://open.kattis.com/problems/slowleak
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

vector<int>station;
ll n, m , t , d;
vector<vector<pair<ll ,int>>>edge;	
ull ans = 0;

vector<vector<pair<ll, int>>>new_edge;
vector<vector<ll>>shortest;
vector<bool>is_station;


void solve(int start) {
	priority_queue<pair<ll, int>>pq;
	vector<bool>visited(n , false);
	shortest[start][start] = 0;
	pq.push({0, start});
	while (pq.size()) {
		ll dist = abs(pq.top().first), node = pq.top().second;
		pq.pop();
		if (visited[node]) continue;
		
		visited[node] = true;
		if (node != start && is_station[node]) {
			new_edge[start].pb({dist, node});
			continue;
		}
		for (auto &p : edge[node]) {
			if (dist + p.first <= d) {
				if (dist + p.first < shortest[start][p.second]) {
					shortest[start][p.second] = dist + p.first;
					pq.push({-(ll)shortest[start][p.second], p.second});
				}
			}
		}
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	cin >> n >> m >> t >> d;
	station = vector<int>(t);
	is_station =vector<bool>(n, false);
	is_station[n-1] = true;
	is_station[0] = true;
	edge = vector<vector<pair<ll, int>>>(n);
	//visited = vector<bool>(n ,false);
	new_edge = vector<vector<pair<ll, int>>>(n);
	shortest = vector<vector<ll>>(n, vector<ll>(n, (ll)1e17));
	
	for (int i = 0; i < t; i++) {
		cin >> station[i];
		station[i]--;
		is_station[station[i]] = true;
	}
	for (int i = 0 ;i < m; i++) {
		ll a ,b, x;
		cin >> a >> b >> x;
		a--;
		b--;
		edge[a].pb({x, b});
		edge[b].pb({x, a});
	}
	solve(0);
	for (int i = 0 ; i < t ;i++) {
		solve(station[i]);
	}
	
	
	
	priority_queue<pair<ll, int>>pq;
	vector<bool>visited(n + 2, false);
	shortest[0][0] = 0;
	pq.push({0, 0});
	for (int i = 1 ; i < n; i++) shortest[0][i] = (ll)1e17;
	while (pq.size()) {
		ll dist = abs(pq.top().first), node = pq.top().second;
			
		pq.pop();
		if (visited[node]) continue;
		
		visited[node] = true;
	
		for (auto &p : new_edge[node]) {
			if (dist + p.first < shortest[0][p.second]) {
				shortest[0][p.second] = dist + p.first;
				pq.push({-(ll)shortest[0][p.second], p.second});
			}
		}
	}
	if (shortest[0][n-1] != (ll)1e17) {
		cout << shortest[0][n-1] << "\n";
		
	}
	else {
		cout << "stuck\n";
	}
	return 0;
}


