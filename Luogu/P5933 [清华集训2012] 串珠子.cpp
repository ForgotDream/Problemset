/*
 * @file    P5933 [清华集训2012] 串珠子.cpp
 * @author  ForgotDream
 * @brief   DP on Subset
 * @date    2024-01-04
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 16, mod = 1e9 + 7;
int n, a[N][N];

i64 f[1 << N], g[1 << N];

void solve() {
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) std::cin >> a[i][j];
  }

  int mask = (1 << n) - 1;
  for (int st = 0; st <= mask; st++) {
    f[st] = 1;
    for (int i = 0; i < n; i++) {
      if (!(st & (1 << i))) continue;
      for (int j = i + 1; j < n; j++) {
        if (!(st & (1 << j))) continue;
        f[st] = f[st] * (a[i][j] + 1) % mod;
      }
    }
  }

  for (int st = 0; st <= mask; st++) {
    g[st] = f[st];
    int lst = st ^ (st & -st);  // 随便去掉一个点
    for (int sub = lst; sub; sub = (sub - 1) & lst) {
      g[st] = (g[st] - f[sub] * g[st ^ sub] % mod + mod) % mod;
    }
  }
  std::cout << g[mask] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
