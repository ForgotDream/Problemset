#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;

int n, m;
std::vector<pii> adj[N];

namespace LCA {

int dfn[N], clk;
int st[20][N];
i64 dep[N];

void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dep[v] = dep[u] + w, dfs(v, u);
  }
}

inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }

void init() {
  dfs(1, 0);
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}

inline int getLCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return cmp(st[d][u], st[d][v - (1 << d) + 1]);
}

inline i64 getDis(int u, int v) {
  return dep[u] + dep[v] - 2 * dep[getLCA(u, v)];
}

}  // namespace LCA

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  i64 lst = 0;
  for (int i = 1, ct; i <= m; i++) {
    std::cin >> ct;
    for (int j = 1, u; j <= ct; j++) std::cin >> u;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
