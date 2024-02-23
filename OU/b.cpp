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

struct comp {
	bool operator() (const pii &p1, const pii &p2)  {
		if (p1.first < p2.first) return true;
		else if (p1.first == p2.first) return p1.second < p2.second;
		else return false;
	}
};

void solve() {
	int m, P;
	cin >> m >> P;
	vector<pii>a(m);
	map<int , vector<int>>mm;
	vector<int> weekends(101, 0);
	for (int i = 6; i <= 100; i+=7) weekends[i] = 2;
	for (int i = 7; i <= 100; i+=7) weekends[i] = 1;
	for (int i= 0 ;i < m; i++) {
		cin >> a[i].first >> a[i].second;
		mm[a[i].first].pb(a[i].second);
	}
	sort(a.begin(), a.end(), comp());
	/*for (int i= 0 ;i < m; i++) {
		cout << a[i].first << " " << a[i].second << "\n";
	}*/
	int cnt = 0;
	int w = 0;
	int last_w = 0;
	for (auto &p : mm) {
		sort(p.second.begin(), p.second.end());
		if (weekends[p.first] > 0) {
			int tmp_P = P;
			for (int i = 0; i < p.second.size(); i++) {
				if (p.first + weekends[p.first] < p.second[i]) {
					mm[p.first + weekends[p.first]].pb(p.second[i]);
					last_w++;
				}
				else {
					if (tmp_P - 2 < 0) {
						cout << "serious trouble\n";
						return;
					}
					tmp_P -= 2;
				}
			}
		}
		else {
			int need = p.second.size() * 2;
			if (need > P) {
				cnt += P / 2;
				for (int i = P / 2; i < p.second.size(); i++) {
					if (p.first + 1 < p.second[i]) {
						mm[p.first + 1].pb(p.second[i]);
					}
					else {
						w++;
					}
				}
			}
			else {
				cnt += p.second.size();
			}
		}
	}
	if (w == 0) cout << "fine";
	else if (w >= 2) cout << "
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	
	
}


