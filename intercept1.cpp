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
//vector<vector<ll>> parent(100001);
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

        if (d + p.first < distance[p.second]) {
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
		re_adj[b].pb({c, a});
	}
	cin >> s >> t;
	dijkstra(s, t, adj, dist);
	dijkstra(t, s, re_adj, re_dist);
	
	//fill(visited.begin(), visited.end(), false);
	priority_queue<pair<ll, ll>> pq;
	pq.push({0, s});
	visited[s] = true;
	while (!pq.empty()) {
		int node = pq.top().second;
		ll d = abs(pq.top().first);
		pq.pop();
		
		if (pq.empty()) ans.pb(node);
		
		for (auto &p : adj[node]) {
			if (!visited[p.second]) {
				ll w = p.first;
				ll nxt = p.second;
				if (d + w + re_dist[nxt] == dist[t]) {
					pq.push({-dist[nxt], nxt});	// d + w is dist[nxt] anyway
					visited[nxt] = true;
				}
			}
		}
	} 		
	// now, from here, there are 3 ways to solve this problem:
	// 1st: create a reverse Dijkstra from t to s.
	// Then do another Dijkstra from s to t, only pushing distances from s to q node onto pq 
	// if that distance + distance from node to t = min dist from s to t
	// Also, we don't visit a node anymore if it has been popped from pq and considered (similar to dijkstra)
	// That is, we only push nodes that are on the shortest paths.
	// Then, a node is an articulation point (in our answer) ONLY when all the distances in pq belong to the same node
	// Because this tells us that all the branches before this node all lead to this node. 
	// If there was another branch that goes beyond this node, then its distance will be in the pq.
	
	// The 2nd way to solve this is to use the REVERSE topological sort of the graph
	// Thinking of the graph as a network flow in the reverse topological sort, 
	// starting from t with flow 1, we split the flow evenly between the parents 
	// (on the shortest paths) of the current node
	// Then, a node is an articulation point (in our answer) ONLY if the network flow
	// to it is equal to 1
	// If there was another branch that goes beyond this node, then the flow will be
	// splitted into that branch and the flow s`um of this node will not add up to 1
	
	sort(ans.begin(), ans.end());
	
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}
