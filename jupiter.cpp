// https://open.kattis.com/problems/jupiter
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
	
	int n, q , s;
	int sum = 0;
	cin >> n >> q >> s;
	vector<int>qs(s);
	vector<int>qsize(q);
	for (int i = 0 ; i < s; i++) cin >> qs[i];
	for (int i = 0 ; i < q; i++) {
		cin >> qsize[i];
		sum += qsize[i];
	}
	
	int cap = 0;
	vector<vector<int>>query(n, vector<int>(s+1));
	for (int i = 0 ; i < n; i++) {
		for (int j = 0 ; j < s + 1; j++) {
			cin >> query[i][j];
			if (j > 0 && query[i][j] > qsize[qs[j]]) {
				cout << "impossible\n";
				return 0;
			}
		}
		cap += query[i][0];
	}
	if (sum > cap) {
		cout << "impossible\n";
		return 0;
	}
	vector<int>rem(q + 1, 0);
	vector<int>predict(q + 1, 0);
	for (int i = 0 ; i < n; i++) {
		for (int j = 1; j < q + 1; j++) {
			predict[j] = rem[j];
		}
		cap = query[i][0];
		/*
		for (int j = 1; j <= s; j++) {
			rem[qs[j]] += query[i][j];
			if (rem[qs[j]] > qsize[qs[i]]) {
				cout << "impossible\n";
				return 0;
			}
		}*/
		A:;
		while (cap > 0) {
			for (int j = i + 1; j < n; j++) {
				for (int k = 0; k < s; k++) {
					predict[qs[k]] += query[j][k];
					if (predict[qs[k]] > qsize[qs[k]]) {
						int diff = min(predict[qs[k]] - qsize[qs[k]], cap);
						predict[qs[k]] -= diff;
						cap -= diff;
						if (cap == 0) {
							'
							goto A;
						}
					}
				}
			}
		}
	}
}


