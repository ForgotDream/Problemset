/**
 * @file    P2822 [NOIP2016 提高组] 组合数问题.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
using pii = std::pair<int, int>;
constexpr int N = 2050, M = 25;
int t, k, n, m;
int fac[N][M], cnt[N][N];
pii key[M];
int kcnt;
void solve() {
  std::cin >> n >> m;
  std::cout << cnt[n][std::min(n, m)] << "\n";
}
int calc(int num, int p) {
  int res = 0, cpy = p;
  for (; p <= num; p *= cpy) res += num / p;
  return res;
}
void init() {
  int cpy = k;
  for (int i = 2; i * i <= cpy; i++) {
    if (cpy % i == 0) {
      key[++kcnt].first = i;
      while (cpy % i == 0) cpy /= i, key[kcnt].second++;
    }
  }
  if (cpy != 1) key[++kcnt] = std::make_pair(cpy, 1);
  for (int i = 1; i <= 2000; i++) {
    for (int k = 1; k <= kcnt; k++) {
      fac[i][key[k].first] = calc(i, key[k].first);
    }
  }
  for (int i = 0; i <= 2000; i++) {
    for (int j = 0; j <= i; j++) {
      bool flg = true;
      for (int k = 1; k <= kcnt; k++) {
        auto [cur, ccnt] = key[k];
        if (fac[i][cur] - fac[j][cur] - fac[i - j][cur] < ccnt) {
          flg = false;
          break;
        }
      }
      if (flg) cnt[i][j] = 1;
      if (i) cnt[i][j] += cnt[i - 1][j];
      if (j) cnt[i][j] += cnt[i][j - 1];
      if (i && j) cnt[i][j] -= cnt[i - 1][j - 1];
    }
    for (int j = i + 1; j <= 2000; j++) {
      if (i) cnt[i][j] += cnt[i - 1][j];
      if (j) cnt[i][j] += cnt[i][j - 1];
      if (i && j) cnt[i][j] -= cnt[i - 1][j - 1];
    }
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t >> k;
  init();
  while (t--) solve();
  return 0;
}