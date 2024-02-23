// by tmt514
#include <bits/stdc++.h>
using namespace std;

int main() {
  int A, L, total = 0;
  for (int i = 0; i < 5; i++) {
    cin >> A >> L;
    total += A * L;
  }
  int N, KWF;
  cin >> N >> KWF;
  cout << total * N / 5 / KWF << endl;
  return 0;
}
