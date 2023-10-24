/**
 * @file    CF1192B Dynamic Diameter.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + Euler Order
 * @date    2023-05-10
 */
#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  struct Node {
    i64 max, min, ld, rd, diam, tag;
    Node() {
      max = min = ld = rd = diam = tag = 0;
    }
  };
  std::vector<Node> tr;
  std::vector<i64> dep;
  std::vector<int> a;

  SegTree(int _n, const std::vector<i64> &_d, const std::vector<int> &_a) {
    n = _n;
    dep = _d;
    a = _a;
    tr.resize((n << 2) + 1);
  }

  void tagging(int u, i64 val) {
    tr[u].max += val, tr[u].min += val;
    tr[u].ld -= val, tr[u].rd -= val;
    tr[u].tag += val;
  }

  Node pushup(const Node &lhs, const Node &rhs) {
    Node res;
    res.max = std::max(lhs.max, rhs.max);
    res.min = std::min(lhs.min, rhs.min);
    res.ld = std::max({lhs.ld, rhs.ld, lhs.max - 2 * rhs.min});
    res.rd = std::max({lhs.rd, rhs.rd, rhs.max - 2 * lhs.min});
    res.diam = std::max({lhs.diam, rhs.diam, lhs.max + rhs.rd, rhs.max + lhs.ld});
    return res;
  }

  void pushdown(int u) {
    if (!tr[u].tag) {
      return;
    }
    int lc = u << 1, rc = u << 1 | 1;
    tagging(lc, tr[u].tag), tagging(rc, tr[u].tag);
    tr[u].tag = 0;
  }

  void build(int l, int r, int u) {
    if (l == r) {
      tagging(u, dep[a[l]]);
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
    tr[u] = pushup(tr[lc], tr[rc]);
  }

  void modify(int l, int r, int s, int t, int u, i64 val) {
    if (l <= s && t <= r) {
      tagging(u, val);
      return;
    }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (l <= mid) {
      modify(l, r, s, mid, lc, val);
    }
    if (r > mid) {
      modify(l, r, mid + 1, t, rc, val);
    }
    tr[u] = pushup(tr[lc], tr[rc]);
  }
};

struct Edge {
  int u, v, id;
  i64 w;
  Edge(int _u, int _v, i64 _w, int _id) {
    u = _u, v = _v, w = _w, id = _id;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, q;
  i64 W;
  std::cin >> n >> q >> W;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    i64 w;
    std::cin >> u >> v >> w;
    edges.emplace_back(u, v, w, i), edges.emplace_back(v, u, w, i);
    g[u].push_back(edges.size() - 2), g[v].push_back(edges.size() - 1);
  }

  std::vector<int> in(n + 1), out(n + 1), eulerOrder(2 * n), edgeID(n + 1);
  int idx = 0;
  std::vector<i64> dep(n + 1);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    eulerOrder[++idx] = u, in[u] = idx;
    for (auto i : g[u]) {
      int v = edges[i].v, id = edges[i].id;
      i64 w = edges[i].w;
      if (v == frm) {
        continue;
      }
      dep[v] = dep[u] + w;
      edgeID[id] = v;
      dfs(v, u);
      eulerOrder[++idx] = u;
    }
    out[u] = idx;
  };

  dfs(1, 0);

  SegTree st(idx, dep, eulerOrder);
  st.build(1, idx, 1);

  i64 lst = 0;
  for (int i = 0; i < q; i++) {
    i64 d, e;
    std::cin >> d >> e;
    i64 D = (d + lst) % (n - 1), E = (e + lst) % W;
    // std::cerr << D << " " << in[edgeID[D]] << " " << out[edgeID[D]] << " " << edgeID[D] << "\n";
    // std::cerr << E << " " << E - edges[D].w << "\n";
    st.modify(in[edgeID[D]], out[edgeID[D]], 1, idx, 1, E - edges[2 * D].w);
    edges[2 * D].w = E, edges[(2 * D) ^ 1].w = E, lst = st.tr[1].diam;
    std::cout << lst << "\n";
  }

  return 0;
}