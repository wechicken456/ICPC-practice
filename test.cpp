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

const ll MOD = 1e9 + 7;

ll f (vector<ll>&A, ll k, ll i, ll r = 0) {
  // A[i] leaves remainder r
  // when divided by k
  const ll c = A[i] % k == r ? 1 : 0;

  if (i == 0)
    return c;
  
  return (c  % MOD) +  
    // All previous subsequences 
    // who's sum leaves remainder r
    // when divided by k
    ( f(A, k, i - 1, r) % MOD )+

    // All previous subsequences who's
    // sum when combined with A[i]
    // leaves remainder r when
    // divided by k
    ( f(A, k, i - 1, (k + r - A[i]%k) % k) % MOD ) % MOD;
}

ll pows[200001];

void calc(ll n) {
	pows[0] = 1;
	for (int i = 1; i <= n ;i++) {
		pows[i] = pows[i-1] * 2;
		pows[i] %= MOD;
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;
	vector<ll>a(n);
	string s;
	cin >> s;
	ll zero = 0;
	for (int i = 0 ; i < n; i++) {
		a[i] = s[i] - '0';
		if (a[i] == 0) zero++;
	}
	cout << f(a, 3, n - 1) - (pows[zero]	 - 1) << "\n";
}


