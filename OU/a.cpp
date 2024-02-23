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

struct node {
	char c;
	int l;
	int r;
};

ll n, m ;
vector<node>graph;

vector<char>v1;
vector<char>v2;

map<char, char>f;

void dfs(int cur, vector<char> &v) {
	if (cur == 0) return;
	v.pb(f[graph[cur].c]);
	if (graph[cur].c == 'L') {
		dfs(graph[cur].l, v);
		graph[cur].c = 'R';
	}
	else {
		dfs(graph[cur].r, v);
		graph[cur].c = 'L';
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	f['R'] = 'L';
	f['L'] = 'R';
	
	graph.resize(m + 1);
	for (int i = 1 ; i <= m; i++) {
		cin >> graph[i].c >> graph[i].l >> graph[i].r;
	}
	dfs(1, v1);
	dfs(1, v2);
	if (n % 2 == 0) {
		for (auto &c : v2) {
			cout << c;
		}
	}
	else {
		for (auto &c : v1) {
			cout << c;
		}
	}
}


