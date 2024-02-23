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

string extract(string s) {
	string res;
	while (s.find('-') != -1) {	// loop until - is not in the string
		string token = s.substr(0, s.find('-'));
		if (token == "upper") res.pb('3');
		else if (token == "middle") res.pb('2');
		else res.pb('1');
		s.erase(0, s.find('-') + 1);
	}
	
	if (s == "upper") res.pb('3');
	else if (s == "middle") res.pb('2');
	else res.pb('1');
	return res;
}

void solve() {
	int n;
	cin >> n;
	vector<pair<string , string>>v(n);
	int max_length = 0;
	for (int i = 0 ; i < n; i++) {
		string name;
		while (cin.peek() != ':') {
			char c;
			cin >> c;
			name.pb(c);
		}
		v[i].second = name;
		cin.ignore();
		while (cin.peek() == ' ') cin.ignore();
		
		string s;
		getline(cin , s);
		s = s.substr(0, s.size() - 6);
		//cout << s << "\n";
		v[i].first = extract(s);
		
		max_length = max(max_length, (int)v[i].first.length());
	}
	
	map<string, vector<string>>m;
	for (auto &p : v) {
		reverse(p.first.begin(), p.first.end());
		while (p.first.size() < max_length) p.first.pb('2');
		m[p.first].pb(p.second);
	}
	
	auto it = m.end()--;
	for ( ; it != m.begin(); it--) {
		auto p = *it;
		sort(p.second.begin(), p.second.end());
		reverse(p.second.begin(), p.second.end());
		for (auto &name : (*it).second) cout << name << "\n";
	}
	auto p = *it;
	sort(p.second.begin(), p.second.end());
	reverse(p.second.begin(), p.second.end());
	for (auto &name : p.second) cout << name << "\n";
	for (int i = 0 ; i < 30; i++) cout << '=';
	cout << "\n";
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


