#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 3e5 + 50;

int n, p[N];
std::vector<int> adj[N];

namespace LCA {

int st[20][N], dfn[N], clk;

void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}

inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }

void init() {
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}

inline int queryLCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return cmp(st[d][u], st[d][v - (1 << d) + 1]);
}

}  // namespace LCA

using LCA::queryLCA;

inline int queryLCA(int u, int v, int rt) {
  return queryLCA(u, v) ^ queryLCA(u, rt) ^ queryLCA(v, rt);
}

int dep[N], t[N];

void dfs(int u, int frm) {
  dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}

int l[N], r[N], stk[N], top;

i64 calc(int rt) {
  dfs(rt, 0), top = 0;
  std::fill(l + 1, l + n, 0), std::fill(r + 1, r + n, n);

  for (int i = 1; i < n; i++) t[i] = queryLCA(p[i], p[i + 1], rt);

  for (int i = 1; i < n; i++) {
    while (top && dep[t[i]] <= dep[t[stk[top]]]) r[stk[top--]] = i;
    if (top) l[i] = stk[top];
    stk[++top] = i;
  }

  i64 res = 1ll * n * (n + 1) / 2;
  for (int i = 1; i < n; i++) res += 1ll * t[i] * (r[i] - i) * (i - l[i]);

  // for (int i = 1; i < n; i++) {
  //   std::cerr << t[i] << " " << l[i] << " " << r[i] << "\n";
  // }
  // std::cerr << "\n";

  return res;
}

void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) std::cin >> p[i];

  LCA::dfs(1, 0), LCA::init();
  
  for (int i = 1; i <= n; i++) std::cout << calc(i) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
