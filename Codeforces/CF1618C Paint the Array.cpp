/**
 * @file    CF1618C Paint the Array.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-08
 */
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 105;
int n;
i64 a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  i64 gcd = 0;
  bool flg = true;
  for (int i = 1; i <= n; i += 2) gcd = std::gcd(gcd, a[i]);
  for (int i = 2; i <= n; i += 2) {
    if (a[i] % gcd == 0) {
      flg = false;
      break;
    }
  }
  if (flg) {
    std::cout << gcd << "\n";
    return;
  }
  gcd = 0;
  for (int i = 2; i <= n; i += 2) gcd = std::gcd(gcd, a[i]);
  for (int i = 1; i <= n; i += 2) {
    if (a[i] % gcd == 0) {
      std::cout << 0 << "\n";
      return;
    }
  }
  std::cout << gcd << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}