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
	
	int sum = 0;
	for (int i = 0 ; i < 5  ;i++) {
		int a, l;
		cin >> a >> l;
		sum += a*l;
	}
	int n , k;
	cin >> n >> k;
	cout << (int)((int)(sum / 5) * n) / k << "\n";;
	
}


