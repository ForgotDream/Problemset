/**
 * @file    LOJ#2397 「JOISC 2017 Day 3」幽深府邸.cpp
 * @author  ForgotDream
 * @brief   DP + Brute Force
 * @date    2023-10-14
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 5e5 + 50;
int n, q, c[N];
std::vector<int> a[N];
int l[N], r[N], s[N], t[N];
bool vis[N];
int p[N];
void dfs(int u) {
  if (vis[u]) return;
  s[u] = t[u] = u, vis[u] = true;
  while (true) {
    int pl = s[u] - 1, pr = t[u] + 1;
    bool flg = false;
    if (r[pl] <= t[u]) {
      dfs(pl);
      if (s[pl] < s[u]) s[u] = s[pl], flg = true;
      if (t[pl] > t[u]) t[u] = t[pl], flg = true;
    }
    if (l[pr] >= s[u]) {
      dfs(pr);
      if (s[pr] < s[u]) s[u] = s[pr], flg = true;
      if (t[pr] > t[u]) t[u] = t[pr], flg = true;
    }
    if (!flg) break;
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i < n; i++) std::cin >> c[i];
  for (int i = 1, b; i <= n; i++) {
    std::cin >> b;
    for (int u; b; b--) std::cin >> u, a[i].push_back(u);
  }
  for (int i = 1; i < n; i++) {
    for (auto j : a[i]) p[j] = i;
    l[i + 1] = p[c[i]];
  }
  for (int i = 1; i <= n; i++) p[i] = n + 1;
  for (int i = n; i > 1; i--) {
    for (auto j : a[i]) p[j] = i;
    r[i - 1] = p[c[i - 1]];
  }
  r[0] = r[n + 1] = n + 1;
  for (int i = 1; i <= n; i++) dfs(i);
  std::cin >> q;
  for (int i = 1, u, v; i <= q; i++) {
    std::cin >> u >> v;
    if (s[u] <= v && v <= t[u]) std::cout << "YES\n";
    else std::cout << "NO\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
