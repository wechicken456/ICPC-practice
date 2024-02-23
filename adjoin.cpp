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
int n, l;
vector<vector<int>>adj;

int longest1[200001];
int longest2[200001];
int furthest[200001];	// the adjacent node which is on the longest path starting from i
bool visited[200001];

int sum = 0;
int cur_longest = 0;
int cur_root = 0;

void make_tree(int node, int p, int start) {
	visited[node] = true;
	if (node != start && adj[node].size() == 1) {
		longest1[node] = 0;
		furthest[node] = node;
		longest2[node] = 0;
		return;
	}
	for (int &nxt : adj[node]) {
		if (nxt != p) {
			make_tree(nxt, node, start);
			if (longest1[nxt]  + 1 > longest1[node]) {
				longest2[node] = longest1[node];
				furthest[node] = nxt;
				longest1[node] = longest1[nxt] + 1;
				
			}
			else {
				longest2[node] = max(longest2[node], longest1[nxt] + 1);
			}
		}
	}
	
}

void calc_longest(int node, int p, int start) {
	if (node != start) {
		if (furthest[p] == node) {						// if the longest path starting at p goes through the current node
			if (longest2[p] + 1 > longest1[node]) {		// if the second longesth path + 1 is > then the longest path (happens if both paths are equal)
				longest2[node] = longest1[node];
				
				furthest[node] = p;
				longest1[node] = longest2[p] + 1;
			}
			else {
				longest2[node] = max(longest2[node], longest2[p] + 1);
			}
		}
		else {
			longest2[node] = longest1[node];
			longest1[node] = longest1[p] + 1;
			furthest[node] = p;
			
		}
	}
	
	if (longest1[node] > cur_longest) {
		//cout << "node " << node << " " << longest1[node] << "\n";
		cur_longest = longest1[node];
		cur_root = node;
	}
	
	for (int &nxt : adj[node]) {
		if (nxt != p)  calc_longest(nxt, node, start);
	}
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	cin >> n >> l;
	adj.resize(n);
	for (int i = 0; i < l; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	vector<int>centers;
	int longest_dia = 0;
	
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			make_tree(i, i, i);
			calc_longest(i, i, i);
			
			centers.pb( ceil((double)cur_longest / 2));
			longest_dia = max(longest_dia, cur_longest);
			cur_longest = 0;
		}
	}
	
	if (centers.size() > 1) {
		sort(centers.begin(), centers.end());
		int ans = centers[centers.size() - 1] + centers[centers.size() - 2] + 1;
		if (centers.size() > 2) {
			ans = max(ans, centers[centers.size() - 2] + centers[centers.size() - 3] + 2);
		}
		ans = max(ans, longest_dia);
		cout <<  ans << "\n";
	}
	else cout << longest_dia << "\n";

}


