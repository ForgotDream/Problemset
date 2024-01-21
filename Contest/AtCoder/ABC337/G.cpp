#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 5;
struct SegmentTree {
  struct Node {
    i64 sum;
    int lson, rson;
  } tree[N * 20];
  int root[N], tot;
  inline int &lc(int k) { return tree[k].lson; }
  inline int &rc(int k) { return tree[k].rson; }
  inline int Merge(int L, int R, int l, int r) {
    if (!L || !R) return L + R;
    tree[L].sum += tree[R].sum;
    if (l == r) return L;
    int mid = (l + r) / 2;
    lc(L) = Merge(lc(L), lc(R), l, mid);
    rc(L) = Merge(rc(L), rc(R), mid + 1, r);
    return L;
  }
  inline void modify(int &k, int l, int r, int p, i64 cag)  // point add
  {
    if (!k) k = ++tot;
    tree[k].sum += cag;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (p <= mid)
      modify(lc(k), l, mid, p, cag);
    else
      modify(rc(k), mid + 1, r, p, cag);
  }
  inline i64 query(int k, int l, int r, int L, int R)  // range sigma
  {
    if (L > R) return 0;
    if (!k || L > R) return 0;
    if (L <= l && r <= R) return tree[k].sum;
    int mid = (l + r) / 2;
    if (R <= mid)
      return query(lc(k), l, mid, L, R);
    else if (mid + 1 <= L)
      return query(rc(k), mid + 1, r, L, R);
    else
      return query(lc(k), l, mid, L, R) + query(rc(k), mid + 1, r, L, R);
  }
} sgt;
struct SegmentTree2 {
  struct Node {
    i64 sum;
    int lson, rson;
  } tree[N * 30];
  int rt[N], tot;
  SegmentTree2() { rt[0] = tot = 1; }
  inline int lc(int k) { return tree[k].lson; }
  inline int rc(int k) { return tree[k].rson; }
  inline void modify(int L, int &R, int l, int r, int p, i64 cag) {
    R = ++tot;
    tree[R] = tree[L];
    tree[R].sum += cag;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (p <= mid)
      modify(tree[L].lson, tree[R].lson, l, mid, p, cag);
    else
      modify(tree[L].rson, tree[R].rson, mid + 1, r, p, cag);
  }
  inline i64 query(int x, int y, int l, int r, int L, int R) {
    if (L > R) return 0;
    if (L <= l && r <= R) return tree[y].sum - tree[x].sum;
    int mid = (l + r) / 2;
    if (R <= mid)
      return query(tree[x].lson, tree[y].lson, l, mid, L, R);
    else if (mid + 1 <= L)
      return query(tree[x].rson, tree[y].rson, mid + 1, r, L, R);
    else
      return query(tree[x].lson, tree[y].lson, l, mid, L, R) +
             query(tree[x].rson, tree[y].rson, mid + 1, r, L, R);
  }
} seg2;
int n;
std::vector<int> adj[N];
int dfn[N], clk, dfo[N], idfn[N];
i64 f[N];
void dfs(int u, int frm) {
  dfn[u] = ++clk;
  idfn[clk] = u;
  for (auto to : adj[u]) {
    if (to == frm) continue;
    dfs(to, u);
    f[u] += f[to];
    sgt.root[u] = sgt.Merge(sgt.root[u], sgt.root[to], 1, n);
  }
  dfo[u] = clk;
  if (u - 1 >= 1) f[u] += sgt.query(sgt.root[u], 1, n, 1, u - 1);
  sgt.modify(sgt.root[u], 1, n, u, 1);
}

void dfs2(int u, int frm) {
  i64 tmp = f[u];
  for (auto to : adj[u]) {
    if (to == frm) continue;
    f[u] = tmp;
    f[u] -= f[to];
    f[u] -=
        seg2.query(seg2.rt[dfn[to] - 1], seg2.rt[dfo[to]], 1, n, 1, u - 1);
    f[to] += f[u];
    f[to] += seg2.query(seg2.rt[0], seg2.rt[dfn[to] - 1], 1, n, 1, to - 1);
    f[to] += seg2.query(seg2.rt[dfo[to]], seg2.rt[clk], 1, n, 1, to - 1);
    dfs2(to, u);
  }
  f[u] = tmp;
}

void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++)
    seg2.modify(seg2.rt[i - 1], seg2.rt[i], 1, n, idfn[i], 1);
  dfs2(1, 0);
  for (int i = 1; i <= n; i++) std::cout << f[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
