#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, k;
  std::cin >> n >> k;
  int cur = 4 * n * n - 4 * 2 * (n * n - n - 2 * k);
  int sqr = std::sqrt(cur);
  if (sqr * sqr == cur) {
    if ((2 * n + sqr) % 4 != 0) {
      std::cout << "NO\n";
    } else {
      int ans = (2 * n + sqr) / 4;
      std::cout << "YES\n";
      for (int i = 1; i <= n; i++) {
        if (i <= ans) {
          std::cout << 1 << " ";
        } else {
          std::cout << -1 << " ";
        }
      }
      std::cout << "\n";
    }
  } else {
    std::cout << "NO\n";
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