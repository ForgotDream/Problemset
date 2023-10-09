/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-09
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1050, B = 7;
int n, a[N], b[N];
int f[N][1 << B];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
