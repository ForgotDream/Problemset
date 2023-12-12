/**
 * @file    CF1178G The Awesomest Vertex.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-08-26
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 5e5 + 50;
constexpr i64 inf = 1e18;
int n, m;
i64 a[N], b[N];

struct Line {
  i64 k, b;
  Line(i64 _k = 0, i64 _b = 0) { k = _k, b = _b; }
} line[N];

// 拍平
std::vector<int> adj[N];
int in[N], out[N], clk;
void dfs(int u, int frm) {
  in[u] = ++clk;
  i64 v = std::abs(b[u]);
  line[clk] = Line(v, a[u] * v);
  for (auto v : adj[u]) {
    if (v == frm) continue;
    a[v] += a[u], b[v] += b[u];
    dfs(v, u);
  }
  out[u] = ++clk;
  line[clk] = Line(-v, -a[u] * v);
}

// 线段树维护凸包
struct SegTree {
  struct Node {
    i64 k, b, tag, nxt;
  } tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) {
    int c = (tree[lc(u)].b >= tree[rc(u)].b) ? lc(u) : rc(u);
    tree[u].k = tree[c].k;
    tree[u].b = tree[c].b;
    tree[u].nxt = std::min(tree[lc(u)].nxt, tree[rc(u)].nxt);
    if (tree[c].k < tree[c ^ 1].k) {
      tree[u].nxt = std::min(tree[u].nxt, (tree[c].b - tree[c ^ 1].b) /
                                              (tree[c ^ 1].k - tree[c].k));
    }
  }
  void tagging(int u, int val) {
    tree[u].b += val * tree[u].k;
    tree[u].nxt -= val;
    tree[u].tag += val;
  }
  void pushdown(int u) {
    if (!tree[u].tag) return;
    tagging(lc(u), tree[u].tag);
    tagging(rc(u), tree[u].tag);
    tree[u].tag = 0;
  }
  void build(int s, int t, int u) {
    if (s == t) {
      tree[u].k = line[s].k;
      tree[u].b = line[s].b;
      tree[u].nxt = inf;
      return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, lc(u));
    build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int l, int r, int s, int t, int u, i64 val) {
    if (l > r) return;
    if (l <= s && t <= r && val <= tree[u].nxt) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u].b;
    pushdown(u);
    int mid = (s + t) >> 1;
    i64 res = -inf;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;

void solve() {
  std::cin >> n >> m;
  for (int u = 2, v; u <= n; u++) {
    std::cin >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  dfs(1, 0);
  seg.build(1, clk, 1);
  while (m--) {
    int opt, u;
    std::cin >> opt >> u;
    if (opt == 1) {
      i64 val;
      std::cin >> val;
      seg.modify(in[u], out[u], 1, clk, 1, val);
    } else {
      std::cout << seg.query(in[u], out[u], 1, clk, 1) << "\n";
    }
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
