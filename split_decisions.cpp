// https://open.kattis.com/problems/splitdecisions/
// first, record all the pairs that only differ in 2 consecutive letters
// for every pair, we insert the position that they differ along with their 2 different letters
// then if in the future, we have to insert that same pair again, we know that we can't use this, so we erase it from the set
// we also gotta mark the pair as true the first time we insert it, so that after an deletion, we will neglect any future insertion
// also, we gotta store the length of each string pair in the set, because strings with different lengths can be used:
/* 
4
ABBA
ACCA
ABBAA
ACCAA
=> ans should be 2: the first 2 form a pair, and the last 2 form a pair
=> they form 2 clues of words of length 4 and 5, respectively.
 * 
 */

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
vector<string>v;

// returns true if can use the pair
bool cmp_diff(int i , int j) {
	int cnt = 0;
	int diff_pos = -1;
	if (v[i].length() != v[j].length()) return false;
	for (int k = 0 ; k < v[i].length(); k++) {
		if (v[i][k] != v[j][k]) {
			if (k + 1 < v[i].length() ) {
				if (v[i][k+1] != v[j][k+1]) {
					diff_pos = k;
					cnt += 2;
					k++;
					continue;
				}
			}
			cnt++;
		}
	}
	if (cnt == 2 && diff_pos > -1) return true;
	else return false;
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;
	v.resize(n);
	vector<map<string, vector<int>>>m(20);
	vector<pair<int ,int>>possible;
	for (int i = 0 ; i < n; i++) {
		cin >> v[i];
		for (int j = 0 ; j < i; j++) {
			if (cmp_diff(i, j)) {
				possible.pb({j, i});
				//cout << j << " - " << i << "\n";
			}
		}
	}

	
	map<pair<int, pair<int, pair<string, string>>>, bool>processed;
	set<pair<int, pair<int, pair<string, string>>>>ans;
	for (int i = 0; i < possible.size(); i++) {
			int x = possible[i].first, y = possible[i].second;
			string a, b;
			int diff_pos;
			for (int k = 0 ; k < v[x].length(); k++) {
				if (v[x][k] != v[y][k]) {
					a.pb(v[x][k]);
					a.pb(v[x][k+1]);
					b.pb(v[y][k]);
					b.pb(v[y][k+1]);
					if (a > b) swap(a, b);
					diff_pos = k;
					break;
				}
			}
			
			pair<int, pair<int, pair<string, string>>> p = {diff_pos, {v[x].length(), {a, b}}};
			auto it = ans.find(p);
			if (it == ans.end()) {
				if (!processed[p]) {
					ans.insert(p);
					//cout << v[x] << " " << v[y] << " " << diff_pos << "\n";
					processed[p] = true;
				}
			}
			else {
				//cout << "del: " << v[x] << " " << v[y] << " " << diff_pos << "\n";
				ans.erase(it);
			}
	}
	cout << ans.size() << "\n";
}


