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
	int n;
	cin >> n ;
	vector<int>a(n);
	int total = 0;
	for (int i = 0 ;i < n; i++) {
		cin >> a[i];
		total += a[i];
	}
	map<ll, vector<ll>>m;
	for (ll i = 1; i < (1 << n); i++) {
		ll sum = 0;
		for (ll k = 0 ; k < n; k++) {
			if ( (i & (1 << k))) {
				sum += a[k];
			}
		}
		m[sum].pb(i);
	}
	for (auto &p : m) {
		for (int i = 0 ; i < p.second.size(); i++) {
			for (int j = i + 1; j < p.second.size(); j++) {
				if ( (p.second[i] & p.second[j]) == 0) {
					for (int k = 0 ; k < n; k++) {
						if ( (p.second[i] & (1 << k))) {
							cout << a[k] << " ";
						}
					}
					cout << "\n";
					for (int k = 0 ; k < n; k++) {
						if ( (p.second[j] & (1 << k))) {
							cout << a[k] << " ";
						}
					}
					cout << "\n";
					return;
				}
			}
		}
	}
	cout << "Impossible\n";
		/*
		vector<int>v;
		bool check = false;
		for (int j = i + 1; j < (1 << n) ; j++) {
			for (int k = 0 ; k < n; k++) {
				if ( (i & (1 <<k)) == (j & (1 << k)) && ( (j & (1 << k)) == 1)) {
					check = true;
					break;
				}
			}
			if (check) {
				break;
			}
			int sum = 0;
			for (int k = 0 ; k < n; k++) {
				if (i & (1 << k)) {
					sum += a[k];
					v.pb(a[k]);
				}
			}
			if (sum == total - sum) {
				for (int &x : v) {
					cout << x << " ";
				}
				cout << "\n";
				return;
			}
		}*/
	
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		cout << "Case #" << i << ":\n";
		solve();
	}
	
	
}


