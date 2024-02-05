/*
 * @file    P1247 取火柴游戏.cpp
 * @author  ForgotDream
 * @brief   SG
 * @date    2024-02-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5e5 + 50;

int n, a[N];

void solve() {
  std::cin >> n;

  int s = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], s ^= a[i];

  if (!s) {
    std::cout << "lose\n";
    return;
  }

  for (int i = 1; i <= n; i++) {
    if ((s ^ a[i]) < a[i]) {
      std::cout << (a[i] - (s ^ a[i])) << " " << i << "\n";
      for (int j = 1; j <= n; j++) {
        if (i == j) std::cout << (s ^ a[j]) << " ";
        else std::cout << a[j] << " ";
      }
      std::cout << "\n";
      return;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
