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
	
	string s;
	ull n;
	cin >> s >> n;
	
	string whole = "";
	string decimal = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') {
			decimal = s.substr(i + 1, s.length());
			break;
		}
		else {
			whole.pb(s[i]);
		}
	}
	
	ull len_dec = decimal.length();
	ull w = stoll(whole);
	ull d = stoll(decimal);	// the decimal part before the repeating part
	ull rep = 0;
	
	if (d - (ull)pow(10, n) < 0) {		// all leading zeros until the repeating part
		rep = d;
		d = 0;
	}
	else {
		ll pow_10 = 1;
		for (int i = 0 ; i < n ;i++) {
			rep += pow_10 * (d % 10);
			d /= 10;
			pow_10 *= 10;
		}
	}
	
	ll offset_to_rep = len_dec - n;
	
	// (10**n)*0.X - 0.X = X. (where X is the repeating digits)
	ull deno_rep = (ull)pow(10, n) - 1;
	ull numer_rep = rep;
	deno_rep *= (ull)pow(10, offset_to_rep);
	
	ull gcd_rep = __gcd(deno_rep, numer_rep);
	

	if (gcd_rep == 0) gcd_rep = 1;
	deno_rep /= gcd_rep;
	numer_rep /= gcd_rep;
	
	ull deno_d;
	if (d != 0) {
		deno_d = (ull)pow(10, offset_to_rep);
		ull gcd_d = __gcd(deno_d, d);
		
		deno_d /= gcd_d;
		d /= gcd_d;
	}
	else {
		deno_d = 1;
	}
	
	//cout << d << " " << deno_d << " " << numer_rep << " " << deno_rep << "\n";
	
	ull common_deno = deno_d * deno_rep;
	
	ull sum_numer = 0;
	sum_numer += w * deno_d * deno_rep;
	sum_numer += d * deno_rep;
	sum_numer += numer_rep * deno_d;
	
	
	ull gcd_ans = __gcd(common_deno, sum_numer);
	//cout << gcd_ans << "\n";
	
	cout << (ull)(sum_numer / gcd_ans) << "/" << (ull)(common_deno / gcd_ans) << "\n";
}


