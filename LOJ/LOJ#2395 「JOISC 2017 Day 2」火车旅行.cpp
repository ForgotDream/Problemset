/**
 * @file    LOJ#2395 「JOISC 2017 Day 2」火车旅行.cpp
 * @author  ForgotDream
 * @brief   倍增优化 DP
 * @date    2023-10-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k ,q;
int l[N];
std::stack<int, std::vector<int>> s;
int f[21][N], g[21][N];
void solve() {
  std::cin >> n >> k >> q;
  for (int i = 1; i <= n; i++) std::cin >> l[i];
  s.push(1);
  for (int i = 1; i <= n; i++) {
    while (!s.empty() && l[s.top()] < l[i]) s.pop(); 
    f[0][i] = s.top(), s.push(i);
  }
  while (!s.empty()) s.pop();
  s.push(n);
  for (int i = n; i >= 1; i--) {
    while (!s.empty() && l[s.top()] < l[i]) s.pop();
    g[0][i] = s.top(), s.push(i);
  }
  for (int i = 1; i <= 17; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = std::min(f[i - 1][f[i - 1][j]], f[i - 1][g[i - 1][j]]);
      g[i][j] = std::max(g[i - 1][g[i - 1][j]], g[i - 1][f[i - 1][j]]);
    }
  }
  for (int i = 1, u, v, l, r; i <= q; i++) {
    std::cin >> u >> v;
    if (u > v) std::swap(u, v);
    i64 ans = 0;
    l = r = u;
    for (int j = 17; ~j; j--) {
      int nxtl = std::min(f[j][l], f[j][r]), nxtr = std::max(g[j][l], g[j][r]);
      if (nxtr < v) {
        l = nxtl, r = nxtr;
        ans += (1 << j);
      }
    }
    u = r;
    l = r = v;
    for (int j = 17; ~j; j--) {
      int nxtl = std::min(f[j][l], f[j][r]), nxtr = std::max(g[j][l], g[j][r]);
      if (nxtl > u) {
        l = nxtl, r = nxtr;
        ans += (1 << j);
      }
    }
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
