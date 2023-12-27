/*
 * @file    P3242 [HNOI2015] 接水果.cpp
 * @author  ForgotDream
 * @brief   Parallel Binary Search
 * @date    2023-12-20
 */
#include <bits/stdc++.h>

using i64 = long long;

// 考虑怎么样去刻画这个约束
// 发现你妈的根本刻画不了
// 我只会普通的拆开，然后呢？
// 开题解，哦原来我不会整体二分，遂滚粗
constexpr int N = 4e4 + 50;
int n, p, q;
std::vector<int> adj[N];

int in[N], out[N], clk;
int siz[N], fa[N], son[N], top[N];
void dfs1(int u, int frm) {
  in[u] = ++clk, siz[u] = 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u), siz[u] += siz[v];
    if (siz[son[u]] < siz[v]) son[u] = v;
  }
  out[u] = clk;
}
void dfs2(int u, int rt) {
  top[u] = rt;
  if (son[u]) dfs2(son[u], rt);
  for (auto v : adj[u]) {
    if (v == fa[u] || v == son[u]) continue;
    dfs2(v, v);
  }
}
int getSon(int u, int v) {
  while (top[u] != top[v]) {
    if (fa[top[u]] == v) return top[u];
    u = fa[top[u]];
  }
  return son[v];
}

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

// 其实是你妈的扫描线
struct Query {
  int typ, y, l, r, w, idx;
  bool operator<(const Query &rhs) const {
    return y < rhs.y || (y == rhs.y && typ < rhs.typ);
  }
} qry[4 * N], q1[4 * N], q2[4 * N];
int ans[N];

void solve(int l, int r, int s, int t) {
  if (s > t) return;
  if (s == t) {
    for (int i = l; i <= r; i++) {
      if (qry[i].typ) ans[qry[i].idx] = s;
    }
    return;
  }
  int mid = (s + t) >> 1, p1 = 0, p2 = 0;
  for (int i = l; i <= r; i++) {
    if (qry[i].typ) {
      int cur = bit.query(qry[i].l);
      if (cur >= qry[i].w) q1[++p1] = qry[i];
      else qry[i].w -= cur, q2[++p2] = qry[i];
    } else {
      if (qry[i].w <= mid) {
        bit.modify(qry[i].l, qry[i].idx);
        bit.modify(qry[i].r + 1, -qry[i].idx);
        q1[++p1] = qry[i];
      } else {
        q2[++p2] = qry[i];
      }
    }
  }
  for (int i = 1; i <= p1; i++) qry[l + i - 1] = q1[i];
  for (int i = 1; i <= p2; i++) qry[r - p2 + i] = q2[i];
  solve(l, l + p1 - 1, s, mid), solve(l + p1, r, mid + 1, t);
}

std::vector<int> b;
inline void init() {
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
}
inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}

void solve() {
  std::cin >> n >> p >> q;

  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs1(1, 0), dfs2(1, 1);

  int cnt = 0;
  for (int i = 1, u, v, w; i <= p; i++) {
    std::cin >> u >> v >> w, b.push_back(w);
    if (in[u] > in[v]) std::swap(u, v);
    if (out[u] >= out[v]) {
      u = getSon(v, u);
      if (in[u] > 1) {
        qry[++cnt] = {0, in[v], 1, in[u] - 1, w, 1};
        qry[++cnt] = {0, out[v] + 1, 1, in[u] - 1, w, -1};
      } 
      if (out[u] < n) {
        qry[++cnt] = {0, out[u] + 1, in[v], out[v], w, 1};
        qry[++cnt] = {0, n + 1, in[v], out[v], w, -1};
      }
    } else {
      qry[++cnt] = {0, in[v], in[u], out[u], w, 1};
      qry[++cnt] = {0, out[v] + 1, in[u], out[u], w, -1};
    }
  }
  init();
  for (int i = 1; i <= cnt; i++) qry[i].w = find(qry[i].w);

  for (int i = 1, u, v, w; i <= q; i++) {
    std::cin >> u >> v >> w;
    if (in[u] > in[v]) std::swap(u, v);
    qry[++cnt] = {1, in[v], in[u], 0, w, i};
  }

  std::sort(qry + 1, qry + cnt + 1);
  solve(1, cnt, 1, b.size());
  for (int i = 1; i <= q; i++) std::cout << b[ans[i] - 1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
