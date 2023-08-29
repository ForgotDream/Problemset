/**
 * @file    P3812 【模板】线性基.cpp
 * @author  ForgotDream
 * @brief   线性空间
 * @date    2023-08-27
 */
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;

constexpr int N = 64;
int n;
u64 p[N];
void insert(u64 val) {
  for (int i = 63; i >= 0; i--) {
    if (!(val & (1ll << i))) continue;
    if (!p[i]) {
      p[i] = val;
      break;
    }
    val ^= p[i];
  }
}
void solve() {
  std::cin >> n;
  u64 cur;
  for (int i = 1; i <= n; i++) {
    std::cin >> cur;
    insert(cur);
  }
  u64 ans = 0;
  for (int i = 63; i >= 0; i--) ans = std::max(ans, ans ^ p[i]);
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