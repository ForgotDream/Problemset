/**
 * @file    P1764 翻转游戏 (加强版).cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-12
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 17;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, a[N][N], tmp[N][N];
void cpy() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) tmp[i][j] = a[i][j];
  }
}
bool valid(int i, int j) { return 1 <= i && i <= n && 1 <= j && j <= n; }
void rotate(int i, int j) {
  for (int k = 0; k < 4; k++) {
    int dx = i + d[k][0], dy = j + d[k][1];
    if (!valid(dx, dy)) continue;
    tmp[dx][dy] ^= 1;
  }
  tmp[i][j] ^= 1;
}
int solve(int st) {
  int ans = 0x3f3f3f3f;
  for (int t = 0; t < 2; t++) {
    cpy();
    for (int i = 1; i <= n; i++) {
      if (st & (1 << (i - 1))) rotate(1, i);
    }
    int cur = __builtin_popcount(st);
    for (int i = 2; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (tmp[i - 1][j] != t) rotate(i, j), cur++;
      }
    }
    bool flg = true;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (tmp[i][j] != t) {
          flg = false;
          break;
        }
      }
    }
    if (flg) ans = std::min(ans, cur);
  }
  return ans;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      std::cin >> c;
      a[i][j] = c == 'b';
    }
  }
  int mask = (1 << n) - 1, ans = 0x3f3f3f3f;
  for (int i = 0; i <= mask; i++) ans = std::min(ans, solve(i));
  if (ans == 0x3f3f3f3f) std::cout << "Impossible\n";
  else std::cout << ans << "\n";
  return 0;
}