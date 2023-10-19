/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-19
 */
#include <iostream>
#include <iomanip>

using i64 = long long;
using f80 = long double;

constexpr int N = 105;
int n, m, sx, sy, tx, ty;
int a[N][N];
f80 s;
void solve() {
  std::cin >> n >> m >> sx >> sy >> tx >> ty;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) std::cin >> a[i][j];
  }
  std::cin >> s;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
