/**
 * @file    CF1662A Organizing SWERC.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-11-01
 */
#include <iostream>

using i64 = long long;

constexpr int N = 105;
int n, a[N];
void solve() {
  for (int i = 1; i <= 10; i++) a[i] = 0;
  std::cin >> n;
  for (int i = 1, t, v; i <= n; i++) {
    std::cin >> v >> t, a[t] = std::max(a[t], v);
  }
  int ans = 0;
  for (int i = 1; i <= 10; i++) {
    if (!a[i]) {
      std::cout << "MOREPROBLEMS\n";
      return;
    }
    ans += a[i];
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
