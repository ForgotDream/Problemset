/**
 * @file    CF1392F Omkar and Landslide.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-07-31
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n;
i64 s, h[N], ans[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> h[i], s += h[i];

  s -= 1ll * n * (n + 1) / 2;
  std::iota(ans, ans + N, 0);

  for (int i = 1; i <= n; i++) ans[i] += s / n;
  s -= (s / n) * n;

  int p = 1;
  while (s) {
    ans[p]++;
    p++, s--;
  }

  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];

  return 0;
}