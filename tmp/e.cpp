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
	vector<pii>a(n);
	for (int i = 0 ; i < n; i++) {
		cin >> a[i].first >> a[i].second;
		a[i].first--;
		a[i].second--;
	}
	int cnt = 0;
	for (int i = 0 ;i < n - 2; i++) {
		if (a[i + 1].first <= i && a[i + 1].second >= i && a[i].second >= i + 1) {
			if (a[i + 2].first <= i + 1 && a[i + 2].second >= i + 1 && a[i + 1].second >= i + 2) {
				if (a[i + 2].first <= i && a[i + 2].second >= i && a[i].second >= i + 2) {
					i += 2;
					cnt++;
				}
			}
		}	
	}
	cout << cnt << "\n";
}


