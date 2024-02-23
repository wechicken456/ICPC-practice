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

void solve() {
	
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, k , c;
	cin >> n >> k >> c;
	vector<pll>a(n + 1);
	vector<vector<pll>>school(n + 1);
	for (int i = 1 ; i <= n; i++) {
		cin >> a[i].first >> a[i].second;
	}
	int cnt = 0 ;
	vector<bool>taken(n + 1, false);
	vector<pll>ans;
	for (int i = 1 ; i <= n; i++) {
		if (cnt >= k) {
			break;
		}
		if (school[a[i].second].size() < c) {
			school[a[i].second].pb({i, a[i].first});
			ans.pb({i, a[i].first});
			taken[i] = true;
			cnt++;
		}
	}
	if (cnt < k) {
		for (int i = 1; i <= n; i++) {
			if (cnt == k) break;
			if (!taken[i]) {
				ans.pb({i, a[i].first});
			}
		}
	}
	sort(ans.begin(), ans.end());
	for (auto &p : ans) cout << p.second << "\n";
}


