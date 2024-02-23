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

ll p[1000001];
ll h[1000001];
ll nh[10];
static const ll M = 1e9 + 7;
static const ll B = 31;

void solve() {
	
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	p[0] = 1;
	for (int i = 1 ;i <= 1000000;i++) {
		p[i] = (p[i-1]*B) % M;
	}
	vector<string>v = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	map<string, int>m;
	int cnt = 0;
	for (string &tmp : v) {
		m[tmp] = cnt++;
	}
	map<int , vector<int>>prob;
	prob[0].pb(b);
	prob[1].pb(
	for (int i = 0 ; i < 10 ; i++) {
		nh[i] = 0;
		int l = v[i].length();
		for (int j = 0 ; j < l; j++) {
			nh[i] += v[i][j]*p[j];
			nh[i] %= M;
		}
		cout << nh[i] << "\n";
	}
	
	string s;
	cin >> s;
	ll n = s.length();
	h[0] = 0;
	for (int i = 1 ; i <= n; i++) {
		h[i] = h[i - 1] + (s[i-1]*p[i-1]) % M;
		h[i] %= M;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0 ; j < 10; j++) {
			int l = v[j].length();
			if (i + l - 1 > n) continue;
			
			//cout << i << "-" << j << " " << (h[i + l - 1] - h[i-1]) % M << " " << nh[j]*p[i-1] << "\n";
			
			
			if ( ((h[i + l - 1] - h[i-1]) % M) == (nh[j]*p[i-1]) % M) {
				cout << i << ";" << j << "\n";
			}
		
		}
	}
}


