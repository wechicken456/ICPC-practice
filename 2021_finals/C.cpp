#include<bits/stdc++.h>
#include<cmath>

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

// the key is to recognise the geometric series and that
// if a fraction f, multiplied by n, an int, is an int, and f*m, where m is an int, is also integer.
// then f * gcd(n, m) has to be an integer

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	ull n, m;
	cin >> n >> m;
	double r = pow(m, 1.0/(double)(n-1));
	//cout << setprecision(8) << r << "\n";
	for (double p = 1 ; p <= r; p+=1.0) {
		for (double q = 1; p + q <= r; q+=1.0) {
			ull tmp1[n+1];
			tmp1[0] = 1;
			ull tmp2[n+1];
			tmp2[0] = 1;
			for (int i = 1; i <= n; i++) {
				tmp1[i] = tmp1[i-1]*(ull)(p+q);
				tmp2[i] = tmp2[i-1]*(ull)q;
			}
			if ( (m*(ull)p) % (tmp1[n] - tmp2[n]) == 0) {
				cout << (ull)p << " " << (ull)(p + q) << "\n";
				return 0;
			}
			// in case there is an overflow, we factorise the denominator to cancel out p.
			ull tmp = 0;
			for (int i = 0; i <= n-1; i++) {
				tmp += tmp1[n-1-i]*tmp2[i];
			}
			if (m % tmp == 0) {
				cout << (ull)p << " " << (ull)(p + q) << "\n";
				return 0;
			}
		}
	}
	cout << "impossible\n";
}


