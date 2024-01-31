/*
 * @file    P4562 [JXOI2018] 游戏.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e7 + 50, mod = 1e9 + 7;

int l, r, n;
bool vis[N];

void solve() {
  std::cin >> l >> r, n = r - l + 1;

  int ct = 0;
  for (int i = l; i <= r; i++) {
    if (vis[i]) continue;
    ct++;
    for (int j = i; j <= r; j += i) vis[j] = true;
  }

  i64 ans = ct;
  for (int i = 1; i <= n + 1; i++) {
    if (i != ct + 1) ans = ans * i % mod;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
