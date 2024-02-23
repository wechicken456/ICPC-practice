#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  vector<int> a(n), b(n);
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);
  b = a;
  sort(b.begin(), b.end());
  
  int ans = 0;
  vector<int> ret;
  int hash_a = 0, hash_b = 0;
  auto h = hash<unsigned int>{};

  for (int i = 0; i < n; i++) {
    if (a[i]==b[i] && (i==n-1 || b[i+1] != b[i]) && hash_a == hash_b) {
      ++ans;
      if (ret.size() < 100) {
        ret.push_back(a[i]);
      }
    }
    hash_a ^= h(a[i]);
    hash_b ^= h(b[i]);
  }

  printf("%d", ans);
  for (int x : ret) printf(" %d", x);
  puts("");
  return 0;
}
