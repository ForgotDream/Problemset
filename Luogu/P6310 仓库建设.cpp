/**
 * @file    P6310 仓库建设.cpp
 * @author  ForgotDream
 * @brief   Kruskal + DP
 * @date    2023-06-08
 */
#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
  int n;
  std::vector<int> fa;
  DSU(int _n) { n = _n, fa.resize(n), std::iota(fa.begin(), fa.end(), 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  void setFa(int u, int f) { fa[u] = f; }
};
struct Edge {
  int u, v, w;
  Edge(int _u, int _v, int _w) { u = _u, v = _v, w = _w; }
};
bool operator<(const Edge &lhs, const Edge &rhs) { return lhs.w < rhs.w; }

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edges.emplace_back(u, v, w);
  }

  std::sort(edges.begin(), edges.end());
  int cnt = n;
  DSU dsu(2 * n);
  std::vector<std::vector<int>> adj(2 * n);
  std::vector<std::vector<int>> fa(2 * n, std::vector<int>(25, 0));
  std::vector<int> val(2 * n);
  for (int i = 0; i < m; i++) {
    int u = edges[i].u, v = edges[i].v, w = edges[i].w;
    u = dsu.find(u), v = dsu.find(v);
    if (u != v) {
      cnt++;
      dsu.setFa(u, cnt), dsu.setFa(v, cnt);
      val[cnt] = w;
      adj[cnt].push_back(v), adj[cnt].push_back(u);
      fa[u][0] = fa[v][0] = cnt;
    }
    if (cnt == 2 * n - 1) { break; }
  }

  std::function<void(int)> init = [&](int u) {
    for (int i = 1; i < 25; i++) { fa[u][i] = fa[fa[u][i - 1]][i - 1]; }
    for (auto v : adj[u]) { init(v); }
  };
  init(cnt);

  std::vector<int> pos(2 * n);
  std::vector<std::vector<int>> to(2 * n);
  for (int i = 1; i <= n; i++) {
    int cur, p;
    std::cin >> cur;
    p = i;
    for (int j = 24; j >= 0; j--) {
      if (fa[p][j] != 0 && val[fa[p][j]] <= cur) { p = fa[p][j]; }
    }
    pos[p]++, to[p].push_back(i);
  }

  std::vector<int> f(2 * n);
  std::function<void(int)> dfs1 = [&](int u) {
    for (auto v : adj[u]) { dfs1(v), f[u] += f[v]; }
    if (pos[u]) { f[u] = 1; }
  };

  std::vector<int> tag(2 * n);
  std::function<void(int, int)> dfs2 = [&](int u, int cur) {
    tag[u] = cur;
    for (auto v : adj[u]) { dfs2(v, cur + pos[u]); }
  };

  std::vector<int> ans(2 * n);
  std::function<void(int)> dfs3 = [&](int u) {
    if (pos[u] > 1 || tag[u]) {
      for (auto v : to[u]) { ans[v] = f[cnt]; }
    } else if (pos[u]) {
      ans[to[u][0]] = f[cnt] - 1;
      for (auto v : adj[u]) { ans[to[u][0]] += f[v]; }
      if (tag[to[u][0]] <= 1) { ans[to[u][0]] = -1; }
    }
    for (auto v : adj[u]) { dfs3(v); }
  };

  dfs1(cnt), dfs2(cnt, 0), dfs3(cnt);
  std::cout << f[cnt] << " ";
  for (int i = 1; i <= n; i++) { std::cout << ans[i] << " \n"[i == n]; }

  return 0;
}