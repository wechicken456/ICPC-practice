// https://open.kattis.com/problems/abandonedanimal

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

// for each item, what are the shops that have it
map<string, set<int>>item;
vector<string>vs;

int n;
int t;
int exist = 0;

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	
	cin >> n;
	int k;
	cin >> k;	
	for (int i = 0 ; i < k; i++) {
		int a;
		string s;
		cin >> a >> s;
		item[s].insert(a);
	}

	cin >> t;
	if (t == 0) {
		cout << "ambiguous\n";
		return 0;
	}
	
	
	for (int i = 0 ; i < t; i++) {
		string s;
		cin >> s;
		// convert string to lowercase
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
		vs.pb(s);
	}
	
	
	
	if (exist == 0) {
		cout << "impossible\n";
	}
	else if (exist == 1) {
		cout << "unique\n";
	}
	else {
		cout << "ambiguous\n";
	}
}


