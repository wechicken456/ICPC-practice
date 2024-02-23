// https://open.kattis.com/problems/divisible

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

ull d, n;
vector<ull>a;
vector<ull>pref;

	
ull divide(int l, int r) {
	if (l == r) {
		return a[l] % d == 0;
	}
	int m = (l + r) / 2;
	map<ull, ull>pref_r;
	for (int i = m + 1; i <= r; i++) {
		pref_r[(pref[i] - pref[m]) % d]++;
	}
	
	ull sum = 0;
	for (int i = l - 1; i < m; i++) {
		int left_half = (pref[m] - pref[i]) % d;
		sum += pref_r[(d - left_half) % d];
	}
	
	sum += divide(l, m) + divide(m + 1, r);
	return sum;
}

void solve() {

	cin >> d >> n;
	a = vector<ull>(n+1);
	pref = vector<ull>(n+1);
	cin >> a[1];
	pref[0] = 0;
	pref[1] = a[1] % d;
	for (int i = 2 ;i  <= n; i++) {
		cin >> a[i];
		pref[i] = pref[i-1] + a[i];
		//pref[i] %= d;
		//cout << pref[i] << " ";
	}
	ull ans = 0;
	ans = divide(1, n);
	cout << ans << "\n";
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


