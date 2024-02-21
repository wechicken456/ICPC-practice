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
### Maximum flow (Dinic)
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
### Min cut (Dinic)
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

### Maximum number of disjoint paths
Find all paths from `1` to `n` such that each vertex appears only in 1 path. Edges have unit capacity.

Using **Edmond-Karps algorithm**, we can find the max flow which is the number of disjoint paths. 

To construct the paths: when we update the flow in the inner while loop, if the current edge used to push the flow is a valid edge (not a reversed edge), then we set `succ[prev][cur]`
to `true`, where `
