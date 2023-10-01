/**
 * @file    P6758 [BalticOI2013] Vim.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-09-17
 */
#include <cstring>
#include <iostream>

using i64 = long long;

void chkmin(int &a, int b) { a = a > b ? b : a; }

constexpr int N = 7e4 + 50, M = 15, inf = 1e9;
int n;
char s[N];
int f[N][M], g[N][M][M];
void solve() {
  std::cin >> n >> (s + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) ans += 2 * (s[i] == 'e');
  std::memset(f, 0x3f, sizeof(f));
  std::memset(g, 0x3f, sizeof(g));
  f[0][s[1] - 'a'] = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'e') {
      std::memcpy(f[i], f[i - 1], sizeof(f[i]));
      std::memcpy(g[i], g[i - 1], sizeof(g[i]));
      continue;
    }
    for (int j = 0; j <= 'k' - 'a'; j++) {
      f[i][j] = inf;
      if (j != s[i] - 'a' && s[i - 1] != 'e') f[i][j] = f[i - 1][j];
      chkmin(f[i][j], f[i - 1][s[i] - 'a'] + 2);
      if (j != s[i] - 'a') chkmin(f[i][j], g[i - 1][s[i] - 'a'][j]);
      chkmin(f[i][j], g[i - 1][s[i] - 'a'][s[i] - 'a'] + 2);
      for (int k = 0; k <= 'k' - 'a'; k++) {
        g[i][j][k] = inf;
        if (j != s[i] - 'a') chkmin(g[i][j][k], f[i - 1][j] + 3);
        chkmin(g[i][j][k], f[i - 1][s[i] - 'a'] + 5);
        if (j != s[i] - 'a' && k != s[i] - 'a')
          chkmin(g[i][j][k], g[i - 1][j][k] + 1);
        if (j != s[i] - 'a')
          chkmin(g[i][j][k], g[i - 1][j][s[i] - 'a'] + 3);
        if (k != s[i] - 'a')
          chkmin(g[i][j][k], g[i - 1][s[i] - 'a'][k] + 3);
        chkmin(g[i][j][k], g[i - 1][s[i] - 'a'][s[i] - 'a'] + 5);
      }      
    }
  }
  std::cout << f[n]['k' - 'a'] + ans - 2 << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
