/**
 * @file    CF797D Broken BST.cpp
 * @author  ForgotDream
 * @brief   啥玩意啊
 * @date    2023-08-27
 */
#include <iostream>
#include <set>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, a[N], lc[N], rc[N];
std::set<int> s;
bool mark[N];
void dfs(int u, int l, int r) {
  if (u == -1) return;
  if (l < a[u] && a[u] < r) s.insert(a[u]);
  dfs(lc[u], l, std::min(r, a[u]));
  dfs(rc[u], std::max(l, a[u]), r);
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i] >> lc[i] >> rc[i];
  for (int i = 1; i <= n; i++) {
    if (lc[i] != -1) mark[lc[i]] = true;
    if (rc[i] != -1) mark[rc[i]] = true;
  }
  int rt = 1;
  for (int i = 1; i <= n; i++) {
    if (!mark[i]) {
      rt = i;
      break;
    }
  }
  dfs(rt, -1, 1e9 + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!s.count(a[i])) ans++;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}