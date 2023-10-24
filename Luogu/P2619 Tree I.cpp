/**
 * @file    P2619 Tree I.cpp
 * @author  ForgotDream
 * @brief   MST + WQS 二分
 * @date    2023-04-19
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
  void useFileInuput() {
    #ifndef ONLINE_JUDGE
    freopen("tmp.in", "r", stdin);
    freopen("tmp.out", "w", stdout);
    #endif
    return;
  }
};

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int n) : n(n) {
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    return;
  }

  void clear() {
    std::iota(fa.begin(), fa.end(), 0);
    return;
  }

  int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  }

  void merge(int u, int v) {
    fa[find(u)] = find(v);
    return;
  }
};

struct Edge {
  int u, v, w, col;
  Edge(int u, int v, int w, int col) : u(u), v(v), w(w), col(col) {}
};

static const bool operator<(const Edge &lhs, const Edge &rhs) {
  if (lhs.w == rhs.w) {
    return lhs.col < rhs.col;
  } else {
    return lhs.w < rhs.w;
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, need;
  std::cin >> n >> m >> need;

  int k = 0;

  std::vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w, col;
    std::cin >> u >> v >> w >> col;
    edges.emplace_back(u, v, w, col);
  }

  int L = -150, R = 150, ans = 0;
  DSU dsu(n + 1);
  while (L <= R) {
    int mid = (L + R) >> 1;

    dsu.clear();
    for (int i = 0; i < edges.size(); i++) {
      if (!edges[i].col) {
        edges[i].w += mid;
      }
    }

    std::sort(edges.begin(), edges.end());

    int wcnt = 0, sum = 0, cnt = 0;
    for (int i = 0; i < edges.size(); i++) {
      int u = edges[i].u, v = edges[i].v, w = edges[i].w;
      if (dsu.find(u) != dsu.find(v)) {
        dsu.merge(u, v);
        if (!edges[i].col) {
          wcnt++;
        }
        cnt++, sum += w;
      }
      if (cnt == n - 1) {
        break;
      }
    }

    if (wcnt >= need) {
      L = mid + 1;
      ans = sum - need * mid;
    } else {
      R = mid - 1;
    }

    for (int i = 0; i < edges.size(); i++) {
      if (!edges[i].col) {
        edges[i].w -= mid;
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}