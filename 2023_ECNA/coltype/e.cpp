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

ull pows[64];

void solve() {
	
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	pows[0] = 1;
	for (int i = 1; i < 63; i++) {
		pows[i] = 2*pows[i-1];
	}
	string s;
	cin >> s;
	if (s[s.length() -1] != 'O') {
		cout << "INVALID\n";
		return 0;
	}
	
	for (int i = 0 ; i < s.length() - 1; i++) {
		if (s[i] == 'O' && s[i + 1] == 'O') {
			cout << "INVALID\n";
			return 0;
		}
	}
	if (s.length() == 1) {
		cout << "5\n";
		return 0;
	}
	ull ans = (ull)1 << 63;
	// bruteforce each power of 2. let pows[i] = the power of 2 after applying the input sequence.
	for (int i = 2; i < 63; i++) {	
		if ( (pows[i] - 1) % 3 != 0) continue; // all numbers in the sequnce are integers
		
		ull num = (pows[i] - 1) / 3;
		bool check = true;
		for (int j = s.length() - 1 ; j > 0 && check; j--) {
			
			if (s[j] == 'O') {	// case currently odd
				num = num * 2;
				
			}
			else {		// case currently even
				if (s[j-1] == 'E') {	// before we are also even.
					num = num * 2;
				}
				else {
					if ( (num - 1) % 3 != 0) {		// all numbers in the sequnce are integers
						check = false;
						break;
					}
					num = (num - 1) / 3;
				}
			}
			for (int k = 0; k < 63; k++) {
				if (num == pows[k]) {
					check = false;
					break;
				}
			}
		}
		if (check) {
			ans = min(ans, num);
		}
	}
	cout << ans << "\n";
}


