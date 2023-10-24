/**
 * @file    CF611D New Year and Ancient Prophecy.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-09-07
 */
#include <string>
#include <iostream>

using i64 = long long;

constexpr int N = 5050, mod = 1e9 + 7;
int n;
std::string s;
int f[N][N], lcp[N][N], sum[N][N];
bool cmp(int x, int y) {
  if (lcp[x][y] >= y - x) return false;
  return s[x + lcp[x][y]] < s[y + lcp[x][y]];
}
void solve() {
  std::cin >> n >> s;
  s = '\0' + s;
  for (int i = n; i >= 1; i--) {
    for (int j = n; j >= 1; j--) {
      if (s[i] == s[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
    }
  }
  for (int i = 1; i <= n; i++) f[i][1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      if (s[j] == '0') continue;
      int k = std::max(1, 2 * j - i);
      f[i][j] += (sum[j - 1][j - 1] - sum[j - 1][k - 1] + mod) % mod;
      k--;
      if (cmp(k, j)) (f[i][j] += f[j - 1][k]) %= mod;
    }
    for (int j = 1; j <= i; j++) {
      sum[i][j] = (sum[i][j - 1] + f[i][j]) % mod;
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) (ans += f[n][i]) %= mod;
  std::cout << ans << "\n";
}

signed main() {
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}