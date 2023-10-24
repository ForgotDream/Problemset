/**
 * @file    UVA12230 Crossing Rivers.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <iostream>
#include <iomanip>

// using i64 = long long;
// using f80 = long double;
typedef long long i64;
typedef long double f80;

int t, n, D;

void solve(int t) {
  f80 ans = D;
  for (int i = 1; i <= n; i++) {
    int p, l, v;
    std::cin >> p >> l >> v;
    ans -= l;
    ans += 2. * l / v;
  }
  std::cout << "Case " << t << ": ";
  std::cout << ans << "\n\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout << std::fixed << std::setprecision(3);
  
  while (std::cin >> n >> D && (n || D)) solve(++t);

  return 0;
}