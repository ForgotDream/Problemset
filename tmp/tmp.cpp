/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-23
 */
#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, m, p[N], a[N], b[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  for (int i = 1; i <= m; i++) std::cin >> a[i] >> b[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
