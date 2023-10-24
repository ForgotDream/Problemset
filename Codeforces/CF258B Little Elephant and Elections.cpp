/**
 * @file    CF258B Little Elephant and Elections.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 11, mod = 1e9 + 7;
int m;
int f[N][N], cnt[N], dig[N];
i64 dfs(int sum, int d) {
  if (d == 7) return 1;
  i64 res = 0;
  for (int i = 0; i < sum; i++) {
    if (!cnt[i]) continue;
    cnt[i]--;
    (res += dfs(sum - i, d + 1) * (cnt[i] + 1) % mod) %= mod;
    cnt[i]++;
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> m;
  int cpy = m, len = 0;
  while (cpy) dig[++len] = cpy % 10, cpy /= 10;
  f[1][0] = 8, f[1][1] = 2;
  for (int i = 2; i <= len; i++) {
    for (int j = 0; j <= i; j++) {
      if (j) f[i][j] += 2 * f[i - 1][j - 1];
      f[i][j] += 8 * f[i - 1][j];
    }
  }
  int c = 0;
  for (int i = len; i >= 1; i--) {
    for (int j = 0; j < dig[i]; j++) {
      int d = (j == 4 || j == 7);
      for (int k = 0; k + c + d < 10; k++) {
        (cnt[k + c + d] += f[i - 1][k]) %= mod;
      }
      if (i == 1) cnt[c + d]++;
    }
    c += (dig[i] == 4 || dig[i] == 7);
  }
  cnt[c]++, cnt[0]--;
  i64 ans = 0;
  for (int i = 1; i <= 9; i++) {
    if (cnt[i]) (ans += dfs(i, 1) * cnt[i] % mod) %= mod;
  }
  std::cout << ans << "\n";
  return 0;
}