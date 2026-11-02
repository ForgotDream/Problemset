/*
 * @file    LOJ#5049 「JOISC 2025 Day2」宇宙怪盗.cpp
 * @author  ForgotDream
 * @brief   Centroid Decomposition, Topo Sort
 * @date    2026-10-31
 */
#include <bits/stdc++.h>
#include "thief.h"

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

// int query(std::vector<int> x) {}
// void answer(int A, int B) {}

void solve(int n, int m, std::vector<int> U, std::vector<int> V) {
  std::vector adj(n, std::vector<pii>());
  for (int i = 0; i < m; i++) {
    adj[U[i]].emplace_back(V[i], i);
    adj[V[i]].emplace_back(U[i], i);
  }

  std::vector tree(n, std::vector<pii>());
  std::vector<bool> in_tree(m), vis(n);
  std::vector<int> tree_edges;

  std::queue<int> q;
  q.push(0), vis[0] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto [v, e] : adj[u]) {
      if (vis[v]) continue;
      vis[v] = true, in_tree[e] = true;
      tree_edges.push_back(e);
      tree[u].emplace_back(v, e), tree[v].emplace_back(u, e);
      q.push(v);
    }
  }

  std::vector<std::vector<signed char>> grp, ins;
  int dfn = 0;
  std::vector<int> bln(m), fa(n), siz(n);

  auto split = [&](auto &&self, const std::vector<int> &edges, int depth) -> void {
    if (edges.empty()) return;
    if (edges.size() == 1 && depth > 0) return;

    if (int(grp.size()) <= depth) {
      grp.emplace_back(m, -1);
      ins.emplace_back(m, -1);
    }

    if (edges.size() == 1) {
      int e = edges[0];
      grp[depth][e] = 0;
      ins[depth][e] = 1;
      return;
    }

    int cur = ++dfn;
    for (auto e : edges) bln[e] = cur;

    int rt = U[edges[0]];
    std::queue<int> q;
    std::vector<int> ord;
    fa[rt] = -1, q.push(rt);

    while (!q.empty()) {
      int u = q.front();
      q.pop(), ord.push_back(u);

      for (auto [v, e] : tree[u]) {
        if (bln[e] != cur || v == fa[u]) continue;
        fa[v] = u, q.push(v);
      }
    }

    for (auto u : ord) siz[u] = 1;
    for (int k = ord.size() - 1; ~k; k--) {
      int u = ord[k];
      if (~fa[u]) siz[fa[u]] += siz[u];
    }

    int c = -1, mn = INT_MAX;
    for (auto u : ord) {
      int mx = ord.size() - siz[u];
      for (auto [v, e] : tree[u]) {
        if (bln[e] != cur || v == fa[u]) continue;
        mx = std::max(mx, siz[v]);
      }
      if (mx < mn) c = u, mn = mx;
    }

    std::vector<std::vector<int>> brns;
    
    for (auto [v, e] : tree[c]) {
      if (bln[e] != cur) continue;

      std::vector<int> brn;
      std::stack<std::array<int, 3>> st;
      st.push({v, c, e});

      while (!st.empty()) {
        auto [u, frm, ei] = st.top();
        st.pop();
        brn.push_back(ei);
        ins[depth][ei] = (U[ei] == u ? 0 : 1);

        for (auto [v, ej] : tree[u]) {
          if (bln[ej] != cur || v == frm) continue;
          st.push({v, u, ej});
        }
      }
      brns.push_back(brn);
    }

    std::vector<std::vector<int>> ch(3);
    int hf = (edges.size() + 1) / 2;
    int sum = 0, stg = 0;

    for (auto &brn : brns) {
      int g;
      if (stg == 0 && sum + int(brn.size()) <= hf) g = 0, sum += brn.size();
      else if (stg == 0) g = 1, stg = 2;
      else g = 2;

      for (auto e : brn) grp[depth][e] = g, ch[g].push_back(e);
    }

    for (auto &g : ch) {
      if (!g.empty()) self(self, g, depth + 1);
    }
  };

  auto get_topo = [&](int depth, int t) {
    std::vector<int> d(m), in(n), topo, idx(n);

    for (auto e : tree_edges) {
      if (~grp[depth][e]) d[e] = ins[depth][e] ^ (grp[depth][e] != t);
    }

    for (auto e : tree_edges) ++in[d[e] ? U[e] : V[e]];

    std::queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      idx[u] = topo.size();
      topo.push_back(u);

      for (auto [v, e] : tree[u]) {
        if ((d[e] && V[e] == u) || (!d[e] && U[e] == u)) {
          if (!--in[v]) q.push(v);
        }
      }
    }

    for (int i = 0; i < m; i++) {
      if (in_tree[i]) continue;
      d[i] = (idx[U[i]] > idx[V[i]]);
    }

    return std::make_pair(d, topo);
  };

  split(split, tree_edges, 0);

  std::vector<int> topo, dir;
  bool flg = false;

  for (int dep = 0; dep < int(grp.size()); dep++) {
    for (int t = 0; t < 3; t++) {
      auto [cd, ct] = get_topo(dep, t);
      if (query(cd)) {
        dir = cd, topo = ct, flg = true;
        break;
      }
    }
    if (flg) break;
  }
  
  std::vector<int> idx(n);
  for (int i = 0; i < n; i++) idx[topo[i]] = i;

  auto check = [&](int l, int r) {
    auto d = dir;

    for (int i = 0; i < m; i++) {
      int u = U[i], v = V[i];
      if (idx[u] > idx[v]) std::swap(u, v);
      if (!(l <= idx[u] && idx[v] <= r)) d[i] ^= 1;
    }

    return query(d);
  };

  int lo = 0, hi = n - 1;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;
    if (check(mid, n - 1)) lo = mid;
    else hi = mid - 1;
  }
  int a = topo[lo];

  lo = 0, hi = n - 1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (check(0, mid)) hi = mid;
    else lo = mid + 1;
  }
  int b = topo[lo];

  answer(a, b);
}
