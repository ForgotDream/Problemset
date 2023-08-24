/**
 * @file    CF346B Lucky Common Subsequence.cpp
 * @author  ForgotDream
 * @brief   String + DP
 * @date    2023-08-24
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 105;
std::string a, b, c, f[N][N][N];
int nxt[N];
void chkmax(std::string &lhs, std::string rhs) {
  if (lhs.length() < rhs.length()) lhs = rhs;
}
void solve() {
  std::cin >> a >> b >> c;
  for (int i = 1; i < c.length(); ++i) {
    int j = nxt[i - 1];
    while (j > 0 && c[i] != c[j]) j = nxt[j - 1];
    if (c[i] == c[j]) ++j;
    nxt[i] = j;
  }
  for (int i = 1; i <= a.length(); ++i) {
    for (int j = 1; j <= b.length(); ++j) {
      for (int k = 0; k < c.length(); ++k) {
        if (a[i - 1] == b[j - 1]) {
          char cur = a[i - 1];
          int p = k;
          while (p > 0 && cur != c[p]) p = nxt[p - 1];
          if (c[p] == cur) ++p;
          chkmax(f[i][j][p], f[i - 1][j - 1][k] + cur);
        }
        chkmax(f[i][j][k], f[i][j - 1][k]);
        chkmax(f[i][j][k], f[i - 1][j][k]);
      }
    }
  }
  std::string ans;
  for (int i = 0; i < c.length(); i++) chkmax(ans, f[a.length()][b.length()][i]);
  if (ans.empty()) std::cout << 0 << "\n";
  else std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}