//#include<bits/stdc++.h>
// https://open.kattis.com/problems/guilds

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<algorithm>

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

map<string, int>m;
vector<string>v;

vector<int>link;

/*
For every chain of guilds, each child guid will have the answer = the top-level guild. So the answer for all children in a chain will be the same. 
Therefore, as we go up the chain to find the top-level guild for a guild,  we will update the answer for the guilds we visit along the path as well.
*/
int f(int x) {
	if (x == link[x]) {
		return x;
	}
	link[x] = f(link[x]);
	return link[x];
}

void unite(int a, int b) {
	b = f(b);
	link[a] = b;
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;
	link = vector<int>(2*n + 5);
	v = vector<string>(2*n + 5);
	for (int i = 1 ; i <= 2*n+5; i++) {
		link[i] = i;
	}
	
	int cnt = 1;
	vector<int>order;
	for (int i = 0 ;i < n; i++) {
		string a, b;
		cin >> a >> b;
		int x, y;
		if (m[a] == 0) {
			m[a] = cnt;
			v[cnt] = a;
			cnt++;
		}
		if (m[b] == 0) {
			m[b] = cnt;
			v[cnt] = b;
			cnt++;
		}
		
		x = m[a];
		y = m[b];
		unite(x, y);
		order.pb(x);
		
	}
	for (int &i : order) {
		cout << v[i] << " " << v[f(i)] << "\n";
	}
}


