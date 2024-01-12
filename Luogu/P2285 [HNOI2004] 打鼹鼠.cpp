/*
 * @file    P2285 [HNOI2004] 打鼹鼠.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int M = 10050;

int n, m;
int f[M], t[M], x[M], y[M];

void solve() {
  std::cin >> n >> m;

  for (int i = 1; i <= m; i++) {
    std::cin >> t[i] >> x[i] >> y[i];
    
    f[i] = 1;
    for (int j = 1; j < i; j++) {
      if (t[i] - t[j] >= std::abs(x[i] - x[j]) + std::abs(y[i] - y[j])) {
        f[i] = std::max(f[i], f[j] + 1);
      }
    }
  }

  std::cout << *std::max_element(f + 1, f + m + 1) << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
