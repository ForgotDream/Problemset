/**
#include <iomanip>
 * @file    LOJ#10065 北极通讯网络.cpp
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

struct Edge {
  int u, v;
  f80 w;
  Edge(int u, int v, f80 w) : u(u), v(v), w(w) {}
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

bool operator<(const Edge &lhs, const Edge& rhs) {
  return lhs.w < rhs.w;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<std::pair<int, int>> point(n);
  for (int i = 0; i < n; i++) {
    std::cin >> point[i].first >> point[i].second;
  }

  auto getDis = [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> f80 {
    return std::hypot(a.first - b.first, a.second - b.second);
  };

  std::vector<Edge> edges;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      edges.emplace_back(i, j, getDis(point[i], point[j]));
    }
  }

  std::sort(edges.begin(), edges.end());

  int cnt = n;
  f80 ans;
  DSU dsu(n);
  for (int i = 0; i < edges.size(); i++) {
    if (cnt == k) {
      break;
    }
    int u = edges[i].u, v = edges[i].v;
    f80 w = edges[i].w;
    if (dsu.find(u) != dsu.find(v)) {
      dsu.merge(u, v);
      cnt--;
      ans = w;
    }
  }

  std::cout << std::fixed << std::setprecision(2) << ans << "\n";

  return 0;
}