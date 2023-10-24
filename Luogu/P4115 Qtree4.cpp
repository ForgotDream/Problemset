/**
 * @file    P4115 Qtree4.cpp
 * @author  ForgotDream
 * @brief   点分树
 * @date    2023-09-09
 */
#include <iostream>
#include <string>
#include <queue>
#include <variant>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, col[N], q;
std::vector<pii> adj[N];
namespace LCA {
int dfn[N], clk, st[21][N], dep[N];
int calc(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dep[v] = dep[u] + w;
    dfs(v, u);
  }
}
void init() {
  dfs(1, 0);
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = calc(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int LCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return calc(st[d][u], st[d][v - (1 << d) + 1]);
}
int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }
}  // namespace LCA
namespace DFZ {
int siz[N], maxsiz[N], sum, rt, cnt;
bool vis[N];
int fa[N];
struct Heap {
  std::priority_queue<int> A, B;
  void insert(int val) { A.push(val); }
  void erase(int val) { B.push(val); }
  void shrink() {
    while (!B.empty() && A.top() == B.top()) A.pop(), B.pop();
  }
  int max() { return shrink(), A.top(); }
  int semi() {
    int cur = max();
    erase(cur);
    int res = max();
    return insert(cur), res;
  }
  size_t size() { return A.size() - B.size(); }
};
Heap dis[N], ch[N], ans;
void calcsiz(int u, int frm) {
  siz[u] = 1, maxsiz[u] = 0;
  for (auto [v, w] : adj[u]) {
    if (v == frm || vis[v]) continue;
    calcsiz(v, u);
    siz[u] += siz[v], maxsiz[u] = std::max(maxsiz[u], siz[v]);
  }
  maxsiz[u] = std::max(maxsiz[u], sum - siz[u]);
  if (maxsiz[u] < maxsiz[rt]) rt = u;
}
void dfs(int u, int frm, int d, auto &s) {
  s.insert(d);
  for (auto [v, w] : adj[u]) {
    if (v == frm || vis[v]) continue;
    dfs(v, u, d + w, s);
  }
}
void dfz(int u) {
  vis[u] = true;
  for (auto [v, w] : adj[u]) {
    if (vis[v]) continue;
    rt = 0, sum = siz[v], maxsiz[rt] = 1e9;
    calcsiz(v, u);
    fa[rt] = u;
    dfs(v, u, w, dis[rt]), ch[u].insert(dis[rt].max());
    dfz(rt);
  }
  ch[u].insert(0);
  if (ch[u].size() >= 2) ans.insert(ch[u].max() + ch[u].semi());
}
void init() {
  rt = 0, sum = cnt = n, maxsiz[rt] = 1e9;
  calcsiz(1, 0), dfz(rt);
}
void query() {
  if (!cnt) std::cout << "They have disappeared.\n";
  else if (cnt == 1) std::cout << 0 << "\n";
  else std::cout << std::max(0, ans.max()) << "\n";
}
void modify(int u) {
  if (!col[u]) {
    cnt--;
    if (ch[u].size() >= 2) ans.erase(ch[u].max() + ch[u].semi());
    ch[u].erase(0);
    if (ch[u].size() >= 2) ans.insert(ch[u].max() + ch[u].semi());
    for (int i = u; fa[i]; i = fa[i]) {
      if (ch[fa[i]].size() >= 2) ans.erase(ch[fa[i]].max() + ch[fa[i]].semi());
      ch[fa[i]].erase(dis[i].max());
      dis[i].erase(LCA::dis(u, fa[i]));
      if (dis[i].size()) ch[fa[i]].insert(dis[i].max());
      if (ch[fa[i]].size() >= 2) ans.insert(ch[fa[i]].max() + ch[fa[i]].semi());
    }
  } else {
    cnt++;
    if (ch[u].size() >= 2) ans.erase(ch[u].max() + ch[u].semi());
    ch[u].insert(0);
    if (ch[u].size() >= 2) ans.insert(ch[u].max() + ch[u].semi());
    for (int i = u; fa[i]; i = fa[i]) {
      if (ch[fa[i]].size() >= 2) ans.erase(ch[fa[i]].max() + ch[fa[i]].semi());
      if (dis[i].size()) ch[fa[i]].erase(dis[i].max());
      dis[i].insert(LCA::dis(u, fa[i]));
      ch[fa[i]].insert(dis[i].max());
      if (ch[fa[i]].size() >= 2) ans.insert(ch[fa[i]].max() + ch[fa[i]].semi());
    }
  }
  col[u] ^= 1;
}
}  // namespace DFZ
void solve() {
  std::cin >> n;
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  LCA::init(), DFZ::init();
  std::cin >> q;
  while (q--) {
    char opt;
    int u;
    std::cin >> opt;
    if (opt == 'A') DFZ::query();
    else std::cin >> u, DFZ::modify(u);
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}