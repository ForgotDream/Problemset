/*
 * @file    P3705 [SDOI2017] 新生舞会.cpp
 * @author  ForgotDream
 * @brief   MCMF + 01 Fractional Programming
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using f64 = double;

constexpr int N = 205, inf = 0x3f3f3f3f;
constexpr f64 eps = 1e-8;

template <typename T>
struct MCMF {
  struct Edge {
    int u, v, cap;
    T cost;
    Edge() = default;
    Edge(int _u, int _v, int _c, T _w) : u(_u), v(_v), cap(_c), cost(_w) {}
  };
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int s, t;
  T dis[N];
  bool vis[N];

  void add_edge(int u, int v, int cap, T cost) {
    edges.emplace_back(u, v, cap, cost);
    edges.emplace_back(v, u, 0, -cost);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }

  bool spfa() {
    static bool ins[N];
    std::queue<int> q;
    std::fill(dis, dis + N, -inf);
    memset(ins, false, sizeof(ins));

    dis[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop(), ins[u] = false;
      for (auto i : adj[u]) {
        auto [_, v, cap, w] = edges[i];
        if (dis[v] < dis[u] + w && cap) {
          dis[v] = dis[u] + w;
          if (!ins[v]) q.push(v), ins[v] = true;
        }
      }
    }

    return dis[t] != -inf;
  }

  int dfs(int u, int lim, T &cost) {
    if (u == t || !lim) return lim;
    int res = 0;
    vis[u] = true;
    for (auto i : adj[u]) {
      auto &[_, v, cap, w] = edges[i];
      int f;
      if (dis[v] == dis[u] + w && !vis[v] && 
          (f = dfs(v, std::min(lim, cap), cost)) > 0) {
        cap -= f, lim -= f, cost += f * w;
        res += f, edges[i ^ 1].cap += f;
        if (!lim) break;
      }
    }
    return res;
  }

  std::pair<int, T> solve(int _s, int _t) {
    s = _s, t = _t;
    int flow = 0;
    T cost = 0;

    while (spfa()) {
      memset(vis, false, sizeof(vis));
      flow += dfs(s, inf, cost);
    }

    return {flow, cost};
  }
};
MCMF<double> solver, eye;

int n, a[N][N], b[N][N];

bool check(f64 u) {
  solver = eye;
  int s = 0, t = 2 * n + 1;
  for (int i = 1; i <= n; i++) {
    solver.add_edge(s, i, 1, 0);
    solver.add_edge(i + n, t, 1, 0);
    for (int j = 1; j <= n; j++) {
      solver.add_edge(i, j + n, 1, a[i][j] - u * b[i][j]);
    }
  }
  auto [flow, cost] = solver.solve(s, t);
  return cost >= 0;
}

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) std::cin >> a[i][j];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) std::cin >> b[i][j];
  }

  f64 lo = 0, hi = 1e6, ans = 0;
  while (std::fabs(hi - lo) > eps) {
    auto mid = (lo + hi) / 2;
    if (check(mid)) ans = mid, lo = mid;
    else hi = mid;
  }

  std::cerr << check(1000) << "\n";

  std::cout << std::fixed << std::setprecision(6) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
