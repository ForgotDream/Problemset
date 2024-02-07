/*
 * @file    P3175 [HAOI2015] 按位或.cpp
 * @author  ForgotDream
 * @brief   FWT / FMT + Min-Max Inclusion-exclusion principle
 * @date    2024-02-07
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using f64 = double;

constexpr int N = 20;

int n;
f64 a[1 << N];

void solve() {
  std::cin >> n, n = (1 << n);
  for (int i = 0; i < n; i++) std::cin >> a[i];

  for (int h = 2; h <= n; h <<= 1) {
    for (int j = 0; j < n; j += h) {
      for (int k = j; k < j + (h >> 1); k++) {
        a[k + (h >> 1)] += a[k];
      }
    }
  }

  f64 ans = 0;
  for (int i = 1; i < n; i++) {
    int siz = __builtin_popcount(i);
    f64 cur = 1 - a[(n - 1) ^ i];
    if (cur < 1e-8) {
      std::cout << "INF\n";
      return;
    }
    cur = 1 / cur;
    ans += (siz & 1) ? cur : -cur;
  }

  std::cout << std::fixed << std::setprecision(10) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
