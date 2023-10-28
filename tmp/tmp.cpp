/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-28
 */
#include <iostream>

using i64 = long long;

constexpr int N = 5050;
int n, m;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> n;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
