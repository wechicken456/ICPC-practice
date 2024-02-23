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
	vector<int>a(n);
		for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	int sum = 0;
	int cnt = 0;
	for (int i = 0 ; i < n; i++) {
		sum += a[i];
		if (sum > 5 * m) {
			break;
		}
		if (sum <= 5 *m) cnt++;
	}
	cout << cnt << "\n";
}


