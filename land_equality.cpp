// https://open.kattis.com/problems/landequality
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ull r , c;
	cin >> r >> c;
	ull cnt_0=0, cnt_2=0, cnt_1=0;
	pair<int, int> pos_0;
	vector<vector<ull>>a(r, vector<ull>(c));
	for (int i = 0 ; i < r; i++) {
		for (int j = 0; j < c; j++) {
			ull x;
			cin >> x;
			a[i][j] = x;
			if (x == 0) {
				cnt_0++;
				pos_0 = {i, j};
			}
			else if (x == 1) {
				cnt_1++;
			}
			else cnt_2++;
		}
	}
	if (cnt_0 >= 2) {
		cout << "0\n";
	}
	else if (cnt_0 == 1) {
		if (cnt_1 >= 1) {
			if (r == 1) {
				ull ans  = (pos_0.second > 0) ? a[0][0] : 1e7;
				ull tmp = (pos_0.second < c - 1) ? a[0][c-1] : 1e7;
				ans = min(tmp, ans);
				cout << ans << "\n";
			}
			else if (c == 1) {
				ull ans  = (pos_0.first > 0) ? a[0][0] : 1e7;
				ull tmp = (pos_0.first < r - 1) ? a[r-1][0] : 1e7;
				ans = min(tmp, ans);
				cout << ans << "\n";
			}
			else {
				cout << "1\n";
			}
		}
		else {
			cout << "2\n";
		}
	}
	else {
		if (cnt_2 >= 2) {
			if (cnt_2 % 2 == 0) {
				cout << "0\n";
			}
			else {
				cout << ((ull)1 << (ull)(cnt_2 / 2)) << "\n";
			}
		}
		else if (cnt_2 == 1) {
				cout << "1\n";
		}
		else {
			cout << "0\n";
		}
	}
}


