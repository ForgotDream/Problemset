/**
 * @file    P3313 旅行.cpp
 * @author  ForgotDream
 * @brief   HLD + 动态开点线段树
 * @date    2023-06-06
 */
#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  struct Node {
    int sum, max;
    int lc, rc, l, r;
    Node() { sum = max = lc = rc = l = r = 0; }
  };
  std::vector<Node> tree;
  std::map<int, int> root;
  std::stack<int> pool;
  std::vector<int> col, a;
  SegTree(int _n, const std::vector<int> &_col, const std::vector<int> &_a) {
    n = _n, col = _col, a= _a;
    tree.resize((n << 5) + 1);
    for (int i = (n << 5); i; i--) { pool.push(i); }
  }
  void pushup(int u) {
    int lc = tree[u].lc, rc = tree[u].rc;
    tree[u].sum = tree[lc].sum + tree[rc].sum;
    tree[u].max = std::max(tree[lc].max, tree[rc].max);
  }
  int init(int l, int r) {
    assert(!pool.empty());
    int cur = pool.top();
    pool.pop();
    tree[cur].l = l, tree[cur].r = r;
    return cur;
  }
  void recycle(int u) {
    pool.push(u);
    tree[u].max = tree[u].sum = 0;
    tree[u].l = tree[u].r = tree[u].lc = tree[u].rc = 0;
  }
  void build() {
    for (int i = 0; i < n; i++) {
      int cur = col[i];
      if (!root.count(cur)) { root[cur] = init(1, n); }
      add(i + 1, root[cur], a[i]);
    }
  }
  void add(int target, int u, int val) {
    int s = tree[u].l, t = tree[u].r;
    if (s == target && t == target) {
      tree[u].max = tree[u].sum = val;
      return;
    }
    int mid = (s + t) >> 1, &lc = tree[u].lc, &rc = tree[u].rc;
    if (target <= mid) {
      if (!lc) { lc = init(s, mid); }
      add(target, lc, val);
    } else {
      if (!rc) { rc = init(mid + 1, t); }
      add(target, rc, val);
    }
    pushup(u);
  }
  bool erase(int target, int u) {
    int s = tree[u].l, t = tree[u].r;
    if (s == target && t == target) {
      recycle(u);
      return true;
    }
    int mid = (s + t) >> 1, &lc = tree[u].lc, &rc = tree[u].rc;
    if (target <= mid) {
      if (erase(target, lc)) { lc = 0; }
    } else {
      if (erase(target, rc)) { rc = 0; }
    }
    pushup(u);
    if (!lc && !rc) {
      recycle(u);
      return true;
    } else {
      return false;
    }
  }
  void modifyCol(int target, int val) {
    int pre = col[target - 1];
    if (erase(target, root[pre])) { root.erase(pre); }
    if (!root.count(val)) { root[val] = init(1, n); }
    col[target - 1] = val;
    add(target, root[val], a[target - 1]);
  }
  void modifyVal(int target, int val) {
    int cur = col[target - 1];
    a[target - 1] = val;
    add(target, root[cur], val);
  }
  int _querySum(int l, int r, int u) {
    int s = tree[u].l, t = tree[u].r;
    if (u == 0) { return 0; }
    if (l <= s && t <= r) { return tree[u].sum; }
    int mid = (s + t) >> 1, lc = tree[u].lc, rc = tree[u].rc;
    int res = 0;
    if (mid >= l) { res += _querySum(l, r, lc); }
    if (mid <  r) { res += _querySum(l, r, rc); }
    return res;
  }
  int querySum(int l, int r, int cur) {
    return _querySum(l, r, root[cur]);
  }
  int _queryMax(int l, int r, int u) {
    int s = tree[u].l, t = tree[u].r;
    if (u == 0) { return INT_MIN; }
    if (l <= s && t <= r) { return tree[u].max; }
    int mid = (s + t) >> 1, lc = tree[u].lc, rc = tree[u].rc;
    int res = INT_MIN;
    if (mid >= l) { res = std::max(res, _queryMax(l, r, lc)); }
    if (mid <  r) { res = std::max(res, _queryMax(l, r, rc)); }
    return res;
  }
  int queryMax(int l, int r, int cur) {
    return _queryMax(l, r, root[cur]);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  std::vector<int> va(n), vb(n);
  for (int i = 0; i < n; i++) {
    std::cin >> va[i] >> vb[i];
  }

  std::vector<std::vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  std::vector<int> fa(n), son(n), siz(n), dep(n);
  std::function<void(int, int)> dfs1 = [&](int u, int frm) {
    fa[u] = frm, siz[u] = 1, dep[u] = dep[frm] + 1;
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      dfs1(v, u);
      siz[u] += siz[v];
      if (son[u] == 0 || siz[son[u]] < siz[v]) { son[u] = v; }
    }
  };

  std::vector<int> idx(n), top(n);
  int clk = 0;
  std::function<void(int, int)> dfs2 = [&](int u, int rt) {
    idx[u] = ++clk, top[u] = rt;
    if (son[u]) { dfs2(son[u], rt); }
    for (auto v : adj[u]) {
      if (v == son[u] || v == fa[u]) { continue; }
      dfs2(v, v);
    }
  };

  dfs1(0, 0), dfs2(0, 0);

  std::vector<int> col(n), val(n);
  for (int i = 0; i < n; i++) {
    val[idx[i] - 1] = va[i];
    col[idx[i] - 1] = vb[i];
  }

  SegTree st(n, col, val);
  st.build();

  auto querySumP2P = [&](int u, int v) {
    int res = 0, cur = st.col[idx[u] - 1];
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) { std::swap(u, v); }
      res += st.querySum(idx[top[u]], idx[u], cur);
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) { std::swap(u, v); }
    res += st.querySum(idx[u], idx[v], cur);
    return res;
  };

  auto queryMaxP2P = [&](int u, int v) {
    int res = INT_MIN, cur = st.col[idx[u] - 1];
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) { std::swap(u, v); }
      res = std::max(res, st.queryMax(idx[top[u]], idx[u], cur));
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) { std::swap(u, v); }
    res = std::max(res, st.queryMax(idx[u], idx[v], cur));
    return res;
  };

  while (q--) {
    std::string opt;
    int u, v;
    std::cin >> opt >> u >> v;
    if (opt == "CC") {
      st.modifyCol(idx[u - 1], v);
    } else if (opt == "CW") {
      st.modifyVal(idx[u - 1], v);
    } else if (opt == "QS") {
      std::cout << querySumP2P(u - 1, v - 1) << "\n";
    } else {
      std::cout << queryMaxP2P(u - 1, v - 1) << "\n";
    }
  }

  return 0;
}