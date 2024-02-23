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
	
	
	ll n, k , p;
	cin >>n >>k >> p;
	vector<ll>f;
	for (ll i = 1; i*i <= n; i++) {
		if (i > k) break;
		if (n % i == 0)	{
			if (n / i <= p) f.pb(i);
			if (n / i != i) {
				if (n / i <= k) {
					if ((n / (n / i)) <= p )f.pb(n / i);
				}
			}
		}
	}
	sort(f.begin(), f.end());
	cout << f.size()<< "\n";
	for (ll &x : f) cout << x << "\n";
}


