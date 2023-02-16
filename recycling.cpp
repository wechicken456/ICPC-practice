// https://open.kattis.com/problems/recycling

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

vector<ll>a;
map<ll, vector<int>>m;
int n;
vector<ll>w;
ll ans = 0;
int ans_left = 0;
int ans_right = 0;

void solve(int l , int r, int val_idx) {
	//cout << l << " " << r <<  " " << val_idx << "\n";
	ll cur_val = w[val_idx];
	
	if (ans < cur_val * (r - l  + 1)) {
		ans = cur_val * ( r - l + 1);
		ans_left = l;
		ans_right = r;
	}
	else if (ans == cur_val * (r - l + 1)) { 
		if (l < ans_left) {
			ans_left=  l;
			ans_right = r;
		}
	}
	if (l == r) {
		return;
	}
	
	vector<int>&v = m[cur_val];
	int idx = lower_bound(v.begin(), v.end(), l) - v.begin();
	if (idx == v.size() || v[idx] > r) {
		solve(l, r, val_idx+1);
		return;
	}
	
	if (v[idx] - l >= 1) {
		solve(l, v[idx] - 1, val_idx + 1);
	}
	idx++;
	
	for (; idx < v.size() && v[idx] <= r; idx++) {
		if (v[idx] - v[idx - 1] > 1) {
			solve(v[idx-1] + 1, v[idx] - 1, val_idx+1);
		}
	}
	
	idx--;
	
	if (r - v[idx] >= 1) {
		solve(v[idx] + 1, r, val_idx+1);
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n;
	a = vector<ll>(n);
	set<ll>st;
	for (int i = 0 ; i < n; i++) {
		cin >> a[i];
		m[a[i]].pb(i);
		//st.insert(a[i]);
	}
	
	for (auto &p : m) {
		w.pb(p.first);
	}
	
	solve(0, n - 1, 0) ;
	cout << ans_left + 1 << " " << ans_right + 1 << " " << ans << "\n";
}


