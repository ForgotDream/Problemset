/**
 * @file    P1040 [NOIP2003 提高组] 加分二叉树.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 35;
int n, lc[N], rc[N];
i64 a[N], ans, f[N][N];
int solve(int l, int r) {
  if (l == r) return l;
  if (l == r - 1) return lc[l] = r, l;
  for (int k = l + 1; k < r; k++) {
    if (f[l][k - 1] * f[k + 1][r] + a[k] == f[l][r]) {
      lc[k] = solve(l, k - 1), rc[k] = solve(k + 1, r);
      return k;
    }
  }
  return l;
}
void print(int u) {
  if (!u) return;
  std::cout << u << " ";
  print(lc[u]), print(rc[u]);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) {
    f[i][i] = a[i];
    f[i][i + 1] = a[i] + a[i + 1];
  }
  for (int len = 3; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      for (int k = l + 1; k < r; k++) {
        f[l][r] = std::max(f[l][r], f[l][k - 1] * f[k + 1][r] + a[k]);
      }
    }
  }
  std::cout << f[1][n] << "\n";
  print(solve(1, n));
  std::cout << "\n";
  return 0;
}