/**
 * @file    CF813D Two Melodies.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-31
 */
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

inline int chkmax(int &a, const int &b) { return a = (a > b) ? a : b; }

using i64 = long long;

constexpr int N = 5050, M = 1e5 + 50;
int n, a[N], f[N][N];
int val[M], rst[7];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    std::memset(val, 0, sizeof(val)), std::memset(rst, 0, sizeof(rst));
    for (int j = 1; j < i; j++) chkmax(val[a[j]], f[j][i]), chkmax(rst[a[j] % 7], f[j][i]);
    for (int j = i + 1; j <= n; j++) {
      f[i][j] = std::max({f[i][0], val[a[j] + 1], val[a[j] - 1], rst[a[j] % 7]}) + 1, f[j][i] = f[i][j];
      chkmax(val[a[j]], f[i][j]), chkmax(rst[a[j] % 7], f[i][j]), chkmax(ans, f[i][j]);
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
