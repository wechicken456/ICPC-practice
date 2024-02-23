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

struct cmp{
	bool operator()(const pii &p1, const pii &p2)const {
		if (p1.first < p2.first) return true;
		if (p1.first == p2.first) return p1.first < p2.first;
		else return false;
	}
};

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, k, rmax;
	cin >> n >> k >> rmax;
	vector<pii>a(n);
	map<int, int>mx;
	map<int, int>my;
	vector<int>ax(n);
	vector<int>ay(n);
	vector<vector<bool>>istree(5000, vector<bool>(5000, false));
	for (int i = 0 ; i < n; i++) {
		cin >> a[i].first >> a[i].second;
		ax[i] = a[i].first;
		ay[i] = a[i].second;
	}
	sort(ax.begin(), ax.end());
	sort(ay.begin(), ay.end());
	for (int i = 0 ; i < n; i++) {
		mx[ax[i]] = i + 1;
		my[ay[i]] = i + 1;
	}
	/*
	for (int i = 0 ; i < n ;i++) {
		istree[ mx[a[i].first] ][ my[a[i].second] ] = true;
	}
	*/
	vector<vector<set<pii, cmp>>>v(4, vector<set<pii, cmp>>(1000));
	for (int i = 0 ; i < k ; i++) {
		int x , y;
		cin >> x >> y;
		for (int j = 0 ; j < n; j++) {
			pii p = a[j];
			if (mx[p.first - x] == 0 || my[p.second - y] == 0)
				v[0][i].insert({p.first - x, p.second - y});	// face up
			if (mx[p.first - y] == 0 || my[p.second + x] == 0)
				v[1][i].insert({p.first - y, p.second + x});	// face right
			if (mx[p.first + x] == 0 || my[p.second + y] == 0)
				v[2][i].insert({p.first + x, p.second + y}); 	// face down
			if (mx[p.first + y] == 0 || my[p.second - x] == 0)
				v[3][i].insert({p.first + y, p.second - x});	// face left
		}
	}
	vector<pii>ans;
	for (int i = 0 ; i < 4; i++) {
		for (auto p : v[i][0]) {
			int cnt = 1;
			for (int j = 1 ; j < k; j++) {
				if (v[i][j].find(p) != v[i][j].end()) cnt++;
				else break;
			}
			if (cnt == k) {
				ans.pb(p);
				if (ans.size() > 1) {
					cout << "Ambiguous\n";
					return 0;
				}
			}
		}
	}
	if (ans.size() == 0) {
		cout << "Impossible\n";
	}
	else if (ans.size() == 1) {
		cout << ans[0].first << " " << ans[0].second << "\n";
	}
	/*
	for (int i = 0 ; i < n; i++) {
		for (int j = 0 ; j < 4; j++) {
			sort(v[i][j].begin(), v[i][j].end(), cmp);
		}
	}
	for (int j = 0 ; j < 4; j++) {
		for (int i = 0 ; i < n; i++) {
			pii cur =
		}
	}
	*/
	/*
	unordered_map<int, unordered_map<int, unordered_map<int, set<int>> > >m;
	for (int i = 0; i < k ; i++) {
		int x, y;
		cin >> x >> y;
		for (int j = 0 ; j < n; j++) {
			pii p = a[j];
			if (!istree[p.first - x][p.second - y])
				m[p.first - x][p.second - y][0].insert(i);	// face up
			if (!istree[p.first - y][p.second + x])
				m[p.first - y][p.second + x][1].insert(i);	// face right
			if (!istree[p.first + x][p.second + y])
				m[p.first + x][p.second + y][2].insert(i); 	// face down
			if (!istree[p.first + y][p.second - x])
				m[p.first + y][p.second - x][3].insert(i);	// face left
		}
	}
	vector<pii>ans;
	for (auto tmp1 : m) {
		for (auto tmp2 : tmp1.second) {
			auto cnt = tmp2.second;
			for (int i = 0 ; i < 4; i ++) {
				if (cnt[i].size() == k) ans.pb({tmp1.first, tmp2.first});
				if (ans.size() > 1) {
						cout << "Ambiguous\n";
						return 0;
				}
			}
		}
	}
	if (ans.size() == 0) {
		cout << "Impossible\n";
	}
	else if (ans.size() == 1) {
		cout << ans[0].first << " " << ans[0].second << "\n";
	}
	*/
}


