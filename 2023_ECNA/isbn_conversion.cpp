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
	string s;
	cin >> s;
	int n = s.length();
	if (s[0] == '-' || s[n - 1] == '-') {
		cout << "invalid\n";
		return;
	}
	int cnt = 0;
	for (int i = 1 ; i < n - 1;  i++) {
		if (s[i] == '-' && s[i + 1] == '-') {
			cout << "invalid\n";
			return;
		}
		if (s[i] == '-') cnt++;
	}
	if (cnt > 3) {
		cout << "invalid\n";
		return;
	}
	if (cnt == 3 && s[n-2] != '-') {
		cout << "invalid\n";
		return;
	}
	if (n - cnt != 10) {
		cout << "invalid\n";
		return;
	} 
	int sum = 0;
	int tmp = 10;
	for (int i = 0 ; i < n; i++) {
		if (s[i] != '-') {
			if (s[i] == 'X') {
				if (i != n-1) {
					cout << "invalid\n";
					return;
				}
				sum += 10;
			}
			else {
				sum += tmp * (s[i] - '0');
				tmp--;
			}
		}
	}
	if (sum % 11 != 0) {
		cout << "invalid\n";
		return;
	}
	
	string ans = "978-" + s.substr(0, n - 1);
	n = ans.size();
	sum = 0;
	cnt = 0;
	for (int i = 0 ; i < n; i++) {
		if (ans[i] != '-') {
			if (cnt % 2 == 0) {
				sum += ans[i] - '0';
			}
			else {
				sum += 3*(ans[i] - '0');
			}
			cnt++;
		}
	}
	//cout << sum << "\n";
	for (int i = 0 ; i < 10; i++) {
		if ( (sum + i) % 10 == 0) {
			cout << ans << i << "\n";
			return;
		}
	}
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


