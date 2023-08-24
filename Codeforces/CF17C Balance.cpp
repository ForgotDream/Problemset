/**
 * @file    CF17C Balance.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-24
 */
#include <iostream>

using i64 = long long;

constexpr int N = 160, mod = 51123987;
int n;
char s[N];
int nxt[N][3], f[N][N / 3][N / 3][N / 3];
void solve() {
  std::cin >> n >> (s + 1);
  for (int i = 0; i < 3; i++) nxt[n + 1][i] = n + 1;
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j < 3; j++) nxt[i][j] = nxt[i + 1][j];
    nxt[i][s[i] - 'a'] = i;
  }
  f[1][0][0][0] = 1;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int a = 0; a <= (n + 2) / 3; a++) {
      for (int b = 0; b <= (n + 2) / 3; b++) {
        for (int c = 0; c <= (n + 2) / 3; c++) {
          if (a + b + c == n && std::abs(a - b) <= 1 && std::abs(a - c) <= 1 &&
              std::abs(b - c) <= 1) {
            (ans += f[i][a][b][c]) %= mod;
          }
          (f[nxt[i][0]][a + 1][b][c] += f[i][a][b][c]) %= mod;
          (f[nxt[i][1]][a][b + 1][c] += f[i][a][b][c]) %= mod;
          (f[nxt[i][2]][a][b][c + 1] += f[i][a][b][c]) %= mod;
        }
      }
    }
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}