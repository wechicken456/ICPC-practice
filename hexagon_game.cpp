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
	if (cin.peek() == '\n') cin.ignore();
	string pos_str;
	getline(cin, pos_str);
	string val_str;
	getline(cin, val_str);
	vector<int>pos;
	vector<int>vals;
	stringstream ss1(pos_str), ss2(val_str);
	string num_str;
	while (ss1 >> num_str) {
		pos.pb(stoi(num_str));
		ss2 >> num_str;
		vals.pb(stoi(num_str));
	}
	int n = pos.size(); 
	
	for (int i= 0 ; i < n; i++) {
		
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	
	
}


