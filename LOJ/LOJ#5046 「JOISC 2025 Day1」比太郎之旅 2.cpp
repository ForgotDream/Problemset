/*
 * @file    LOJ#5046 「JOISC 2025 Day1」比太郎之旅 2.cpp
 * @author  ForgotDream
 * @brief   Kruskal Reconstruction Tree 
 * @date    2026-10-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

struct DSU {
  std::vector<int> fa;
  int n;

  DSU(int n) : n(n) {
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
  }

  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
};

void solve() {
  int h, w, l;
  std::cin >> h >> w >> l;

  int n = h * w;
  auto idx = [&w](int i, int j) { return i * w + j; };

  std::vector<int> t(n);
  std::vector<pii> pts;
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int cur = idx(i, j);
      std::cin >> t[cur];
      pts.emplace_back(t[cur], cur);
    }
  }

  std::sort(pts.begin(), pts.end());
  DSU dsu(n);
  int d[][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
  };
  std::vector adj(n, std::vector<int>());
  std::vector<bool> vis(n);

  for (auto [_, u] : pts) {
    int cx = u / w, cy = u % w;
    vis[u] = true;
    for (auto [dx, dy] : d) {
      int nx = cx + dx, ny = cy + dy;
      if (nx < 0 || nx >= h) continue;
      if (ny < 0 || ny >= w) continue;

      int v = idx(nx, ny);
      if (vis[v]) {
        int fu = dsu.find(u), fv = dsu.find(v);
        if (fu == fv) continue;
        adj[u].push_back(fv);
        dsu.fa[fv] = u;
      }
    }
  }

  std::vector<int> dep(n);
  std::vector up(20, std::vector<int>(n));
  std::vector nxt(20, std::vector<int>(n));

  auto dfs = [&](this auto self, int u, int frm) -> void {
    dep[u] = dep[frm] + 1;
    up[0][u] = frm;
    for (int k = 1; k < 20; k++) up[k][u] = up[k - 1][up[k - 1][u]];
    for (auto v : adj[u]) self(v, u);
  };

  int rt = pts.back().second;
  dfs(rt, rt);

  auto get_lca = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) std::swap(u, v);
    for (int k = 19; ~k; k--) if (dep[up[k][u]] >= dep[v]) u = up[k][u];
    if (u == v) return u;
    for (int k = 19; ~k; k--) if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
    return up[0][u];
  };

  auto get_nxt = [&](int u, int h) -> int {
    for (int k = 19; ~k; k--) if (t[up[k][u]] <= h) u = up[k][u];
    return u;
  };

  for (int i = 0; i < n; i++) nxt[0][i] = get_nxt(i, l + t[i]);
  for (int k = 1; k < 20; k++) {
    for (int i = 0; i < n; i++) nxt[k][i] = nxt[k - 1][nxt[k - 1][i]];
  }

  int q;
  std::cin >> q;

  while (q--) {
    int sx, sy, tx, ty;
    std::cin >> sx >> sy >> tx >> ty;
    sx--, sy--, tx--, ty--;

    int s = idx(sx, sy), t = idx(tx, ty);
    int w = get_lca(s, t);

    if (s == t) {
      std::cout << 0 << "\n";
      continue;
    }

    if (dep[nxt[19][s]] > dep[w]) {
      std::cout << -1 << "\n";
      continue;
    }

    int ans = 0;
    for (int k = 19; ~k; k--) {
      if (dep[nxt[k][s]] > dep[w]) s = nxt[k][s], ans += (1 << k);
    }
    std::cout << ans + 1 << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
