/*
 * @file    P4768 [NOI2018] 归程.cpp
 * @author  ForgotDream
 * @brief   Kruskal Reconstruction Tree
 * @date    2024-01-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using ti3 = std::tuple<int, int, int>;
using pli = std::pair<i64, int>;

constexpr int N = 4e5 + 50;

int n, m, q, k, s;
std::vector<ti3> adj[N];

struct Edge {
  int u, v, w, h;
  Edge() {}
  Edge(int _u, int _v, int _w, int _h) : u(_u), v(_v), w(_w), h(_h) {}
};
std::vector<Edge> edges;

i64 dis[N];
bool vis[N];

void dijkstra() {
  std::priority_queue<pli, std::vector<pli>, std::greater<>> pq;
  memset(dis, 0x3f, sizeof(dis)), memset(vis, false, sizeof(vis));

  dis[1] = 0, pq.emplace(0, 1);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w, h] : adj[u]) {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pq.emplace(dis[v], v);
      }
    }
  }
}

namespace KRUSKAL_REBUILD_TREE {

struct DSU {
  int fa[N];
  void init(int _n) { std::iota(fa + 1, fa + _n + 1, 1); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
} dsu;

std::vector<int> adj[N];
int m, val[N];

int st[20][N];

void dfs(int u, int frm = 0) {
  st[0][u] = frm;
  for (int i = 1; i <= std::__lg(m); i++) st[i][u] = st[i - 1][st[i - 1][u]];
  for (auto v : adj[u]) dfs(v, u), dis[u] = std::min(dis[u], dis[v]);
}

void build() {
  for (int i = 1; i < 2 * n; i++) adj[i].clear();

  std::sort(edges.begin(), edges.end(), [&](const Edge &lhs, const Edge &rhs) {
    return lhs.h > rhs.h;
  });
  dsu.init(n);

  m = n;
  std::fill(val + 1, val + n + 1, INT_MAX);

  for (u32 i = 0; i < edges.size(); i++) {
    auto [u, v, w, h] = edges[i];
    int fu = dsu.find(u), fv = dsu.find(v);
    if (fu == fv) continue;
    m++, val[m] = h;
    dsu.fa[m] = dsu.fa[fu] = dsu.fa[fv] = m;
    adj[m].push_back(fu), adj[m].push_back(fv);
    if (m == 2 * n - 1) break;
  }

  dfs(m);
}

int query(int v, int h) {
  for (int i = std::__lg(m); i >= 0; i--) {
    if (st[i][v] && val[st[i][v]] > h) v = st[i][v];
  }
  return v;
}

}  // namespace KRUSKAL_REBUILD_TREE

using KRUSKAL_REBUILD_TREE::query;

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, w, h; i <= m; i++) {
    std::cin >> u >> v >> w >> h;
    adj[u].emplace_back(v, w, h), adj[v].emplace_back(u, w, h);
    edges.emplace_back(u, v, w, h);
  }

  dijkstra();
  KRUSKAL_REBUILD_TREE::build();

  std::cin >> q >> k >> s;
  i64 lst = 0;
  for (int i = 1, h, u; i <= q; i++) {
    std::cin >> u >> h;
    u = (u + k * lst - 1) % n + 1;
    h = (h + k * lst) % (s + 1);

    int v = query(u, h);
    std::cout << (lst = dis[v]) << "\n";
  }

  for (int i = 1; i <= n; i++) adj[i].clear();
  edges.clear();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
