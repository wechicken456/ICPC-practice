// https://www.youtube.com/watch?v=gQS74eoGegk&list=PLKtOWhDBKQPas91g6eeYNmeixA9ThjxoU&index=9
// https://open.kattis.com/problems/gcdharmony

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

int n, maxN = 5000, maxV = 10000;
vector<vector<ll>>v(1001);
vector<ll>a;
vector<vector<int>>edge;

// primes from 1 to 100
vector<int>primes;

// products of prime factors from 1 to 100 that don't exceed 10000
vector<int>V;
// inv_V[x] = index of x in V
vector<int>inv_V(10001);

// g[x][v]: the minimum total cost to make the subtree at x GCD-harmonic with x.value = v
vector<vector<int>>g(maxN + 1, vector<int>(maxV + 1, 1e7));
// f[c][v]: the minimum total cost to make the subtree at c GCD-harmonic with GCD(c.value, v) > 1
vector<vector<int>>f(maxN + 1, vector<int>(maxV + 1, 1e7));
// h[x][p]: the minimum total cost to make the subtree at x GCD-harmonic with x.value % primes[p] == 0
vector<vector<int>>h(maxN + 1, vector<int>(25, 1e7));

// factors[i] = vector of factors of i
vector<vector<int>>factors(10001);
// multiples[i] = multiples of primes[i]
vector<vector<int>>multiples(25);

void generate_V(vector<int>& subset, int idx, int product) {
	if (idx == subset.size()) {
		if (product <= 10000) {
			factors[product] = subset;
			V.pb(product);
			for (int &i : subset) {
				multiples[i].pb(product);
			}
		}
		return;
	}
	
	int pows = 1;
	for (; product * pows <= 10000; pows *= primes[subset[idx]]) {
		generate_V(subset, idx + 1, product * pows);
	}
}

void solve(int node, int par) {	// dp on tree
	
	for (int &c : edge[node]){
		if (c != par) solve(c, node);
	}
    
	for (int i = 0; i < V.size(); i++) {
		g[node][i] = (V[i] == a[node]) ? 0 : V[i];	
		for (int &c : edge[node]) {                 // recursion
			if (c != par) { 
				g[node][i] += f[c][i]; 	
				// cost of making node = V[i] && gcd(V[i], children's.value) > 1 
			}
        }
        for (int &p : factors[V[i]]) {
			h[node][p] = min(h[node][p], g[node][i]);
			// for each prime p, minimum cost to make subtree at node harmonic with node.value
			// divisible by p
		}
    }
    
    // fast version for f
    for (int p = 0 ; p < 25; p++) {
		for (int &multiple : multiples[p]) {
			int idx = inv_V[multiple];
			//cout << p << " " << multiple << " " << idx << "\n";
			f[node][idx] = min(f[node][idx], h[node][p]);
		}
	}
	
	/* slow version for f
	for (int p = 0 ; p < 25; p++) {
		for (int i = 0; i < V.size(); i++) {
			if (V[i] % primes[p] == 0) {
				f[node][i] = min(f[node][i], h[node][p]);
			}
		}
	}*/
}

int main(){
    
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    for (int i = 2; i <= 100; i++) {
		bool check = true;
		for (int j = 2; j*j <= i; j++) {
			if (i % j == 0) {
				check  = false;
				break;
			}
		}
		if (check) {
			primes.pb(i);
		}
	}
	
	// generate products of prime factors from 1 to 100 that don't exceed 10000
	vector<bool>C(25, false);
	for (int r = 1; r < 6; r++) {	// product of first 6 primes > 10000
		fill(C.begin(), C.end() - r, false);
		fill(C.end() - r, C.end(), true);
		
		do {
			vector<int>subset;
			int product = 1;
			bool check = true;
			for (int i = 0 ; i < 25; i++) {
				if (C[i]) {
					subset.pb(i);
					product *= primes[i];
					if (product > 10000) {
						check = false;
						break;
					}
				}
			}
			if (check) {
				//V.pb(product);
				generate_V(subset, 0, product);
			}
		} while (next_permutation(C.begin(), C.end()));
    }
    sort(V.begin(), V.end());
    for (int i = 0 ; i < V.size(); i++) inv_V[V[i]] = i;
    
    cin >> n;
    a.resize(n);
    edge.resize(n);
    for (int i = 0 ; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0 ; i <   n -1 ; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edge[x].pb(y);
        edge[y].pb(x);
    }
    solve(0, -1);
    int best = 1e7;
    for (int i = 0; i < V.size(); i++) {
        best = min(best, g[0][i]);
    }
    cout << best << "\n";
    
}


