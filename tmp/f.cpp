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
	
	
	string s;
	cin >> s;
	int cnt = 0;
	int cnt2 =0 ;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' ||  s[i]=='u' || s[i] == 'o') {
			cnt++;
			cnt2++;
		}
		if (s[i] == 'y') cnt2++;
	}
	cout << cnt << "\n" << cnt2 << "\n";
}


