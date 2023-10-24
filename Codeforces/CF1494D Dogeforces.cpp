/**
 * @file    CF1494D Dogeforces.cpp
 * @author  ForgotDream
 * @brief   Kruskal 重构树
 * @date    2023-08-25
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

template<int N = 5050>
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
};
DSU dsu;

constexpr int N = 1050;
int ecnt;
struct Edge {
  int u, v, w;
  Edge(int _u = 0, int _v = 0, int _w = 0) { u = _u, v = _v, w = _w; }
  bool operator<(const Edge &rhs) const { return w < rhs.w; }
} edges[N * N];

int n, a[N][N], cnt, val[N], mp[N], vcnt, res[N];
std::vector<int> adj[N];
std::vector<pii> ans;
void dfs(int u, int frm) {
  if (u <= n) return;
  if (val[u] != val[frm]) mp[u] = ++vcnt, res[vcnt] = val[u];
  else mp[u] = mp[frm];
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
  for (auto v : adj[u]) {
    if (v == frm) continue;
    if (mp[v] != mp[u]) ans.emplace_back(mp[v], mp[u]);
  }
}
void solve() {
  std::cin >> n;
  vcnt = cnt = n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      std::cin >> a[i][j];
      if (j > i) edges[++ecnt] = Edge(i, j, a[i][j]);
    }
    res[i] = val[i] = a[i][i], mp[i] = i;
  }
  std::sort(edges + 1, edges + ecnt + 1);
  for (int i = 1; i <= ecnt; i++) {
    auto [u, v, w] = edges[i];
    u = dsu.find(u), v = dsu.find(v);
    if (u != v) {
      val[++cnt] = w;
      dsu.fa[u] = dsu.fa[v] = dsu.fa[cnt] = cnt;
      adj[cnt].push_back(u), adj[cnt].push_back(v);
    }
  }
  dfs(cnt, 0);
  std::cout << vcnt << "\n";
  for (int i = 1; i <= vcnt; i++) std::cout << res[i] << " \n"[i == vcnt];
  std::cout << mp[cnt] << "\n";
  for (auto [u, v] : ans) std::cout << u << " " << v << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}