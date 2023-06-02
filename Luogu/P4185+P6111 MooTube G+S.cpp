/**
 * @file    P4185+P6111 MooTube G+S.cpp
 * @author  ForgotDream
 * @brief   DSU + Offline Algorithm
 * @date    2023-05-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

struct DSU {
  int n;
  std::vector<int> fa, siz;

  DSU(int _n) : n(_n) {
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    siz.resize(n + 1, 1);
    return;
  }

  int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  }

  bool merge(int u, int v) {
    int fau = find(u), fav = find(v);
    if (fau == fav) {
      return false;
    }
    fa[fau] = fav;
    siz[fav] += siz[fau];
    return true;
  }

  int sizeOf(int u) {
    return siz[u];
  }

};

struct Edge {
  int u, v, w;
};

bool operator<(const Edge &lhs, const Edge &rhs) {
  return lhs.w > rhs.w;
}

struct Query {
  int k, v, id;
};

bool operator<(const Query &lhs, const Query &rhs) {
  return lhs.k > rhs.k;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  std::vector<Edge> edges(n - 1);
  for (int i = 0; i < n - 1; i++) {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
  }

  std::vector<Query> query(q);
  for (int i = 0; i < q; i++) {
    std::cin >> query[i].k >> query[i].v;
    query[i].id = i;
  }

  std::sort(edges.begin(), edges.end());
  std::sort(query.begin(), query.end());

  DSU dsu(n + 1);
  int pivot = 0;
  std::vector<int> ans(q);
  for (int i = 0; i < q; i++) {
    while (pivot < n - 1 && query[i].k <= edges[pivot].w) {
      dsu.merge(edges[pivot].u, edges[pivot].v);
      pivot++;
    }
    ans[query[i].id] = dsu.sizeOf(dsu.find(query[i].v)) - 1;
  }

  for (int i = 0; i < q; i++) {
    std::cout << ans[i] << "\n";
  }

  return 0;
}