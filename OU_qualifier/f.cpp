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
ll prod = 1;
ll a, b , c;

ull exponent(ull base, ull exp) {
	if (exp == 0) {
		return 1;
	}
	if (base > c) {
		cout << "Oh look, a squirrel!\n";
		exit(0);
	}
	if (exp % 2 == 1) {
		ull res = exponent(base * base, exp / 2) * base;
		if (res > c) {
			cout << "Oh look, a squirrel!\n";
			exit(0);
		}
		return res;
	}
	else {
		ull res = exponent(base * base, exp / 2);
		if (res > c) {
			cout << "Oh look, a squirrel!\n";
			exit(0);
		}
		return res;
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	

	cin >> a >> b >> c;
	if (a == 1) {
		cout << "What an excellent example!\n";
		return 0;
	}
	ull res = exponent(b, c - 1);
	if (res == c) {
		cout << "What an excellent example!\n";
	}
	else {
		cout << "Oh look, a squirrel!\n";
	}
	return 0;
}


