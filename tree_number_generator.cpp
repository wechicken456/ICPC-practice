// https://open.kattis.com/problems/treegenerator

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
	vll ancestor;
	vector<ll> up;
	int depth;
	ll val;
	ll mod_val;
};

vvll edge;
vector<Node> tree;
ll n, m , q;
vector<ll>powers;

void build_tree(int cur_node, int cur_depth, int p, ll num) {
	int levels = (cur_depth == 0) ? 0 : floor(log2(cur_depth));
	tree[cur_node].ancestor.resize(levels + 1);
	tree[cur_node].up.resize(levels + 1);
	tree[cur_node].ancestor[0] = p;
	tree[cur_node].depth = cur_depth;
	if (cur_node != 0) tree[cur_node].up[0] = ( (tree[cur_node].val%m)*10 + tree[p].val % m) % m;
	
	num = (num % m) * 10;
	num += tree[cur_node].val % m;
	num %= m;
	tree[cur_node].mod_val = num;
	for (int i = 1; i < levels + 1; i++) {
		int cur_half = tree[cur_node].ancestor[i-1];
		tree[cur_node].ancestor[i] = tree[cur_half].ancestor[i-1];
		
		ll tmp = (tree[cur_node].up[i-1] - tree[cur_half].val % m) % m;
		tree[cur_node].up[i] =  tmp*powers[1 << (i-1)] % m 
								+ tree[cur_half].up[i-1] % m;
		tree[cur_node].up[i] %= m;
	}
	for (auto &nxt : edge[cur_node]) {
		if (nxt != p) {
			build_tree(nxt, cur_depth + 1, cur_node, num);
		}
	}
}

pair<int, ll> get_ancestor(int node, int k) {
	ll res = 0;
	int cnt = 0;
	for (int i = tree[node].ancestor.size() - 1; i >= 0 ; i--) {
		if (i >= tree[node].ancestor.size()) continue;
		if (k & (1 << i)) {
			if (cnt > 0) {
				res -= tree[node].val;
				res %= m;
			}
			res *= powers[1 << i];
			res %= m;
			res += tree[node].up[i] % m;
			res %= m;
			node = tree[node].ancestor[i];
			cnt++;
		}
	}
	return make_pair(node, res);
}

int lca(int a, int b) {
	if (tree[a].depth < tree[b].depth) {
		swap(a, b);
	}
	
	int diff = tree[a].depth - tree[b].depth;
	
	a = get_ancestor(a, diff).first;
	if (a == b) return a;
	
	for (int i = tree[a].ancestor.size() - 1; i >= 0; i--) {
		if (i >= tree[a].ancestor.size()) continue;

		if (tree[a].ancestor[i] != tree[b].ancestor[i]) {
			a = tree[a].ancestor[i];
			b = tree[b].ancestor[i];
		}
	}
	return tree[a].ancestor[0];
}

int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m >> q;
	tree = vector<Node>(n);
	edge = vvll(n);
	powers = vector<ll>(n + 1);
	powers[0] = 1 % m;
	for (int i = 1; i < n; i++) {
		int a ,b;
		cin >> a >> b;
		a--;
		b--;
		edge[a].pb(b);
		edge[b].pb(a);	
		powers[i] = 10 * powers[i-1];
		powers[i] %= m;
	}
	powers[n] = 10 * powers[n-1];
	powers[n] %= m;
	
	for (int i = 0 ; i < n; i++) {
		cin >> tree[i].val;
		tree[i].val %= m;
	}
	
	build_tree(0, 0, 0, 0);
	
	/*
	for (int i = 0 ; i < n; i++) {
		cout << "node " << i << " :\n";
		cout << tree[i].mod_val << "\n";
		for (ll &x : tree[i].up) cout << x << " ";
		cout << "\n";
	}*/
	
	for (int i = 0 ; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		if (a == b) {
			cout << tree[a].val % m << "\n";
			continue;
		}
		int common = lca(a, b);
		int diff_a = tree[a].depth - tree[common].depth;
		int diff_b = tree[b].depth - tree[common].depth;
		ll first_part = (diff_a == 0) ? tree[a].val : get_ancestor(a, diff_a).second;
		first_part %= m;
		ll tmp = (tree[common].mod_val * powers[diff_b]) % m;
		tmp = (tree[b].mod_val - tmp) % m;
		ll second_part = tmp;
	
		ll ans;
		if (diff_a == 0) ans = ((tree[a].val * powers[diff_b]) % m + second_part) % m;
		else if (diff_b == 0) ans = first_part % m;
		else ans = ( (first_part*powers[diff_b]) % m + second_part) % m;
		//cout << first_part << " " << second_part << " " << ans << "\n";
		cout << ans << "\n";
	}
}


