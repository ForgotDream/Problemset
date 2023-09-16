/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-09-16
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
