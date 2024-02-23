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
#define sort_all(a) sort(a.begin(), a.end())

using namespace std;

/*
ull power(ll x, ull y) {
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
        return power(x, y / 2) * power(x, y / 2);
    else
        return x * power(x, y / 2) * power(x, y / 2);
}
 
ll my_ceil(ll a, ll b) {
	return (a/b) + ( (a%b)!=0 );
}

vector<ll>tree;
const ll maxA = 1e9+1;
int n,q;

				// SEGMENT TREE MINIMUM 

ll query(int node, int node_low, int node_high, int query_low, int query_high){
	if (node_low >= query_low && node_high <= query_high) {
		return tree[node];
	}
	if(node_low > query_high || node_high < query_low) {
		return maxA;
	}

	int middle = (node_low + node_high)/2;
	return min(query(2 * node, node_low, middle, query_low, query_high) 		// left child
		 , query(2 * node + 1, middle + 1, node_high, query_low, query_high));	// right child
}

void build_tree(vector<ll>a) {
	// pad with 0 to make power of 2
	while (__builtin_popcount(n) != 1) {
		a.push_back(maxA);
		n++;
	}
	tree.resize(2 * n);
	// copy elements
	for (int i = 0 ; i < n; i++){
		tree[i+n] = a[i];
	}
	// start building nodes
	for (int i = n-1; i >= 1; i--){
		tree[i] = min(tree[2*i] , tree[2*i+1]);
	}

}

void update(int pos, ll value){
	tree[pos] = value;
	pos /= 2;
	while (pos > 0) {
		ll cur_min = min(tree[2*pos], tree[2*pos+1]);
		if ( cur_min == tree[pos]) return;
		tree[pos] = cur_min;
		pos /= 2;
	}
}



//		Shortest path between any pairs
int dist[maxN][maxN];
void compute_shortest_path() {
	// essentially we start at city j, go to city k through city i.
	for (int i = 1; i <= n; i++){		// i is the intermediate city
		for (int j = 1; j <= n; j++){	// starting from city j
			for (int k = 1; k <= n; k++){	// destination is city k
				dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
			}
		}
	}
}


//	Shortest path between one node and others
vector<int>adj[maxN];
// find shortest path using Dijkstra's algorithm
priority_queue<pair<ull,int>>q; 		// default sort by first element in pairs
dist[1] = 0;
q.push({0, 1});
while (!q.empty()) {
	pair<ull,int> cur_top = q.top();
	q.pop();
	ull parent_node = cur_top.second;
	if (visited[parent_node]) continue;
	visited[parent_node] = true;
	for (auto &cur : adj[parent_node]) {
		ull weight = cur.second, cur_node = cur.first;
		if (dist[parent_node] + weight < dist[cur_node]) {
			dist[cur_node] = dist[parent_node] + weight;
			q.push({-dist[cur_node], cur_node});
		}
	}
}
*/

struct debt {
	int nxt;
	ll amount;
	ll has;
	ll total;
};

vector<set<int>>to;
vector<debt>from;
vector<bool>visited;
ull ans = 0;

void solve() {
	
}

vector<int>cycles;


// solve outside of cycles first as it's a straight forward problem.
ll dfs1(int node) {
	if (visited[node]) return 0;
	visited[node] = true;
	
	ll cost = 0;
	if (from[node].amount > from[node].has) {
		cost = from[node].amount - from[node].has;
	}
	from[from[node].nxt].has += from[node].amount;
	if (to[from[node].nxt].size() == 1) {
		cost += dfs1(from[node].nxt);
	}
	to[from[node].nxt].erase(node);
	return cost;
	
}

// solve inside cycle helper
ll dfs2(int node, ll cur, int root) {
	from[node].total = cur + from[node].has;
	visited[node] = true;
	ll cost = 0;
	if (from[node].amount > from[node].total) {
		cost = from[node].amount - from[node].total;
	}
	if (from[node].nxt == root) return cost;
	
	cost += dfs2(from[node].nxt, from[node].amount, root);
	return cost;
}

/*
void find_cycle(int node) {
	// find the cycle on the path starting at `node`
	int a = from[node];
	int b = from[from[node]];
	while (a != b) {
		a = from[a];
		b = from[from[b]];
	}
	a = node;
	while (a != b) {
		a = from[a];
		b = from[b];
	}
	return a; // return the first node in the cycle
}
*/

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	int n;
	cin >> n;
	from.assign(n, {-1, 0, 0, 0});
	to.assign(n, set<int>());
	visited.assign(n, false);
	//total.assign(n, 0);
	for (int i = 0 ;i < n; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		from[i] = {a, b, 0};
		to[a].insert(i);	
	}
	
	for (int i = 0 ; i< n; i++) {
		if (to[i].size() == 0) {
			ans += dfs1(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			
			// solve inside cycles, find optimal starting point.
			int root = i, cur = from[root].nxt;
			ll mi = from[root].amount - from[root].has, min_start = root;
			while (cur != root) {
				if (from[cur].amount - from[cur].has < mi) {
					mi = from[cur].amount - from[cur].has;
					min_start = cur;
				}
				cur = from[cur].nxt;
			}
			ans += dfs2(min_start, 0, min_start);
			
			/*
			ll root = i , res = dfs2(i, 0, root);
			if (from[from[root].nxt].nxt == root) {
				ans += res;
				continue;
			}
			ll mi = res, cur = *to[root].begin(), nxt = root;
			ll cur_cost = mi;
			while (cur != root) {
				cout << cur << "\n";
				if (from[nxt].total < from[nxt].amount) {
					cur_cost -= (from[nxt].amount - from[nxt].total);
				}
				cout << from[cur].total << ";" << from[cur].amount << " - " << from[nxt].total << ";" << from[nxt].amount << " "  << cur_cost <<";\n";
				if (from[cur].total < from[cur].amount) {
					cur_cost -= (from[cur].amount - from[cur].total);
				}
				
				from[cur].total -= from[*to[cur].begin()].amount;
				if (from[cur].total < from[cur].amount) {
					cur_cost += from[cur].amount - from[cur].total;
				}
				cout << from[cur].total << ";" << from[cur].amount << " - " << from[nxt].total << ";" << from[nxt].amount << " "  << cur_cost <<";\n";

				from[nxt].total += from[cur].amount;
				if (from[nxt].total < from[nxt].amount) {
					cur_cost += (from[nxt].amount - from[nxt].total);
				}
				cout << from[cur].total << ";" << from[cur].amount << " - " << from[nxt].total << ";" << from[nxt].amount << " "  << cur_cost <<";\n\n";
				if (cur_cost < mi) {
					mi = cur_cost;
				}
				nxt = cur;
				cur = *to[cur].begin();
			}
			*/
			//ans += mi;
			
			
		}
	}
	cout << ans << "\n";
}


