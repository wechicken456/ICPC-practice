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
static const ll M = 2305843009213693951;
static const ll B = 9973;
ll p[1000001];
/*
ll calc_pref(string &s) {
	ull h = 0;
	for (int i = 0 ;i < s.length(); i++) {
		h += s[i]*p[s.legnth() - i - 1];
		h %= M;
	}
	return h % M;
}*/


int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	p[0] = 1;
	for (int i = 1 ;i <= 1000000;i++) {
		p[i] = (p[i-1]*B) % M;
	}
	
	int n, q;
	cin >> n >> q;
	map<ll, int>pref;
	map<ll, int>suff;
	map<pair<ll, ll>, int>both;
	for (int i = 0; i < n ;i++) {
		string s;
		cin >> s;
		ull h = 0;
		ull sh = 0;
		for (int k = 0 ;k < s.length(); k++) {
			h += s[k]*p[k];
			h %= M;
			pref[h]++;
			
			sh += s[s.length() - k - 1]*p[k];
			sh %= M;
			suff[sh]++;
			
			//cout << h << " " << sh << "\n";
			both[{h, sh}]++;
		}
	}
	for (int i = 0; i < q; i++) {
		string a, b , c;
		cin >> a >> b >> c;
		ull h = 0;
		ull sh = 0;
		for (int k = 0 ;k < b.length(); k++) {
			h += b[k]*p[k];
			h %= M;
			
			sh += c[c.length() - k - 1]*p[k];
			sh %= M;
		}
		//cout << h << "-" << sh << "\n";
		//cout << pref[h] << " " << suff[sh] << ";" << both[{h, sh}] << "\n";
		if (a == "AND") {
			cout << both[{h, sh}] << "\n";
		}
		else if (a == "OR") {
			cout << pref[h] + suff[sh] - both[{h, sh}]  << "\n";
		}
		else {
			cout << pref[h] + suff[sh] - 2*both[{h, sh}]  << "\n";
		}
	}
}


