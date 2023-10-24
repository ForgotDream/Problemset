/**
 * @file    P4180 严格次小生成树.cpp
 * @author  ForgotDream
 * @brief   Kruskal + 倍增
 * @date    2023-04-17
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
  Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
};

bool operator<(const Edge &lhs, const Edge &rhs) {
  return lhs.w < rhs.w;
}

struct Tree {
  int n, maxDep;
  std::vector<std::vector<std::pair<int, int>>> e;
  std::vector<int> dep;
  std::vector<std::vector<int>> anc, max, semi;

  Tree(int n) : n(n), maxDep(22) {
    e.resize(n + 1);
    dep.resize(n + 1);
    anc.resize(n + 1, std::vector<int>(maxDep));
    max = semi = anc;
    return;
  }

  void add(int u, int v, int w) {
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
    return;
  }

  void dfs(int u, int frm) {
    dep[u] = dep[frm] + 1;
    anc[u][0] = frm;
    semi[u][0] = INT_MIN;

    for (int i = 1; (1 << i) <= dep[u]; i++) {
      anc[u][i] = anc[anc[u][i - 1]][i - 1];

      std::vector<int> tmp = {
        max[u][i - 1],
        max[anc[u][i - 1]][i - 1],
        semi[u][i - 1],
        semi[anc[u][i - 1]][i - 1],
      };
      std::sort(tmp.begin(), tmp.end(), std::greater<int>());

      max[u][i] = tmp[0];
      int pivot = 1;
      while (pivot < 4 && tmp[pivot] == tmp[0]) {
        pivot++;
      }
      if (pivot == 4) {
        semi[u][i] = INT_MIN;
      } else {
        semi[u][i] = tmp[pivot];
      }
    }

    for (auto i : e[u]) {
      int v = i.first, w = i.second;
      if (v == frm) {
        continue;
      }
      max[v][0] = w;
      dfs(v, u);
    }

    return;
  }

  int getLCA(int u, int v) {
    if (dep[u] < dep[v]) {
      std::swap(u, v);
    }
    for (int i = maxDep - 1; i >= 0; i--) {
      if (dep[anc[u][i]] >= dep[v]) {
        u = anc[u][i];
      }
    }
    if (u == v) {
      return u;
    }
    for (int i = maxDep - 1; i >= 0; i--) {
      if (anc[u][i] != anc[v][i]) {
        u = anc[u][i], v = anc[v][i];
      }
    }

    return anc[u][0];
  }

  int findMax(int u, int v, int w) {
    int res = INT_MIN;

    for (int i = maxDep - 1; i >= 0; i--) {
      if (dep[anc[u][i]] >= dep[v]) {
        if (w != max[u][i]) {
          res = std::max(res, max[u][i]);
        } else {
          res = std::max(res, semi[u][i]);
        }
        u = anc[u][i];
      }
    }

    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edges.emplace_back(u, v, w);
  }

  std::sort(edges.begin(), edges.end());

  // Use Kruskal to get the MST
  DSU dsu(n);
  Tree tree(n);
  int cnt = 0;
  i64 sum = 0;
  std::vector<bool> used(m);
  for (int i = 0; i < m; i++) {
    int u = edges[i].u, v = edges[i].v, w = edges[i].w;
    if (dsu.find(u) != dsu.find(v)) {
      dsu.merge(u, v);
      cnt++, sum += w;
      used[i] = true;
      tree.add(u, v, w);
      if (cnt == n - 1) {
        break;
      }
    }
  }

  tree.dfs(1, 0);

  i64 ans = LONG_LONG_MAX;
  for (int i = 0; i < m; i++) {
    if (!used[i]) {
      int u = edges[i].u, v = edges[i].v, w = edges[i].w;
      int lca = tree.getLCA(u, v);
      i64 maxA = tree.findMax(u, lca, w);
      i64 maxB = tree.findMax(v, lca, w);
      // std::cerr << u << " " << v << " " << w << " ";
      // std::cerr << maxA << " " << maxB << "\n";
      if (std::max(maxA, maxB) > INT_MIN) {
        ans = std::min(ans, sum - std::max(maxA, maxB) + w);
      }
    }
  }

  if (ans == LONG_LONG_MAX) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }

  return 0;
}