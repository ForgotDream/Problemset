/**
 * @file    LOJ#10066 新的开始.cpp
 * @author  ForgotDream
 * @brief   MST
 * @date    2023-04-16
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
    fa.resize(n + 1);
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
  int u, v, w;
  Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

bool operator<(const Edge &lhs, const Edge &rhs) {
  return lhs.w < rhs.w;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<Edge> edges;
  for (int i = 0; i < n; i++) {
    int w;
    std::cin >> w;
    edges.emplace_back(n + 1, i, w);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int w;
      std::cin >> w;
      if (j > i) {
        edges.emplace_back(i, j, w);
      }
    }
  }

  std::sort(edges.begin(), edges.end());

  DSU dsu(n + 1);
  int ans = 0, cnt = 0;
  for (int i = 0; i < edges.size(); i++) {
    int u = edges[i].u, v = edges[i].v, w = edges[i].w;
    if (dsu.find(u) != dsu.find(v)) {
      dsu.merge(u, v);
      cnt++;
      ans += w;
      if (cnt == n + 1) {
        break;
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}