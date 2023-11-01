/**
 * @file    CF845F Guards In The Storehouse.cpp
 * @author  ForgotDream
 * @brief   DP + DFS
 * @date    2023-11-01
 */
#include <cassert>
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 255, M = 15, mod = 1e9 + 7;
int n, m;
char s[N][N];
i64 f[N][1 << 15][2][2];
// f[pos][st][cover][hole]
i64 dfs(int x, int y, int st, bool cover, bool hole) {
  if (x == n) return 1;
  if (y == m) return dfs(x + 1, 0, st, false, hole);
  i64 &res = f[x * m + y][st][cover][hole];
  if (res != -1) return res;
  res = 0;
  if (s[x][y] == 'x') {
    res = dfs(x, y + 1, st & (~(1 << y)), false, hole);
  } else {
    if (cover || (st & (1 << y))) res = dfs(x, y + 1, st, cover, hole);
    res += dfs(x, y + 1, st | (1 << y), true, hole), res %= mod;
    if (!cover && !hole && !(st & (1 << y))) {
      res += dfs(x, y + 1, st, cover, true), res %= mod;
    }
  }
  return res;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 0; i < n; i++) std::cin >> s[i];
  if (n < m) {
    for (int i = 0; i < n; i++) {
      for (int j = i; j < m; j++) std::swap(s[i][j], s[j][i]);
    }
    std::swap(n, m);
  }
  assert(n >= m);
  std::memset(f, -1, sizeof(f));
  std::cout << dfs(0, 0, 0, false, false) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
