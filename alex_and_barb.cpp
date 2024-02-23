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
	
	
	int k, m ,n;
	cin >> k >> m >> n;
	if (k < m) {
		cout << "Barb\n";
		return 0;
	}
	int tmp = k % (n + m);
	if (tmp >= m) {
		cout << "Alex\n";
	}
	else {
		cout << "Barb\n";
	}
}


