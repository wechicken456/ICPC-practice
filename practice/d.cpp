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
	
	ll a,b,c,d,total = 0;
	cin >> a >> b >> c >> d;
	
	total += c * d;
	
	if ( c > 0) {
		total += b;
		b = 0;
	}
	
	if ( d > 0) {
		total += a;
		a = 0;
	}
	
	total += min(a,b);
	
	cout << total << '\n';
	
}


