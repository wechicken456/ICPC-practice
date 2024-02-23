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
	
	ll a, b, c, d, e ,f , g;
	cin >> a >> b >> c >> d >> e >> f >> g;
	
	if (a > b) swap(a, b);
	
	set<ll, greater<ll>>s;
	for (int i = 1; 2*i < a; i++) {
		ll _size = i * (a - 2*i) * (b-2*i);
		s.insert(_size);
	}
	//for (const ll &x : s) cout << x << "\n";
	
	// c + s[0]*x = d + s[1]*y = e + s[2]*z
	// x , y , z MUST be integers
	auto tmp = s.begin();
	ll m1, m2, m3;
	m1 = *tmp;
	tmp++;
	m2 = *tmp;
	tmp++;
	m3 = *tmp;
	tmp++;
	ll cnt = 0;
	while (m1 * cnt + c <= g) {
		if (m1 * cnt + c >= f) {
			if ( (m1 * cnt + c - d) % m2 == 0) {
				if ( (m1 * cnt + c - e) % m3 == 0) {
					cout << m1 * cnt + c << "\n";
					return 0;
				}
			}
		}
		cnt++;
	}
}


