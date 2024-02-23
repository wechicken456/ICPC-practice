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

vector<vector<ll>>adj(101);
vector<ll>in_flow(101, 0);
vector<ll>out_flow(101, 0);

void solve() {
	
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	ll n, m , s ,T;
	cin >> n >> m >> s >> T;
	for (int i = 0 ; i < m ; i++) {
		int x, y;
		cin >> x >> y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	
	in_flow[s] = 1;
	for (int  t = 0; t < T; t++) {
		for (int i = 0; i < n; i++) {
			if (in_flow[i] > 0) {
				out_flow[i] = in_flow[i];
				in_flow[i] = 0;
			}
		}
		for (int i = 0 ; i < n; i++) {
			if (out_flow[i] > 0) {
				for (int neighbor : adj[i]) {
					in_flow[neighbor] += out_flow[i];
				}
				out_flow[i] = 0;
			}
		}
	}
	if (T == 0) { 
		cout << 0 << "\n";
		return 0;
	}
	
	ll sum = 0;
	for (int i = 0 ; i < n;i ++) {
		sum += in_flow[i];
	}
	cout << sum << "\n";
}


