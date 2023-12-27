/*
 * @file    P4719 【模板】"动态 DP"&动态树分治.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + DP
 * @date    2023-12-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, p[N];
std::vector<int> adj[N];

struct Mat {
  i64 a[2][2];
  Mat() { memset(a, -0x3f, sizeof(a)); }
  i64 *operator[](size_t idx) { return a[idx]; }
  const i64 *operator[](size_t idx) const { return a[idx]; }
  Mat operator*(const Mat &rhs) const {
    Mat res;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          res[i][j] = std::max(res[i][j], a[i][k] + rhs[k][j]);
        }
      }
    }
    return res;
  }
} mat[N];
std::ostream &operator<<(std::ostream &os, const Mat &mm) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) os << mm[i][j] << " \n"[j == 1];
  }
  return os;
}

int siz[N], dep[N], fa[N], son[N];
int top[N], dfn[N], idfn[N], end[N], clk;
i64 f[N][2];
void dfs1(int u, int frm) {
  siz[u] = 1, dep[u] = dep[frm] + 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u), siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs2(int u, int rt) {
  top[u] = rt, dfn[u] = ++clk, idfn[clk] = u, end[rt] = clk;

  f[u][0] = 0, f[u][1] = p[u];
  mat[u][0][0] = mat[u][0][1] = 0, mat[u][1][0] = p[u];

  if (son[u]) {
    dfs2(son[u], rt);
    f[u][0] += std::max(f[son[u]][0], f[son[u]][1]);
    f[u][1] += f[son[u]][0];
  }
  for (auto v : adj[u]) {
    if (v == son[u] || v == fa[u]) continue;
    dfs2(v, v);

    f[u][0] += std::max(f[v][0], f[v][1]);
    f[u][1] += f[v][0];
    mat[u][0][0] += std::max(f[v][0], f[v][1]);
    mat[u][0][1] = mat[u][0][0];
    mat[u][1][0] += f[v][0];
  }
}
inline int in(int u) { return dfn[u]; }
inline int out(int u) { return end[u]; }

struct SegTree {
  Mat tree[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  inline void pushup(int u) { tree[u] = tree[lc(u)] * tree[rc(u)]; }
  void build(int s, int t, int u) {
    if (s == t) return tree[u] = mat[idfn[s]], void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  Mat query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1;
    if (mid >= r) return query(l, r, s, mid, lc(u));
    else if (mid < l) return query(l, r, mid + 1, t, rc(u));
    else return query(l, r, s, mid, lc(u)) * query(l, r, mid + 1, t, rc(u));
  }
  void modify(int tar, int s, int t, int u) {
    if (s == t) return tree[u] = mat[idfn[s]], void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
    pushup(u);
  }
} seg;

inline void modify(int u, int w) {
  mat[u][1][0] += w - p[u];
  p[u] = w;

  while (u) {
    auto bfr = seg.query(in(top[u]), out(top[u]), 1, n, 1);
    seg.modify(in(u), 1, n, 1);
    auto aft = seg.query(in(top[u]), out(top[u]), 1, n, 1);

    u = fa[top[u]];
    if (!u) break;

    mat[u][0][0] += std::max(aft[0][0], aft[1][0]) - std::max(bfr[0][0], bfr[1][0]);
    mat[u][0][1] = mat[u][0][0];
    mat[u][1][0] += aft[0][0] - bfr[0][0];
  }
}

void solve() {
  std::cin >> n >> m;
  // std::getline(std::cin, *new std::string());
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs1(1, 0), dfs2(1, 1);
  seg.build(1, n, 1);
  // for (int i = 1; i <= n; i++) std::cerr << mat[i] << "\n";

  for (int i = 1, u, w; i <= m; i++) {
    std::cin >> u >> w, modify(u, w);
    auto ans = seg.query(in(1), out(1), 1, n, 1);
    std::cout << std::max(ans[0][0], ans[1][0]) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
