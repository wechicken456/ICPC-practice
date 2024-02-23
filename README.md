# ICPC cheatsheet

## Includes:
```C
#include<iostream>
#include<set>
#include<stdio.h>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
#include<math.h>
#include<cmath>
```

or

```C
#include<bits/stdc++.h>
```

## Permutations
```C++
vector<int> permutation;
    for (int i = 0; i < n; i++) {
        permutation.push_back(i);
    }
    do {
        // process permutation
    } while (next_permutation(permutation.begin(),permutation.end()));
```

## Longest increasing subsequence
`d[l] = a[i]` the **smallest** element at which an increasing subsequence of length  `l`  ends.
1. The array  `d`  will always be sorted:  `d[l-1] < d[l]`
2. => There's only 1 position in `d` with `d[l-1] < a[i] < d[l]`
3. => Use binary search.
O(NlogN) 
```C++
int lis(vector<int> const& a) {
    int n = a.size();
    const int INF = 1e9;
    vector<int> d(n+1, INF);
    d[0] = -INF;

    for (int i = 0; i < n; i++) {
        int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[l-1] < a[i] && a[i] < d[l])
            d[l] = a[i];
    }

    int ans = 0;
    for (int l = 0; l <= n; l++) {
        if (d[l] < INF)
            ans = l;
    }
    return ans;
}
```

## Nearest smaller element (to the left)
```C++
void printPrevSmaller(int arr[], int n)
{
    // Create an empty stack
    stack<int> S;
 
    // Traverse all array elements
    for (int i=0; i<n; i++)
    {
        // Keep removing top element from S while the top
        // element is greater than or equal to arr[i]
        while (!S.empty() && S.top() >= arr[i])
            S.pop();
 
        // If all elements in S were greater than arr[i]
        if (S.empty())
            cout << "_, ";
        else  //Else print the nearest smaller element
            cout << S.top() << ", ";
 
        // Push this element
        S.push(arr[i]);
    }
}
```


## Custom comparator
```C++
struct compare{
  public:
  bool operator()(Node& a,Node& b) // overloading both operators 
  {
      return a.w < b.w: // if you want increasing order;(i.e increasing for minPQ)
      return a.w > b.w // if you want reverse of default order;(i.e decreasing for minPQ)
   }
};

...

priority_queue<Node, vector<Node>, compare> q;
```

***
## Maximum flow (Dinic)
```C++
struct Edge {
	int u;	// from v to u
	ll cap, flow = 0;
	Edge(int u, ll cap) : u(u), cap(cap) {}
};

const int maxN = 500;
const ll maxX = 1e17;
int n, m,x;
int s, t;	// source and sink

vector<int>level(maxN, 0);	// for level graph
vector<Edge>edges;	// edges are stored by id = order they are added in
vector<int>ptr(maxN, 0);	// pointer for dfs optimization
vector<vector<int>>adj(maxN);

bool bfs() {
	fill(level.begin(), level.end(), -1);
	level[s] = 0;
	queue<int>q;
	q.push(s);
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		for (int &id : adj[v]) {
			
			if (level[edges[id].u] != -1) continue;
			if (edges[id].cap - edges[id].flow <= 0) continue;
	
			// u hasn't been labeled and (v, u) has pos residual capacity
			level[edges[id].u] = level[v] + 1;
			q.push(edges[id].u);
		}
	}
	return level[t] != -1;	// t reachable?
}

// cur_pushed: current flow on the way to t
ll dfs(int v, ll cur_pushed) {
	if (v == t) return cur_pushed;
	
	// pass by reference to increase the pointer
	for (int &i = ptr[v] ; i < adj[v].size(); i++) {
		int id = adj[v][i];
		
		if ( (level[edges[id].u] != level[v] + 1) || (edges[id].cap - edges[id].flow <= 0) ) {
			continue;
		}
		
		ll pushed = dfs(edges[id].u, min(cur_pushed, edges[id].cap - edges[id].flow));
		if (pushed == 0) continue;
		
		// to update both edges at the same time, storing the edges in the chosen data structure is necessary
		edges[id].flow += pushed;
		edges[id ^ 1].flow -= pushed;
		return pushed;
	}
	return 0;
}

int main(){
	cin >> n >> m;
	s = 0, t = n - 1;
	
	for (int i = 0 ; i < m; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		adj[a].pb(edges.size());	// which is the current size of `edges`
		adj[b].pb(edges.size() + 1);
		edges.emplace_back(b, c);
		edges.emplace_back(a, 0);
	}
	ll max_flow = 0;
	while (bfs()) {
		fill(ptr.begin(), ptr.end(), 0);	// reset pointers
		while (ll cur_pushed = dfs(s, maxX)) {
			max_flow += cur_pushed;
		}
	}
	cout << max_flow << "\n";
}
```

