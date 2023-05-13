#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n ,q;
  std::cin >> n >> q;

  std::vector<int> a(n), k(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < q; i++) {
    std::cin >> k[i];
  }

  std::sort(a.begin(), a.end());

  for (int i = 0; i < q; i++) {
    
  }

  return 0;
}