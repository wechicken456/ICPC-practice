// 2nd method to solve intercept. CHeck intercept1 for explanation of other methods

// The 2nd way to solve this is to use the REVERSE topological sort of the graph
// Thinking of the graph as a network flow in the reverse topological sort, 
// starting from t with flow 1, we split the flow evenly between the parents 
// (on the shortest paths) of the current node
// Then, a node is an articulation point (in our answer) ONLY if the network flow
// to it is equal to 1
// If there was another branch that goes beyond this node, then the flow will be
// splitted into that branch and the flow s`um of this node will not add up to 1
	
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define ll long long
#define pb push_back

using namespace std;
ll n, m, s, t;
vector<vector<pair<ll, ll>>> adj(100001);
vector<vector<pair<ll, ll>>> re_adj(100001);	// for reverese graph
vector<ll> dist(100001, 1e18);
vector<ll> re_dist(100001, 1e18); //	for reverse graph
vector<vector<ll>> parent(100001);
vector<bool> visited(100001, false);
vector<int> ans;
//vector<int> flow(100001, 0);

void dijkstra(int start, int dest, vector<vector<pair<ll, ll>>> &edge, vector<ll> &distance) {
  priority_queue<pair<ll, pair<ll, ll>>> pq;
  distance[start] = 0;
  pq.push({0, {start, start}});
  while (!pq.empty()) {
    ll d = abs(pq.top().first);
    ll node = pq.top().second.first;
    ll par = pq.top().second.second;

    pq.pop();

    if (d != distance[node]) {
      continue;
    }

    for (auto &p : edge[node]) {
      if (p.second != par) {
        if (d + p.first > distance[dest]) // if distance from s to the current node is
                                   // greater than dist[t]
          continue;

        if (d + p.first == distance[p.second]) {
          parent[p.second].pb(node);
        } else if (d + p.first < distance[p.second]) {
          parent[p.second].clear();
          parent[p.second].pb(node);
          distance[p.second] = d + p.first;
          pq.push({-distance[p.second], {p.second, node}});
        }
      }
    }
  }
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;

	ll a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		adj[a].pb({c, b});
	}
	cin >> s >> t;
	dijkstra(s, t, adj, dist);
	
	topological_sort();
	
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}
