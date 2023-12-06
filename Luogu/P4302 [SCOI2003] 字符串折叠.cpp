/**
 * @file    P4302 [SCOI2003] 字符串折叠.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-12-03
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 105;
std::string s;
int n, f[N][N];
int calc(int l, int r) {
  int len = r - l + 1, res = len;
  for (int i = 1; i < len; i++) {
    if (len % i != 0) continue;
    bool flg = true;
    for (int j = 0; j < len - i; j++) {
      if (s[l + j] != s[l + j + i]) {
        flg = false;
        break;
      }
    }
    if (flg) res = std::min(res, int(std::log10(len / i)) + 3 + f[l][l + i - 1]);
  }
  return res;
}
void solve() {
  std::cin >> s, n = s.length(), s = " " + s;
  for (int i = 1; i <= n; i++) f[i][i] = 1;
  for (int len = 2; len <= n; len++) {
    for (int l = 1; l <= n - len + 1; l++) {
      int r = l + len - 1;
      f[l][r] = calc(l, r);
      for (int k = l; k < r; k++) {
        f[l][r] = std::min(f[l][r], f[l][k] + f[k + 1][r]);
      }
    }
  }
  std::cout << f[1][n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
