/**
 * @file    CF305B Continued Fractions.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-30
 */
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 100;
i64 p, q, n, a[N];
void shrink(i64 &a, i64 &b) {
  auto d = std::gcd(a, b);
  a /= d, b /= d;
}
void solve() {
  std::cin >> p >> q >> n;
  shrink(p, q);
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  i64 up = a[n], dwn = 1;
  for (int i = n - 1; i >= 1; i--) {
    shrink(up, dwn);
    std::swap(up, dwn);
    up = a[i] * dwn + up;
  }
  if (p == up && q == dwn) std::cout << "YES\n";
  else std::cout << "NO\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}