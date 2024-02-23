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
	
	
	int n;
	cin >> n;
	vector<int>a(n);
	vector<int>mi(n + 1, 1e9);
	vector<int>ma(n + 1, 0);
	for (int i= 0 ;  i < n ;i++) {
		cin >> a[i];
	}
	if (n == 1) {
		cout << "1 " << a[0] << "\n";
		return 0;
	}
	for (int i = 1; i < n; i++) {
		ma[i] = max(a[i-1], ma[i-1]);
	}
	for (int i = n - 2; i >= 0; i--) {
		mi[i] = min(a[i + 1], mi[i + 1]);
	}
	vector<int>ans;
	for (int i = 0 ; i < n; i++) {
		if (ma[i] <= a[i] && mi[i] > a[i]) {
			ans.pb(a[i]);
		}
	}
	cout << ans.size() << " ";
	for (int i = 0 ; i <  min((int)ans.size(), 100); i++) {
		if (i == ans.size() - 1) {
			cout << ans[i];
		}
		else cout << ans[i] << " " ;
	}
	cout << "\n";
}


