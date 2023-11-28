/**
 * @file    P1265 公路修建.cpp
 * @author  ForgotDream
 * @brief   Prim
 * @date    2023-11-26
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f64 = double;

constexpr int N = 5050;
int n, x[N], y[N];
f64 f[N];
bool used[N];
inline f64 dis(int u, int v) { return std::hypot(x[u] - x[v], y[u] - y[v]); }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i], f[i] = 1e18;
  f[1] = 0, used[1] = true;
  f64 ans = 0;
  int p = 1;
  for (int i = 1; i <= n; i++) {
    f64 mn = 1e18;
    for (int j = 1; j <= n; j++) if (!used[j] && f[j] < mn) p = j, mn = f[j];
    ans += f[p], used[p] = true;
    for (int j = 1; j <= n; j++) if (!used[j] && dis(p, j) < f[j]) f[j] = dis(p, j);
  }
  std::cout << std::fixed << std::setprecision(2) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
