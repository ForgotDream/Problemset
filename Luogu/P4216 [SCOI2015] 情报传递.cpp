/*
 * @file    P4216 [SCOI2015] 情报传递.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-12-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, fa[N], rt;
std::vector<int> adj[N];

int siz[N], dep[N], dfn[N], clk;
int st[20][N];
void dfs(int u) {
  siz[u] = 1, dep[u] = dep[fa[u]] + 1;
  st[0][dfn[u] = ++clk] = fa[u];
  for (auto v : adj[u]) dfs(v), siz[u] += siz[v];
}
inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
void init() {
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
inline int getDis(int u, int v) {
  int lca = getLCA(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
}

inline int in(int u) { return dfn[u]; }
inline int out(int u) { return dfn[u] + siz[u] - 1; }

struct BIT {
  int tree[N];
  inline void modify(int u, int val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  inline int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit;
inline i64 query(int u, int v) {
  int lca = getLCA(u, v);
  return bit.query(in(u)) + bit.query(in(v)) - 
         bit.query(in(lca)) - bit.query(in(fa[lca]));
}

struct Query {
  int opt, u, v;
} qry[N];
std::vector<int> idx[N];
int ans[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> fa[i];
    if (fa[i]) adj[fa[i]].push_back(i);
    else rt = i;
  }

  dfs(rt), init();

  std::cin >> m;
  for (int i = 1, w; i <= m; i++) {
    auto &[opt, u, v] = qry[i];
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> u >> v >> w;
      if (w < i) idx[i - w - 1].push_back(i);
    } else {
      std::cin >> u;
    }
  }

  for (int i = 1; i <= m; i++) {
    auto [opt, u, v] = qry[i];
    if (opt == 2) {
      bit.modify(in(u), 1), bit.modify(out(u) + 1, -1);
    }
    for (auto j : idx[i]) ans[j] = query(qry[j].u, qry[j].v);
    if (opt == 1) {
      std::cout << getDis(u, v) + 1 << " " << ans[i] << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
