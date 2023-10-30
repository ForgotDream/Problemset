/**
 * @file    P2305 [NOI2014] 购票.cpp
 * @author  ForgotDream
 * @brief   Lichao SegTree + DP
 * @date    2023-10-29
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50, S = 0, T = 1e6;
constexpr i64 inf = 1e18;
int n, t, p[N];
i64 s[N], lim[N], q[N];
struct Line {
  i64 k, b;
  inline i64 operator()(const i64 &val) { return k * val + b; }
} line[N];
struct SegTree {
  struct Node {
    int lc, rc, id;
  } tree[N << 5];
  int cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void modify(int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    int &cur = tree[u].id, mid = (s + t) >> 1;
    if (!cur) return cur = val, void();
    if (line[val](mid) < line[cur](mid)) std::swap(val, cur);
    if (line[val](s) < line[cur](s)) modify(s, mid, lc(u), val);
    if (line[val](t) < line[cur](t)) modify(mid + 1, t, rc(u), val);
  }
  i64 query(int tar, int s, int t, int u) {
    if (!u) return inf;
    if (s == t) return line[tree[u].id](tar);
    int mid = (s + t) >> 1;
    i64 res = line[tree[u].id](tar);
    if (mid >= tar) return std::min(res, query(tar, s, mid, lc(u)));
    else return std::min(res, query(tar, mid + 1, t, rc(u)));
  }
} seg;
// 其实是一个类似线段树分治的玩意？
std::vector<int> adj[N];
int rt[N << 2];
inline int lc(int u) { return u << 1; }
inline int rc(int u) { return u << 1 | 1; }
int pos[N];
void build(int s, int t, int u) {
  if (s == t) return pos[s] = u, void();
  int mid = (s + t) >> 1;
  build(s, mid, lc(u)), build(mid + 1, t, rc(u));
}
inline void modify(int tar, int val) {
  int p = pos[tar];
  while (p) seg.modify(S, T, rt[p], val), p >>= 1;
}
i64 query(int l, int r, int s, int t, int u, int val) {
  if (l <= s && t <= r) return seg.query(val, S, T, rt[u]);
  int mid = (s + t) >> 1;
  i64 res = inf;
  if (mid >= l) res = std::min(res, query(l, r, s, mid, lc(u), val));
  if (mid < r) res = std::min(res, query(l, r, mid + 1, t, rc(u), val));
  return res;
}
int dfn[N], clk;
void init(int u) {
  for (auto v : adj[u]) init(v);
  dfn[u] = ++clk;
}
int top, idx[N];
i64 dis[N], f[N];
int find(i64 u) {
  return std::lower_bound(dis, dis + top, u) - dis;
}
void dfs(int u) {
  idx[top] = u, line[u] = {-dis[top], f[u]};
  modify(dfn[u], u);
  for (auto v : adj[u]) {
    top++, dis[top] = dis[top - 1] + s[v];
    int l = dfn[v], r = dfn[idx[find(dis[top] - lim[v])]];
    f[v] = query(l, r, 1, n, 1, p[v]) + dis[top] * p[v] + q[v];
    dfs(v);
    top--;
  }
}
void solve() {
  std::cin >> n >> t;
  for (int i = 2, f; i <= n; i++) {
    std::cin >> f >> s[i] >> p[i] >> q[i] >> lim[i];
    adj[f].push_back(i);
  }
  build(1, n, 1);
  init(1), dfs(1);
  for (int i = 2; i <= n; i++) std::cout << f[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
