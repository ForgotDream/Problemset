#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 20;

int n, m, k;
int col[N][N], row[N][N];

void solve() {
  std::cin >> n >> m >> k;

  if (k < n + m - 2) return std::cout << "NO\n", void();

  int d = k / (n + m - 2), r = k % (n + m - 2);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      col[i][j] = col[i][j - 1] ^ 1;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
