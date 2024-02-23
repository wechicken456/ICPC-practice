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
	
	
	int n, m;
	cin >> n >> m;
	vector<int>a(m);
	vector<int>ans(m, 0);
	for (int i = 0 ; i < m ; i++) cin >> a[i];
	while (n > 0) {
		int cnt = 0;
		for (int i = 0 ; i < m; i++) {
			if (a[i] > 0) {
				a[i]--;
				ans[i]++;
				n--;
				cnt++;
			}
			if (n == 0) break;
		}
		if (cnt == 0) break;
	}
	for (int i = 0 ; i < m; i++) {
		cout << ans[i] << "\n";
	}
}


