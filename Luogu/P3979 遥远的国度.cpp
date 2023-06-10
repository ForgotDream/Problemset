/**
 * @file    P3979 遥远的国度.cpp
 * @author  ForgotDream
 * @brief   HLD
 * @date    2023-06-05
 */
#include <bits/stdc++.h>

using i64 = long long;

const int inf = INT_MAX;

struct SegTree {
  int n;
  struct Node {
    int min, tag;
    Node(int _v = 0, int _t = 0) { min = _v, tag = _t; }
  };
  std::vector<Node> tree;
  std::vector<int> a;

  SegTree(int _n, const std::vector<int> &_a) {
    n = _n, a = _a;
    tree.resize((n << 2) + 1);
  }

  void pushup(int u) {
    int lc = u << 1, rc = u << 1 | 1;
    tree[u].min = std::min(tree[lc].min, tree[rc].min);
  }

  void tagging(int u, int val) { tree[u].tag = tree[u].min = val; }

  void pushdown(int u) {
    if (!tree[u].tag) { return; }
    tagging(u << 1, tree[u].tag), tagging(u << 1 | 1, tree[u].tag);
    tree[u].tag = 0;
  }

  void build(int l, int r, int u) {
    if (l == r) {
      tree[u].min = a[l - 1];
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
    pushup(u);
  }

  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) {
      tagging(u, val);
      return;
    }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (mid >= l) { modify(l, r, s, mid, lc, val); }
    if (mid <  r) { modify(l, r, mid + 1, t, rc, val); }
    pushup(u);
  }

  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      return tree[u].min;
    }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    int res = inf;
    if (mid >= l) { res = std::min(res, query(l, r, s, mid, lc)); }
    if (mid <  r) { res = std::min(res, query(l, r, mid + 1, t, rc)); }
    return res; 
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  std::vector<int> siz(n), dep(n), fa(n), son(n);
  std::function<void(int, int)> dfs1 = [&](int u, int frm) {
    siz[u] = 1, dep[u] = dep[frm] + 1, fa[u] = frm;
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
    top[u] = rt, idx[u] = clk++;
    if (son[u]) { dfs2(son[u], rt); }
    for (auto v : adj[u]) {
      if (v == fa[u] || v == son[u]) { continue; }
      dfs2(v, v);
    }
  };

  dfs1(0, 0), dfs2(0, 0);

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> trans(n);
  for (int i = 0; i < n; i++) {
    trans[idx[i]] = a[i];
  }

  SegTree st(n, trans);
  st.build(1, n, 1);

  int cur;
  std::cin >> cur;
  cur--;

  auto modifyP2P = [&](int u, int v, int val) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) { std::swap(u, v); }
      st.modify(idx[top[u]] + 1, idx[u] + 1, 1, n, 1, val);
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) { std::swap(u, v); }
    st.modify(idx[u] + 1, idx[v] + 1, 1, n, 1, val);
  };

  auto getLCA = [&](int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) { std::swap(u, v); }
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) { std::swap(u, v); }
    return u;
  };

  auto find = [&](int u, int v) {
    while (top[u] != top[v] && top[u] != top[fa[top[v]]]) { v = fa[top[v]]; }
    while (fa[v] != u) { v = fa[v]; }
    return v;
  };

  while (m--) {
    int opt;
    std::cin >> opt;

    if (opt == 1) {
      int u;
      std::cin >> u;
      cur = --u;
    } else if (opt == 2) {
      int u, v, val;
      std::cin >> u >> v >> val;
      u--, v--;
      modifyP2P(u, v, val);
    } else {
      int u;
      std::cin >> u;
      u--;
      int lca = getLCA(u, cur);

      if (u == cur) {
        std::cout << st.query(1, n, 1, n, 1) << "\n";
      } else if (lca == cur || (lca != cur && lca != u)) {
        std::cout << st.query(idx[u] + 1, idx[u] + siz[u], 1, n, 1) << "\n";
      } else {
        int p = find(u, cur);
        int res = st.query(1, idx[p], 1, n, 1);
        res = std::min(res, st.query(idx[cur] + siz[cur] + 1, n, 1, n, 1));
        std::cout << res << "\n";
      }
    }
  }

  return 0;
}