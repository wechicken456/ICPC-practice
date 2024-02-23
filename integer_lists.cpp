#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s;
  cin >> s;
  int n;
  cin >> n;
  if (cin.peek() == '\n')
    cin.ignore();
  char c;
  cin >> c;
  vector<int> a(n);
  int i = 0;
  string num = "";
  while (c != ']') {
    cin >> c;
    // cout << c << "-\n";
    if (c == ']')
      break;
    while (c != ',' && c != ']') {
      num.push_back(c);
      cin >> c;
    }
    // cout << num << "\n";
    a[i] = stoi(num);
    i++;
    num.clear();
  }
  
  int l = 0;
  int r = n - 1;
  bool reversed = false;
  for (i = 0 ; i < s.length(); i++) {
	  if (s[i] == 'R') reversed = !reversed;
	  else {		// case drop
		  if (r - l < 0) {
				  cout << "error\n";
				  return;
		  }
		  if (reversed) {
			r--;
		  }
		  else {
			l++;
		  }
	  }
  }
  
  if (r - l < 0) {
	  cout << "[]\n";
	  return;
  }
  cout << "[";
  if (!reversed) {
	  for (i = l; i <= r - 1; i++) {
		cout << a[i] << ",";
	  }
	  cout << a[r];
  }
  else {
	  for (i = r; i >= l + 1; i--) {
		cout << a[i] << ",";
	  }
	  cout << a[l];
  }
  cout << "]\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}
