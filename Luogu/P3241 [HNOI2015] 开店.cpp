/*
 * @file    P3241 [HNOI2015] 开店.cpp
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using pil = std::pair<int, i64>;

constexpr int N = 1.5e5 + 50;
constexpr i64 inf = 1e18;
int n, q, A, val[N];
std::vector<pil> adj[N];

inline pil calc(int a, int b, i64 lst) {
  a = (a + lst) % A, b = (b + lst) % A;
  if (a > b) std::swap(a, b);
  return {a, b};
}

namespace LCA {
int st[20][N], dfn[N], clk;
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
  int lca = getLCA(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
}
}  // namespace LCA
using LCA::getDis;

int siz[N], max[N], rt, tot, fa[N];
bool vis[N];
std::vector<pil> dis[N], ch[N];
void calcsiz(int u, int frm) {
  siz[u] = 1, max[u] = 0;
  for (auto [v, w] : adj[u]) {
    if (v == frm || vis[v]) continue;
    calcsiz(v, u), siz[u] += siz[v];
    max[u] = std::max(max[u], siz[v]);
  }
  max[u] = std::max(max[u], tot - siz[u]);
  if (max[u] < max[rt]) rt = u;
}
void dfs(int u, int frm, int sum) {
  siz[u] = 1, dis[rt].emplace_back(val[u], sum);
  if (fa[rt]) ch[rt].emplace_back(val[u], getDis(u, fa[rt]));
  for (auto [v, w] : adj[u]) {
    if (v == frm || vis[v]) continue;
    dfs(v, u, sum + w), siz[u] += siz[v];
  }
}
void dfz(int u) {
  vis[u] = true, dfs(u, 0, 0);
  for (auto [v, w] : adj[u]) {
    if (vis[v]) continue;
    tot = siz[u], rt = 0, max[rt] = 1e9;
    calcsiz(v, u), fa[rt] = u;
    dfz(rt);
  }
}

inline i64 query(int l, int r, std::vector<pil> &v, i64 &ss) {
  auto lp = std::lower_bound(v.begin(), v.end(), std::make_pair(l, 0ll)) - 1;
  auto rp = std::upper_bound(v.begin(), v.end(), std::make_pair(r, inf)) - 1;
  ss = rp - lp;
  i64 res = 0;
  if (rp >= v.begin() && rp < v.end()) res += rp->second;  
  if (lp >= v.begin() && lp < v.end()) res -= lp->second;
  return res;
}

void solve() {
  std::cin >> n >> q >> A;
  for (int i = 1; i <= n; i++) std::cin >> val[i];
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }

  LCA::dfs(1, 0), LCA::init();
  tot = n, rt = 0, max[rt] = 1e9, calcsiz(1, 0), dfz(rt);
  for (int i = 1; i <= n; i++) {
    std::sort(dis[i].begin(), dis[i].end());
    std::sort(ch[i].begin(), ch[i].end());
    for (size_t j = 1; j < dis[i].size(); j++) {
      dis[i][j].second += dis[i][j - 1].second;
    }
    for (size_t j = 1; j < ch[i].size(); j++) {
      ch[i][j].second += ch[i][j - 1].second;
    }
  }

  i64 lst = 0;
  for (int i = 1, u, l, r; i <= q; i++) {
    std::cin >> u >> l >> r, std::tie(l, r) = calc(l, r, lst);
    i64 s1 = 0, s2 = 0;
    lst = query(l, r, dis[u], s1);
    for (int p = u; fa[p]; p = fa[p]) {
      lst += query(l, r, dis[fa[p]], s2) - query(l, r, ch[p], s1);
      lst += (s2 - s1) * getDis(u, fa[p]);
    }
    std::cout << lst << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
