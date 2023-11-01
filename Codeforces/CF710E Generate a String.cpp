/**
 * @file    CF710E Generate a String.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-31
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e7 + 50;
int n, x, y;
i64 f[N];
void solve() {
  std::cin >> n >> x >> y;
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] + x;
    if (i % 2 == 0) f[i] = std::min(f[i], f[i / 2] + y);
    else f[i] = std::min(f[i], f[(i + 1) / 2] + y + x);
  }
  std::cout << f[n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
