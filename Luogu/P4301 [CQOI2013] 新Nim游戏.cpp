/**
 * @file    P4301 [CQOI2013] 新Nim游戏.cpp
 * @author  ForgotDream
 * @brief   Linear Basis
 * @date    2023-08-27
 */
#include <algorithm>
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;

namespace VECSPACE {
constexpr int N = 64;
u64 p[N];
bool insert(u64 val) {
  for (int i = 63; i >= 0; i--) {
    if (!(val & (1ll << i))) continue;
    if (!p[i]) {
      p[i] = val;
      break;
    }
    val ^= p[i];
  }
  return val == 0;
}
}
constexpr int N = 105;
int n, a[N], p[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1);
  i64 ans = 0;
  for (int i = n; i >= 1; i--) {
    if (VECSPACE::insert(a[i])) ans += a[i];
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}