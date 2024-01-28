/*
 * @file    P4897 【模板】最小割树（Gomory-Hu Tree）.cpp
 * @author  ForgotDream
 * @brief   最小割树 / Gomory-Hu Tree
 * @date    2024-01-28
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

constexpr int N = 2050, inf = 0x3f3f3f3f;

struct Dinic {
  struct Edge {
    int u, v, cap, flow;
    Edge() = default;
    Edge(int _u, int _v, int _c) : u(_u), v(_v), cap(_c), flow(0) {}
  };
  std::vector<Edge> edges;
  int s, t;
  std::vector<int> adj[N];

  void add_edge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }

  int dis[N];
  u32 cur[N];

  bool bfs() {
    std::queue<int> q;
    memset(dis, 0x3f, sizeof(dis));

    dis[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (dis[v] == inf && cap > flow) {
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }

    return dis[t] < inf;
  }

  int dfs(int u, int lim) {
    if (u == t || lim <= 0) return lim;

    int res = 0;
    for (u32 &i = cur[u]; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      int f;
      if (dis[v] == dis[u] + 1 && cap > flow &&
          (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        res += f, flow += f;
        lim -= f, edges[adj[u][i] ^ 1].flow -= f;
        if (!lim) break;
      }
    }

    return res;
  }

  int max_flow(int _s, int _t) {
    s = _s, t = _t;

    int flow = 0;
    while (bfs()) memset(cur, 0, sizeof(cur)), flow += dfs(s, inf);

    return flow;
  }
} solver;

int n, m, q;
int U[N], V[N], W[N];

int p[N], p1[N], p2[N];
std::vector<pii> adj[N];

void init() {
  solver = Dinic();
  for (int i = 1; i <= m; i++) {
    solver.add_edge(U[i], V[i], W[i]);
    solver.add_edge(V[i], U[i], W[i]);
  }
}

void solve(int l, int r) {
  if (l >= r) return;
  init();
  int s = p[l], t = p[l + 1];

  int cut = solver.max_flow(s, t);
  adj[s].emplace_back(t, cut), adj[t].emplace_back(s, cut);
  std::cerr << s << " " << t << " " << cut << "\n";

  int c1 = 0, c2 = 0;
  for (int i = l; i <= r; i++) {
    if (solver.dis[p[i]] != inf) p1[++c1] = p[i];
    else p2[++c2] = p[i];
  }
  for (int i = 1; i <= c1; i++) p[i + l - 1] = p1[i];
  for (int i = 1; i <= c2; i++) p[i + c1 + l - 1] = p2[i];

  solve(l, l + c1 - 1), solve(l + c1, r);
}

int fa[N], cost[N], dep[N];

void dfs(int u, int frm) {
  dep[u] = dep[frm] + 1;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    fa[v] = u, cost[v] = w, dfs(v, u);
  }
}

int query(int u, int v) {
  if (dep[u] < dep[v]) std::swap(u, v);
  int res = 1e9;
  while (dep[u] > dep[v]) res = std::min(res, cost[u]), u = fa[u];
  while (u != v) res = std::min({res, cost[u], cost[v]}), u = fa[u], v = fa[v];
  return res;
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) std::cin >> U[i] >> V[i] >> W[i];

  std::iota(p, p + n + 1, 0);
  solve(0, n), dfs(0, 0);

  std::cin >> q;
  for (int i = 1, s, t; i <= q; i++) {
    std::cin >> s >> t;
    std::cout << query(s, t) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