***
## Min cut (Dinic)
To count and find edges in the min cut, change `struct Edge` to include the vertex that the edge starts from a.k.a `v`:
```C++
struct Edge {
	int v, u;	// from v to u
	ll cap, flow = 0;
	Edge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};
...

// find all nodes reachable in the residual graph AFTER finding max flow
// the set of saturated edges AT this node forms a min cut
// this is because the max flow is the sum of saturated edges.
vector<int>reach(maxN, 0);
void dfs2(int v, int p) {
	for (int i = 0 ; i < adj[v].size(); i++) {
		int id = adj[v][i];
		if (edges[id].u == p) continue;
		if (reach[edges[id].u] == 1) continue;
		
		if (edges[id].cap - edges[id].flow > 0) {
			reach[edges[id].u] = 1;
			dfs2(edges[id].u, v);
		}
	}
}
...
reach[0] = 1;
dfs2(0, 0);
for (auto &e : edges) {
  if (reach[e.v]) {
    if (!reach[e.u]) {
      cout << e.v + 1 << " " << e.u + 1 << "\n";
    }
  }
}
```
***
## Maximum number of disjoint paths
Find all paths from `1` to `n` such that each vertex appears only in 1 path. Edges have **UNIT** capacity. 

Using **Edmond-Karps algorithm**, we can find the max flow which is the number of disjoint paths. 

L et `prev = par[cur]`. 

When we update the flow in the inner while loop: 
- if the current edge `(prev, cur)` used to push the flow is a valid edge (not a reversed edge), then we set `succ[prev][cur] = true`, which means the edge `(prev, cur)` was used to push the flow.
- Otherwise, we used a *reversed edge* a.k.a `(cur, prev)`, meaning instead of taking the correct edge in the previous rotation (before this augmenting path), we take another edge. So we set `succ[cur][prev] = false`.

