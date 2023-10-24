/**
 * @file    P3265 [JLOI2015] 装备购买.cpp
 * @author  ForgotDream
 * @brief   Linear Basis
 * @date    2023-08-27
 */
#include <algorithm>
#include <cmath>
#include <iostream>

using i64 = long long;
using f80 = long double;

constexpr int N = 550;
constexpr f80 eps = 1e-8;
int n, m;
struct Node {
  f80 a[N];
  int c;
  bool operator<(const Node &rhs) const { return c < rhs.c; }
} a[N];
int p[N];
int cnt, ans;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) std::cin >> a[i].a[j];
  }
  for (int i = 1; i <= n; i++) std::cin >> a[i].c;
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (std::fabs(a[i].a[j]) <= eps) continue;
      if (!p[j]) {
        p[j] = i;
        cnt++, ans += a[i].c;
        break;
      }
      f80 d = a[i].a[j] / a[p[j]].a[j];
      for (int k = j; k <= m; k++) a[i].a[k] -= d * a[p[j]].a[k];
    }
  }
  std::cout << cnt << " " << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}