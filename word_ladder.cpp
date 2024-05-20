// https://www.youtube.com/watch?v=GdjCI2wZrD8&list=PLKtOWhDBKQPas91g6eeYNmeixA9ThjxoU&index=4
// basically just rotate the second half cyclicly, then for every cycle, rotate the first half


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

void solve(string cur, int idx_first_half, int idx, int n) {
	for (int i = 0 ; i < 25; i++) {
		for (int j = 0 ; j < 5; j++, idx++) {
			cur[5 + j % 5]++;
			if (cur[5 + j % 5] > 'z') cur[5 + j % 5] = 'a';
			cout << cur << "\n";	
			if (idx + 1 == n) return;
		}
	}
	if (idx_first_half % 2 == 0) cur[4]++;
	else cur[2]++;
	idx++;
	cout << cur << "\n";
	if (idx == n) return;
	if (idx_first_half % 2 == 0) cur[3]++;
	else cur[1]++;
	idx++;
	cout << cur << "\n";
	if (idx == n) return;
	solve(cur, idx_first_half + 1, idx, n);
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;
	string a = "aaaaaaaaaa";
	solve(a, 0, 0, n);
	
}


