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

struct Node {
	bool is_end = false;
	string ending;
	int adj[3];
	ull val = 0;
};

vector<Node>graph;
map<int, int>section;
vector<bool>visited;

ull find_path(int node) {
	if (graph[node].is_end == true) {
		if (graph[node].ending == "favourably") return 1;
		else return 0;
	}
	if (visited[node] == true) {
		return graph[node].val;
	}
	visited[node] = true;
	ull sum = 0;
	for (int &nxt : graph[node].adj) {
		sum += find_path(section[nxt]);
	}
	graph[node].val = sum;
	return sum;
} 

void solve() {
	int n;
	ull ans = 0;
	cin >> n;
	graph = vector<Node>(n+1);
	visited = vector<bool>(n+1);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		section[x] = i;
		while (cin.peek() == '\n' || cin.peek() == ' ') cin.ignore();
		if (cin.peek() >= '0' && cin.peek() <= '9') {
			cin >> graph[i].adj[0] >> graph[i].adj[1] >> graph[i].adj[2];
		}
		else {
			string s;
			while (cin.peek() == '\n' || cin.peek() == ' ') cin.ignore();
			getline(cin , s);
			graph[i].ending = s;
			graph[i].is_end = true;
		}
	}
	ans = find_path(section[1]);
	cout << ans << "\n";
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


