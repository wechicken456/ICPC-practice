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

int MAX = 2e6 + 1;

vector<ll>prod_factors(MAX, 1);
int num_prime_factors[2000001];

void sieve() {
	for (int i = 2; i <= MAX; i+=2) {
		if (num_prime_factors[i] == 0) {
			for (int u = 2 * i; u <= MAX; u += i) {
				num_prime_factors[u]++;
				ll tmp = u, exp = 0;
				while (tmp % i == 0) {	 // find how many times the prime i divides u
					exp++;
					tmp /= i;
				}
				prod_factors[u] *= (exp+1);
			}
		}
		if (i == 2) i--;
	}
}

int main(){
	
	/*
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	*/
	sieve();
	
	int T;
	scanf("%d", &T);
	while (T--) {
		ll n;
		scanf("%lld", &n);
		if (n <= 2) puts("1");
		else {
			printf("%lld\n", prod_factors[n] - num_prime_factors[n]);
		}
	}
	
	
}


