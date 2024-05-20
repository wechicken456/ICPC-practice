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

void solve() {
	
}

typedef struct {
	int cur_ans;
	int t, s;
	int diff_t, diff_s;
} node;

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	int n;
	cin >> n;
	
	
	// separation between each line = a*t + b*s
	// v[i].first = a
	// v[i].second = b
	vector<pair<int ,int>>v(n, {0, 0});
	vector<bool>is_open(n, false);
	
	for (int i = 0 ; i < n; i++) {
		string s; 
		cin >> s;
		for (int j = 0 ; j < s.length(); j++) {
			if (s[j] == 't') v[i].first++;
			else if (s[j] == 's') v[i].second++;
			else if (s[j] == '{') is_open[i] = true;
		}
	}

	vector<int>levels(n,0);
	int cur_ans = 0;
	// the indentation we have to match
	// each node on the stack has {last node's `a`, last node's `b`, diff of `a` between last node and the second last node, diff of `b` between last node and the second last node}
	stack<node>s; 
	s.push({0, 0, 0, 0, 0});
	
	
	for (int i = 1 ; i < n; i++) {
		
		//cout << i << ": " << cur_ans << "\n";
		// we have found an answer for `a`. compute the indentation amount for each level.
		if (cur_ans > 0) {
			// find the first indented line, that's our indentation amount.
			int sep = 0;
			for (int j = 0 ; j < n; j++) {
				if (v[j].first != 0 || v[j].second != 0) {
					sep = cur_ans*v[j].first + v[j].second;
					break;
				}
			}
			for (int k = 0 ; k < n;k++) {
				levels[k] = k*sep;
			}
			break;
		}
		
		if (is_open[i] == false) {
			
			// we're closing against the outer-most curly
			if (s.size() == 1) {
				if (v[i].first != 0 || v[i].second != 0) {
					cur_ans = -1;
					break;
				}
				s.pop();
				continue;
			}
			
			node &last = s.top();
			int diff_s = v[i].second - last.s;
			int diff_t = v[i].first - last.t;

			// since we're processing a closing curly, the top node on the stack must be an opening curly 
			// this means they have the same indentation amount
			// if one diff is 0, the other diff must also be 0
			if ( (diff_t == 0 && diff_s != 0) || (diff_s == 0 && diff_t != 0) ) {
				cur_ans = -1;
				break;
			}
			
			if (diff_t == 0 && diff_s == 0) {
				s.pop();
				continue;
			}
			
			// `a` must be a whole number
			if (diff_s % diff_t != 0) {
				cur_ans = -1;
				break;
			}
			
			// `a` > 0
			if ( (double)diff_s  / (-diff_t) < 0) {
				cur_ans = -1;
				break;
			}
			
			int tmp = diff_s / (-diff_t);
			if (cur_ans == 0) {
				cur_ans = tmp;
			}
			else if (cur_ans != tmp) {	// the required indentation here != already found amount => invalid
				cur_ans = -1;
				break;
			}
			s.pop();
		}
		else {	
			if (s.size() == 0) {
				if (v[i].first != 0 || v[i].second != 0) {
					cur_ans = -1;
					break;
				}
				s.push({cur_ans, 0, 0, 0, 0});
				continue;
			}
			else if (s.size() == 1) {
				s.push({cur_ans, v[i].first, v[i].second, v[i].first, v[i].second});
				continue;
			}
			
			// difference of `a` and `b` between the current and last node.
			node &last = s.top();
			int diff_s = v[i].second - last.s;
			int diff_t = v[i].first - last.t;
			
			if ( (diff_t == last.diff_t && diff_s != last.diff_s) || (diff_s == last.diff_s && diff_t != last.diff_t) ) {
				cur_ans = -1;
				break;
			}

			if (diff_t == diff_s) {
				s.push(last);
				continue;
			}
			
			int w = diff_s - last.diff_s;
			int z = last.diff_t - diff_t;
			
			if (z == 0 && w != 0) {
				cur_ans = -1;
				break;
			}
			else if (z == 0 && w == 0) {
				s.push({cur_ans, v[i].first, v[i].second, diff_t, diff_s});
				continue;
			}
			
			if (w % z != 0) {
				cur_ans = -1;
				break;
			}
			
			if ( (double)w  / z < 0) {
				cur_ans = -1;
				break;
			}
			
			int tmp = w / z;
			if (cur_ans == 0) {
				cur_ans = tmp;
			}
			else if (cur_ans != tmp) {
				cur_ans = -1;
				break;
			}
			s.push({cur_ans, v[i].first, v[i].second, diff_t, diff_s});
		}
	}
	
	if (cur_ans == -1) {
		cout << "-1\n";
		return 0;
	}
	else if (cur_ans == 0) {
		cout << "1\n";
		return 0;
	}
	
	// loop through each line and check its indentation
	int depth = 0;
	for (int i = 0 ; i < n;i++) {
		if (is_open[i]) {
			if (cur_ans * v[i].first + v[i].second != levels[depth]) {
				cout << "-1\n";
				return 0;
			}
			depth++;
		}
		else {
			if (cur_ans * v[i].first + v[i].second != levels[depth - 1]) {
				cout << "-1\n";
				return 0;
			}
			depth--;
		}

	}
	
	cout << cur_ans << "\n";
	return 0;
}


