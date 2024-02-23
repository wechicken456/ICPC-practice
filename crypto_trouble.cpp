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
ll pows[200001];
vector<ll>cnt(3, 0);
ll zero = 0;

void calc(ll n) {
	pows[0] = 1;
	for (int i = 1; i <= n ;i++) {
		pows[i] = pows[i-1] * 2;
		pows[i] %= MOD;
	}
}

ll powmod(ll a, ll b){
    a %= MOD;
    if (a == 0) return 0;
    ll product = 1;
    while(b > 0){
        if (b&1){    // you can also use b % 2 == 1
            product *= a;
            product %= MOD;
            --b;
        }
        a *= a;
        a %= MOD;
        b /= 2;    // you can also use b >> 1
    }
    return product;
}



int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;
	string s;
	cin >> s;
	
	calc(n);
	for (int i = 0 ; i < n; i++) {
		
		ll x = s[i] - '0';
		cnt[x % 3]++;
		if (x == 0) {
			zero++;
		}
	}
	
	// calculate combinations for nCr, where n = number of ones, number of twos
	vector<vector<ll>>comb(2);
	for (int i = 0 ; i < 2; i++) { 
		ll N = cnt[i + 1];
		comb[i].resize(N + 1);
		comb[i][0] = 1;
		comb[i][N] = 1;
		for (int j = 1; j <= N / 2; j++) {
			comb[i][j] = comb[i][j - 1]*(N - j + 1);
			comb[i][j] %= MOD;
			comb[i][j] *= powmod(j, MOD - 2);
			comb[i][j] %= MOD;
			comb[i][N-j] = comb[i][j];
		}
	}
	
	vector<vector<ll>>sum(2, vector<ll>(3, 0));
	
	for (int i = 0 ; i < 2; i++) {
		for (int j = 0; j <= cnt[i + 1]; j++) { 
			sum[i][ ((i+1)*j) % 3] += comb[i][j];
			sum[i][ ((i+1)*j) % 3] %= MOD;
		}
	}
	
	
	ll ans = pows[cnt[0]];
	ll tmp = ( (sum[0][0]*sum[1][0]) % MOD + (sum[0][1]*sum[1][2]) % MOD + (sum[0][2]*sum[1][1]) % MOD) % MOD;
	ans *= tmp;
	ans %= MOD;
	//cout << ans << "\n";
	ans = ans + MOD - pows[zero];
	ans %= MOD;
	cout << ans << "\n";
}


