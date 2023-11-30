/**
 * @file    P3194 [HNOI2008] 水平可见直线.cpp
 * @author  ForgotDream
 * @brief   Half-plane Intersection + Convex Hull
 * @date    2023-11-29
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f64 = double_t;

constexpr int N = 5e4 + 50;
int n, a[N], b[N], p[N];
int s[N], top, ans[N];
inline f64 slope(int u, int v) { return f64(b[u] - b[v]) / (a[v] - a[u]); }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
  std::iota(p + 1, p + n + 1, 1);
  std::sort(p + 1, p + n + 1, [&](int lhs, int rhs) {
    return a[lhs] > a[rhs] || (a[lhs] == a[rhs] && b[lhs] > b[rhs]);
  });
  for (int i = 1; i <= n; i++) {
    int u = p[i], v = p[i - 1];
    if (a[u] == a[v] && i != 1) continue;
    while (top > 1 && slope(s[top], u) >= slope(s[top], s[top - 1])) top--; 
    s[++top] = u, ans[top] = u;
  }
  std::sort(ans + 1, ans + top + 1);
  for (int i = 1; i <= top; i++) std::cout << ans[i] << " ";
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
