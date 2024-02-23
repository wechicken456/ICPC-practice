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

vector<vector<int>>edge;

void solve() {
	
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n , m;
	cin >> n >> m;
	edge.resize(n);
	for (int i = 0 ;i < n; i++) {
		int a ,b;
		cin >> a >> b;
		edge[a].pb({w, b});
		edge[b].pb({w, a});
	}
	
}


