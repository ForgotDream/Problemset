/*
 * @file    CF830A Office Keys.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-02-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2050;

int n, m, p, a[N], b[N];
i64 f[N][N];

void solve() {
  std::cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i];

  std::sort(a + 1, a + n + 1);
  std::sort(b + 1, b + m + 1);

  memset(f, 0x3f, sizeof(f));
  std::fill(f[0], f[0] + m + 1, 0);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      i64 w = std::abs(a[i] - b[j]) + std::abs(p - b[j]);
      f[i][j] = std::min(f[i][j - 1], std::max(f[i - 1][j - 1], w));
    }
  }

  std::cout << f[n][m] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
