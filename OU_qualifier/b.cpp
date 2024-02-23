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
	
	string s1, s2;
	cin >> s1 >> s2;
	int i = 0, j = 0;
	int l1 = s1.length(), l2= s2.length();
	while (i < l1 || j < l2) {
		if (i == l1) {
			for (; j < l2; j++) cout << s2[j];
			break;
		}
		else if (j == l2) {
			for (; i < l1; i++) cout << s1[i];
			break;
		}
		if (s1[i] < s2[j]) {
			cout << s1[i];
			i++;
		}
		else {
			cout << s2[j];
			j++;
		}
	}
	
}


