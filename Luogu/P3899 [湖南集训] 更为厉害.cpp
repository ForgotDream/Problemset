/*
 * @file    P3899 [湖南集训] 更为厉害.cpp
 * @author  ForgotDream
 * @brief   长链剖分 + BIT
 * @date    2024-01-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 3e5 + 50, M = 1;
int n, q;
std::vector<int> adj[N / M];
std::vector<pii> qry[N / M];

int dep[N], len[N], fa[N], son[N], siz[N];
void dfs1(int u, int frm) {
  dep[u] = dep[frm] + 1, len[u] = 1, fa[u] = frm;
  siz[u] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u), siz[u] += siz[v];
    if (len[v] + 1 > len[u]) len[u] = len[v] + 1, son[u] = v;
  }
}
int top[N], dfn[N], idfn[N], clk;
void dfs2(int u, int tp) {
  top[u] = tp, dfn[u] = ++clk, idfn[clk] = u;
  if (son[u]) dfs2(son[u], tp);
  for (auto v : adj[u]) {
    if (v == fa[u] || v == son[u]) continue;
    dfs2(v, v);
  }
}

struct BIT {
  i64 tree[N];
  void modify(int u, i64 val) {
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  i64 query(int u) {
    i64 res = 0;
    for (int i = u; i; i -= i &-i) res += tree[i];
    return res;
  }
  i64 query(int l, int r) { return query(r) - query(l - 1); }
} bit;

i64 ans[N];
void dp(int u) {
  if (son[u]) dp(son[u]);
  bit.modify(dfn[u], siz[u] - 1);
  for (auto v : adj[u]) {
    if (v == fa[u] || v == son[u]) continue;
    dp(v);
    for (int i = 1; i <= len[v]; i++) {
      bit.modify(dfn[u] + i, bit.query(dfn[v] + i - 1, dfn[v] + i - 1));
    }
  }
  for (auto [k, i] : qry[u]) {
    int t1 = std::min(k, len[u] - 1), t2 = std::min(k, dep[u] - 1);
    ans[i] = bit.query(dfn[u] + 1, dfn[u] + t1) + 1ll * t2 * (siz[u] - 1);
  }
}

void solve() {
  std::cin >> n >> q;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1, p, k; i <= q; i++) {
    std::cin >> p >> k;
    qry[p].emplace_back(k, i);
  }

  dfs1(1, 0), dfs2(1, 1), dp(1);

  for (int i = 1; i <= q; i++) std::cout << ans[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
