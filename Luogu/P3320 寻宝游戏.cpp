/**
 * @file    P3320 寻宝游戏.cpp
 * @author  ForgotDream
 * @brief   HLD + DFN
 * @date    2023-06-22
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  int clk = 0;
  std::vector<int> dfn(n), idfn(n);
  std::vector<i64> dis(n);
  std::vector<int> fa(n), siz(n), son(n, -1), dep(n);
  std::function<void(int, int)> dfs1 = [&](int u, int frm) {
    fa[u] = frm, dfn[u] = clk, idfn[clk++] = u, siz[u] = 1;
    dep[u] = dep[frm] + 1;
    for (auto i : adj[u]) {
      int v = i.first, w = i.second;
      if (v == frm) {
        continue;
      }
      dis[v] = dis[u] + w;
      dfs1(v, u);
      siz[u] += siz[v];
      if (son[u] == -1 || siz[v] > siz[son[u]]) {
        son[u] = v;
      }
    }
  };
  std::vector<int> top(n);
  std::function<void(int, int)> dfs2 = [&](int u, int rt) {
    top[u] = rt;
    if (son[u] != -1) {
      dfs2(son[u], rt);
    }
    for (auto i : adj[u]) {
      int v = i.first;
      if (v == fa[u] || v == son[u]) {
        continue;
      }
      dfs2(v, v);
    }
  };
  dfs1(0, 0), dfs2(0, 0);

  auto lca = [&](int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) {
        std::swap(u, v);
      }
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  };
  auto dist = [&](int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
  };

  std::vector<bool> used(n);
  std::set<int> s;
  i64 ans = 0;
  while (m--) {
    int u;
    std::cin >> u;
    u--;
    if (!used[u]) {
      s.insert(dfn[u]);
      auto l = s.lower_bound(dfn[u]), r = s.upper_bound(dfn[u]);
      l = std::prev(l == s.begin() ? s.end() : l);
      r = (r == s.end() ? s.begin() : r);
      int pre = idfn[*l], nxt = idfn[*r];
      i64 d = dist(pre, u) + dist(u, nxt) - dist(pre, nxt);
      used[u] = true, ans += d;
    } else {
      auto l = s.lower_bound(dfn[u]), r = s.upper_bound(dfn[u]);
      l = std::prev(l == s.begin() ? s.end() : l);
      r = (r == s.end() ? s.begin() : r);
      int pre = idfn[*l], nxt = idfn[*r];
      i64 d = dist(pre, u) + dist(u, nxt) - dist(pre, nxt);
      used[u] = false, ans -= d;
      s.erase(dfn[u]);
    }
    std::cout << ans << "\n";
  }

  return 0;
}
