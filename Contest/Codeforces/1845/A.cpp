#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

void solve() {
  int n, k, x;
  std::cin >> n >> k >> x;

  if (x != 1) {
    std::cout << "YES\n";
    std::cout << n << "\n";
    while (n--) {
      std::cout << 1 << " ";
    }
    std::cout << "\n";
    return;
  }

  std::vector f(k + 1, std::vector<int>(n + 1, inf));
  f[0][0] = 0;
  for (int i = 2; i <= k; i++) {
    for (int j = i; j <= n; j++) {
      f[i][j] = std::min(f[i - 1][j], f[i][i - j] + j);
    }
  }

  if (f[k][n] == inf) {
    std::cout << "NO\n";
  } else {
    std::cout << f[k][n] << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}