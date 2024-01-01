/*
 * @file    P3292 [SCOI2016] 幸运数字.cpp
 * @author  ForgotDream
 * @brief   Linear Space
 * @date    2023-12-30
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e4 + 50, W = 61;
int n, q;
i64 a[N];
std::vector<int> adj[N];

struct Basis {
  i64 p[W];
  Basis() { init(); }
  void init() { std::memset(p, 0, sizeof(p)); }
  void insert(i64 val) {
    for (int i = W - 1; ~i; i--) {
      if (!(val & (1ll << i))) continue;
      if (!p[i]) {
        p[i] = val;
        break;
      }
      val ^= p[i];
    }
  }
  i64 queryMax(i64 val = 0) {
    i64 res = val;
    for (int i = W - 1; ~i; i--) res = std::max(res, res ^ p[i]);
    return res;
  }
};
Basis operator+(const Basis &lhs, const Basis &rhs) {
  Basis res = lhs;
  for (int i = 0; i < W; i++) res.insert(rhs.p[i]);
  return res;
}

Basis st[20][N];
int fa[20][N], dep[N];
void dfs(int u, int frm) {
  fa[0][u] = frm, st[0][u].insert(a[u]), dep[u] = dep[frm] + 1;
  for (int i = 1; i <= std::__lg(n); i++) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
    st[i][u] = st[i - 1][u] + st[i - 1][fa[i - 1][u]];
  }
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
Basis query(int u, int v) {
  Basis res;
  if (dep[u] < dep[v]) std::swap(u, v);
  for (int i = std::__lg(n); ~i; i--) {
    if (dep[fa[i][u]] >= dep[v]) res = res + st[i][u], u = fa[i][u];
  }
  if (u == v) return res + st[0][u];
  for (int i = std::__lg(n); ~i; i--) {
    if (fa[i][u] != fa[i][v]) {
      res = res + st[i][u], u = fa[i][u];
      res = res + st[i][v], v = fa[i][v];
    }
  }
  res = res + st[0][fa[0][u]] + st[0][u] + st[0][v];
  return res;
}

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs(1, 0);

  for (int u, v; q; q--) {
    std::cin >> u >> v;
    auto res = query(u, v);
    std::cout << res.queryMax() << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
