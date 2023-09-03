/**
 * @file    CF281B Nearest Fraction.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-02
 */
#include <cmath>
#include <iostream>
#include <numeric>

using i64 = long long;
using f80 = long double;

int a, y, n;
template<typename T>
void shrink(T &a, T &b) {
  auto d = std::gcd(a, b);
  a /= d, b /= d;
}
f80 up, dn, a = 1e18;
void solve() {
  std::cin >> a >> y >> n;
  shrink(a, y);
  if (y <= n) {
    std::cout << a << "/" << y << "\n";
    return;
  }
  f80 val = f80(a) / y;
  for (int i = 1; i <= n; i++) {
    f80 m1 = std::floor(val * i), m2 = std::ceil(val * i), m;
    if (val - m1 / i <= m2 / i - val) m = m1;
    else m = m2;
    f80 o = std::fabs(m / i - val);
    if (o < a) up = m, dn = i, a = o;
  }
  std::cout << i64(up + 0.5) << "/" << i64(dn + 0.5) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}