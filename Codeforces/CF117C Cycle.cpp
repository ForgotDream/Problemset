/**
 * @file    CF117C Cycle.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-24
 */
#include <bitset>
#include <iostream>

using i64 = long long;

constexpr int N = 5050;
int n;
std::bitset<N> val[N];
int to[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      std::cin >> c;
      val[i][j] = c - '0';
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (val[i][j] && (!to[i] || val[j][to[i]])) to[i] = j;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (val[to[i]][j] && val[j][i]) {
        std::cout << i << " " << to[i] << " " << j << "\n";
        return;
      }
    }
  }
  std::cout << -1 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}