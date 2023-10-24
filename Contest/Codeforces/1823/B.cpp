#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> p(n);
  std::vector<int> v;
  int illegal = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> p[i];
    if (std::abs(i - p[i] + 1) % k != 0) {
      illegal++;
      v.push_back(i);
    }
  }

  if (illegal >= 1) {
    if (illegal > 2) {
      std::cout << -1 << "\n";
    } else if (illegal == 2) {
      if (p[v[0]] % k == (v[1] + 1) % k && p[v[1]] % k == (v[0] + 1) % k) {
        std::cout << 1 << "\n";
      } else {
        std::cout << -1 << "\n";
      }
    }
  } else {
    std::cout << 0 << "\n";
  }

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}