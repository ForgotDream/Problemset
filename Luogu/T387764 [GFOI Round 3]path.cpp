/**
 * @file    T387764 [GFOI Round 3]path.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-10-13
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 5e3 + 50;
int n, m;
std::vector<pii> adj[N];
int fa[N];
bool vis[N], used[N];
bool visp[N];
int tot, cnt;
void dfs(int u, int frm) {
  visp[u] = true;
  tot++;
  for (auto [v, i] : adj[u]) {
    if (i == frm) continue;
    if (visp[v]) {
      if (!vis[i]) {
        int p = u;
        for (; p != fa[v]; p = fa[p]) {
          if (!used[p]) used[p] = true, cnt++;
        }
        vis[i] = true;
      }
      continue;
    }
    fa[v] = u, vis[i] = true, dfs(v, i);
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
  }
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    if (visp[i]) continue;
    tot = cnt = 0;
    dfs(i, 0);
    ans += 1ll * (tot - 1) * cnt;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
