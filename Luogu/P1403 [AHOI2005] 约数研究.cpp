/**
 * @file    P1403 [AHOI2005] 约数研究.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e6 + 50;
int n, d[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) d[j]++;
  }
  std::cout << std::accumulate(d + 1, d + n + 1, 0ll) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