To construct the paths: We already have the set of edges used to push flow found in the above section, so we only need to connect the edges together (find parent of each node). If `succ[node][nxt] = true` (we used this edge to push flow) && `par[nxt] == -1` (we haven't used this vertice), then set `succ[node][nxt] = false` because we use this edge now && `par[i] = node`.

```C++
...
while ((new_flow = find_flow())) {
		// new_flow is either 1 or 0 in this problem
		int cur = n - 1;
		while (cur != 0) {
			int prev = par[cur];
			capacity[cur][prev] += new_flow; // reverse edge
			capacity[prev][cur] -= new_flow; // edge
			
			if (isedge[prev][cur]) {
				succ[prev][cur] = true;
			}
			else {	// if we're using reverse edge, then the corresponding correct edge is not used
					// because instead of taking the correct edge in the previous rotation (before this augmenting path), we take another edge. 
				succ[cur][prev] = false;
			}
			cur = prev;
		}
		cnt++;
	}
	cout << cnt << "\n";
	SET(par, n, -1);
	par[0] = -2;
	while (dfs(0)) {
		int cur =  n - 1;
		vector<int>v;
		while (cur != 0) {
			v.pb(cur);
			cur = par[cur];
		}
		v.pb(0);
		
		cout << v.size() << "\n";
		for (int i = v.size() - 1; i >= 0; i--) cout << v[i]+1 << " ";
		cout << "\n";
		
		SET(par, n, -1);
		par[0]= -2;
	};
```
***

## SEGMENT TREE WITH LAZY PROPAGATION
Intuition: for a query (l1, r1), that covers our node, then the increase for each element is: 
```
(index) l1   l1 + 1     ...          l 		...	 r 	

(inc)   1       2     + ... +    l - l1 + 1     ...  r - l1 + 1
```
then the increase in sum can be decomposed into:
`how far we are from l1` + `(1 + 2 + ... + r - l + 1)`
Example: (l1, r1) = (2, 9). (l, r) = (5, 8).
by the time we reach index 5, the increase for the 5-th element is 5 -2 + 1 = 4.
inc(6-th element)=5
inc(7-th element)=6
inc(8-th element)=7

=> increase in sum for our node = 4 + 5 + 6 + 7 = (3 + 1) + (3 + 2) + (3 + 3) + (3 + 4) = 3*4 + (1+2+3+4)

So say we have some increase queries denoted as (l1, r1), (l2, r2), ... (lk, rk) that COVERS our node

Then, let our node's range be (l, r), the increase in sum for our node is:
```

  (l - l1) + (l - l1 + 1) + ... + (l - l1 + r - l + 1)	(there are r - l + 1 terms)
+ (l - l2) + (l - l2 + 1) + ... + (r - l2 + 1)
...
+ (l - lk) + (l - lk + 1) + ... + (r - lk + 1)

= (r - l + 1) * (l - l1) + (1 + 2 + ... + r - l + 1)
+ (r - l + 1) * (l - l2) + (1 + 2 + ... + r - l + 1)
...
+ (r - l + 1) * (l - lk) + (1 + 2 + ... + r - l + 1)

= (r - l + 1) * ( (l - l1) + (l - l2) + ... + (l - lk) ) + k*(r -l + 1)*(r - l + 2) / 2

=> z1 = k
=> z0 = (l - l1) + (l - l2) + ... + (l - lk)
```

Now if the queries don't entirely covers the node's range but overlap the node's range.
Then, the increase in sum for an overlap into the RIGHT of a query range is :
1. the previous update using the method above: `sum += z0*(r - l + 1) + k*(r -l + 1)*(r - l + 2) / 2`
2. the current update: how far we are from the LEFT of the query * range(node) + (1 + 2 + ... + range(node)) = `(l - l1)*(r - l + 1) + 1*(r - l + 1)*(r - l + 2) / 2`


Then, to propagate the update to the LEFT child, we pass `z1` and `z0` to it. 
This works because the LEFT of the child is also the LEFT of the current node, 
so the distances to the LEFT of the previous queries are the same.

To propagate the update to the RIGHt child, we use the same strategy, 
except that the distances to the LEFT of the previous queries (`z0`) are INCREASED by `(r - l + 1)/2`
Finally, we set `z0 = z1 = 0` for the current node.

```C++
struct tree_node {
	ll sum;
	ll z1, z0;	
};

ll n ,q ;
vector<tree_node>tree;
vector<ll>a;

void build_tree() {
	for (ll i = 0 ; i < n; i++) {
		tree[i + n].sum = a[i];
		tree[i + n].z1 = tree[i+n].z0 = 0;
	}
	
	for (ll i = n-1 ; i > 0; i--) {
		tree[i].sum = tree[2*i].sum + tree[2*i + 1].sum;
		tree[i].z1 = tree[i].z0 = 0;
	}
}

ll polynomial_update(ll degree, ll coef, ll range) {
	if (degree == 0) {
		return range*coef;	
	}
	else {
		return (coef*range*(range + 1)) / 2;
	}
}

ll increase(ll node, ll node_l, ll node_h, ll query_l, ll query_h, ll z1, ll z0, ll q_type) {
	tree[node].z1 += z1;	// receive update from parent 
	tree[node].z0 += z0;	// receive udpate from parent
	if (node_l > query_h || node_h < query_l) {		// query completely outside node
		return 0;
	}
	else if (node_l >= query_l && node_h <= query_h) {	// query completely covers node
		// if its an increase query
		if (q_type == 1) {
			tree[node].z1 += 1;
			tree[node].z0 += node_l - query_l;
		} 
		return tree[node].sum + polynomial_update(1, tree[node].z1, node_h - node_l + 1) + polynomial_update(0, tree[node].z0, node_h - node_l + 1);
	}
	
	ll middle = (node_l + node_h) / 2;
	// update sum from previous lazy updates
	tree[node].sum += polynomial_update(1, tree[node].z1, node_h - node_l + 1) + polynomial_update(0, tree[node].z0, node_h - node_l + 1);

	if (q_type == 1){	// an increase query, then update sum first so we can propagate updates to children
		ll intersection = min(node_h, query_h) - max(node_l, query_l) + 1;
		if (query_l <= node_l) {
			tree[node].sum += polynomial_update(0, node_l - query_l, intersection) + polynomial_update(1, 1, intersection);
		}
		else {
			tree[node].sum += polynomial_update(1, 1, intersection);
		}
	}

	ll tmp_z1 = tree[node].z1, tmp_z0 = tree[node].z0, tmp_z0_2 = 0;
	if (tmp_z0 > 0 || tmp_z1 > 0 ) {
		tmp_z0_2 = tmp_z0 + tmp_z1*(node_h - node_l + 1) / 2;	// right child's increase in `z0`
	}
	tree[node].z1 = 0;
	tree[node].z0 = 0;
	return  increase(2*node, node_l, middle, query_l, query_h, tmp_z1, tmp_z0, q_type) 
		 +  increase(2*node + 1, middle + 1, node_h, query_l, query_h, tmp_z1, tmp_z0_2, q_type);
	
	
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> q;
	a = vector<ll>(n);
	for (ll i= 0 ;i < n;i ++) {
		cin >> a[i];
	}
	while (__builtin_popcount(n) != 1) {
		a.pb(0);
		n++;
	}
	
	tree.resize(2*n);
	build_tree();
	
	for (ll i = 0 ; i < q; i++) {
		ll c, l , h;
		cin >> c >> l >> h; 
		l--; h--;
		if (c == 1) {	// increase query
			increase(1, 0, n - 1, l , h, 0, 0, 1);
		}
		else {		// read query
			cout << increase(1, 0, n - 1, l , h, 0, 0, 2) << "\n";
		}
	}
}
```
***

## Sqrt Decomp
<img width="943" alt="image" src="https://github.com/wechicken456/ICPC-practice/assets/55309735/20c32a23-3377-4b49-9e5f-979fc98be4c7">
<img width="943" alt="image" src="https://github.com/wechicken456/ICPC-practice/assets/55309735/1813b35d-d893-4078-aa60-cadd0fb4ef65">


```C++
// input data
int n;
vector<int> a (n);

// preprocessing
int len = (int) sqrt (n + .0) + 1; // size of the block and the number of blocks
vector<int> b (len);
for (int i=0; i<n; ++i)
    b[i / len] += a[i];

// answering the queries
for (;;) {
    int l, r;
  // read input data for the next query
    int sum = 0;
    for (int i=l; i<=r; )
        if (i % len == 0 && i + len - 1 <= r) {	
            // if the whole block starting at i belongs to [l, r]
            sum += b[i / len];
            i += len;
        }
        else {  // the tail elements
            sum += a[i];
            ++i;
        }
}
```
***

## LCA
```C++
// LCA of a and b
int get_common(int a, int b) {	// assuming a and b are of the same depth
	int i = 0;
	for (; i < tree[a].ancestor.size(); i++) {
		if (tree[a].ancestor[i] == tree[b].ancestor[i]) {
			break;
		}
	}
	if (i == 0) {
		return a;
	}
	else if (i == 1) {
		return boss[a];
	}
	else {	// find the first common ancestor (DOESN'T HAVE TO BE LOWEST), then go back 1 power of 2 to find the LOWEST common ancestor
		return get_common(tree[a].ancestor[i-1], tree[b].ancestor[i-1]);
	}
}

// get the k-th ancestor of node
int get_ancestor(int node, int k) {
	if (k > tree[node].depth) return -1;
	if (k == 0) return node;
	if (k == 1) return boss[node];
	int idx = floor(log2(k));
	return get_ancestor(tree[node].ancestor[idx + 1], k - powers_2[idx]);
} 

void build_node(int cur_node, int cur_depth) {
	int levels = (cur_depth != 0) ? floor(log2(cur_depth)) : 0;
	tree[cur_node].depth = cur_depth;
	tree[cur_node].ancestor = vector<int>(levels + 2);	
	tree[cur_node].ancestor[0] = cur_node;				// 0th ancestor is itself
	tree[cur_node].ancestor[1] = boss[cur_node];		// we alr know 1th ancestor is its boss
	
	for (int i = 2 ; i < levels + 2; i++) {				// every 2^i-th ancestor is the 2^(i-1)-th ancestor of the previous ancestor
		tree[cur_node].ancestor[i] = tree[ tree[cur_node].ancestor[i-1] ].ancestor[i-1];
	}
	for (int &nxt : employee[cur_node]) {
		build_node(nxt, cur_depth + 1);
	}
}

...
int main() {
	powers_2[0] = 1;
	for (int i =1 ;i < 19; i++) {
		powers_2[i] = 2*powers_2[i-1];
	}

	build_node(0, 0);
	for (int i= 0 ; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		if (tree[a].depth > tree[b].depth) a = get_ancestor(a, tree[a].depth - tree[b].depth);
		else b = get_ancestor(b,tree[b].depth - tree[a].depth);
		cout << get_common(a , b) + 1 << "\n";
	}
}
```
***

## DSU
```C++
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}
```
***

## Strongly Connected Componenents
*The crucial **invariant property is that a node remains on the stack after it has been visited if and only if there exists a path in the input graph from it to some node earlier on the stack**. In other words, it means that in the DFS a node would be **ONLY removed from the stack after all its connected paths have been traversed**. When the DFS will backtrack it would remove the nodes on a single path and return to the root in order to start a new path.*

```
algorithm tarjan is
    input: graph G = (V, E)
    output: set of strongly connected components (sets of vertices)
   
    index := 0
    S := empty stack
    for each v in V do
        if v.index is undefined then
            strongconnect(v)
   
    function strongconnect(v)
        // Set the depth index for v to the smallest unused index
        v.index := index
        v.lowlink := index
        index := index + 1
        S.push(v)
        v.onStack := true
      
        // Consider successors of v
        for each (v, w) in E do
            if w.index is undefined then
                // Successor w has not yet been visited; recurse on it
                strongconnect(w)
                v.lowlink := min(v.lowlink, w.lowlink)
            else if w.onStack then // If w is not on stack, then (v, w) is an edge pointing to an SCC already found and must be ignored
                // Successor w is in stack S and hence in the current SCC
		// this means (v, w) is a cycle. But we haven't returned to w yet, so low[w] hasn't been set => w.index is the correct one.
		// as there could be multiple edges starting v which leads to a cycle, we take the min.
                v.lowlink := min(v.lowlink, w.index)
      
        // If v is a root node, pop the stack and generate an SCC
        if v.lowlink = v.index then
            start a new strongly connected component
            repeat
                w := S.pop()
                w.onStack := false
                add w to current strongly connected component
            while w ≠ v
            output the current strongly connected component
```

Checking if every vertex is reachable from each other:
```C++
// https://open.kattis.com/problems/onewayroads?tab=metadata


/*
https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

The idea is that if for an edge (v,u), if index[v] < low[u], then it means that
a path starting at u doesn't loop/go to any earlier node, which means that it's a 
dead end so the answer is NO.

*/
vector<vector<bool>>edge;
vector<int>low;
vector<int>idx;
int n, m;
static int t = 0; // time each node is visited

void dfs(int node, int par) {
	idx[node] = low[node] = t++;
	for (int i = 0 ;i < n; i++) {
		if (edge[node][i] == true) {
			edge[i][node] = false;
			if (i == par) continue;
			
			if (idx[i] == -1) {	// node hasn't been visited  yet
				dfs(i, node);
				low[node] = min(low[node], low[i]);
			}
			else {					// "already visited" == "found a loop"
				low[node] = min(low[node], idx[i]);	// there could be multiple loops, find the earliest one.
													// not using low[i] here because we haven't returned to i yet, so low[i] hasn't been updated
			}
			if (idx[node] < low[i]) {	// explained at the header
				cout << "NO\n";
				exit(0);
			}
		}
	}
}

int main () {
	cin >> n >> m;
	edge.assign(n, vector<bool>(n, false));
	low.resize(n);
	idx.assign(n, -1);
	for (int i = 0 ;i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;b--;
		edge[a][b] = true;
		edge[b][a] = true;
	}
	dfs(0, -1);
	cout << "YES\n";
	for (int i = 0 ;i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (edge[i][j]) cout << i + 1 << " " << j + 1 << "\n";
		}
	}
}

```


