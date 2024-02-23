#include <bits/stdc++.h>
using namespace std;

int main() {
  string S;
  cin >> S;
  int m = S.size();
  // check first.
  if (S.back() != 'O') {
    cout << "INVALID" << endl;
    return 0;
  }
  for (int i = 0; i < m-1; i++) {
    if (S[i] == 'O' && S[i+1] == 'O') {
      cout << "INVALID" << endl;
      return 0;
    }
  }
  // now solve the problem.
  for (long long v = 1; v <= (1LL<<47); v++) {
    long long u = v;
    for (int i = 0; i < m; i++) {
      // check power of two.
      if ((u&-u) == u) { u=-1; break; }
      
      // 
      if ((S[i] == 'O') ^ (u%2==1)) {
        u = -1; break;
      }
        
      if (u%2) u=3*u+1;
      else u/=2;
    }
    if (u != -1 && (u&-u)==u) {
      cout << v << endl;
      return 0;
    }
  }
  assert(false);
  return 0;
}
