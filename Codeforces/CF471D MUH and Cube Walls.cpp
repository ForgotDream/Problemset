/*
 * @file    CF471D MUH and Cube Walls.cpp
 * @author  ForgotDream
 * @brief   KMP
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

int n, m, a[N], b[N];
int nxt[N];

void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i];

  if (m == 1) return std::cout << n << "\n", void();

  for (int i = n; i >= 1; i--) a[i] = a[i] - a[i - 1];
  for (int i = 1; i <= n; i++) a[i] = a[i + 1];
  n--;

  for (int i = m; i >= 1; i--) b[i] = b[i] - b[i - 1];
  for (int i = 1; i <= m; i++) b[i] = b[i + 1];
  m--;

  for (int i = 2, j = nxt[i - 1]; i <= m; i++) {
    while (j && b[i] != b[j + 1]) j = nxt[j];
    if (b[i] == b[j + 1]) j++;
    nxt[i] = j;
  }

  int j = 0, ans = 0;
  for (int i = 1; i <= n; i++) {
    while (j && a[i] != b[j + 1]) j = nxt[j];
    if (a[i] == b[j + 1]) j++;
    if (j == m) j = nxt[j], ans++;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
