/**
 * @file    CF283B Cow Program.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50;
int n;
i64 a[N], f[N][2];
i64 calc(int u, int d) {
  if (u != 1) {
    if (f[u][d] != 0) return f[u][d];
    f[u][d] = -1;
  }
  int nxt = d ? u - a[u] : u + a[u];
  if (nxt <= 0 || nxt > n) return f[u][d] = a[u];
  if (nxt == 1) return f[u][d] = -1;
  i64 tmp = calc(nxt, d ^ 1);
  if (tmp == -1) return f[u][d] = -1;
  return f[u][d] = a[u] + tmp;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 2; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n - 1; i++) {
    a[1] = i;
    std::cout << calc(1, 0) << "\n";
  }
  return 0;
}