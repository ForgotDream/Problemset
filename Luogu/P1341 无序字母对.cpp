/**
 * @file    P1341 无序字母对.cpp
 * @author  ForgotDream
 * @brief   Euler Tour
 * @date    2023-05-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 52;

struct Edge {
  int u, v, w;
  bool deleted;
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) { deleted = false; }
  void del() { deleted = true; }
};

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int _n) : n(_n) {
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
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
    return true;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  DSU dsu(N);

  int n;
  std::cin >> n;

  auto encode = [](char c) {
    if (std::isupper(c)) {
      return c - 'A';
    } else {
      return c - 'a' + 26;
    }
  };
  auto decode = [](int i) {
    if (i >= 0 && i < 26) {
      return char(i + 'A');
    } else {
      return char(i - 26 + 'a');
    }
  };

  std::vector<Edge> edges;
  std::vector<std::vector<int>> g(N);

  auto add = [&](int u, int v) {
    edges.emplace_back(u, v, 0);
    g[u].push_back(edges.size() - 1);
  };

  std::vector<int> deg(N);
  for (int i = 0; i < n; i++) {
    char a, b;
    std::cin >> a >> b;
    add(encode(a), encode(b)), add(encode(b), encode(a));
    deg[encode(b)]++, deg[encode(a)]++;
    dsu.merge(encode(a), encode(b));
  }

  int oddCnt = 0;
  for (int i = 0; i < N; i++) {
    if (dsu.find(i) == i && deg[i]) {
      oddCnt++;
    }
  }
  if (oddCnt != 1) {
    std::cout << "No Solution\n";
    return 0;
  }

  int pivot = -1;
  oddCnt = 0;
  for (int i = 0; i < N; i++) {
    if (pivot == -1 && deg[i]) {
      pivot = i;
    } else if (!(deg[pivot] & 1) && (deg[i] & 1)) {
      pivot = i;
    }
    if (deg[i] & 1) {
      oddCnt++;
    }
  }

  if (oddCnt && oddCnt != 2) {
    std::cout << "No Solution\n";
    return 0;
  }

  for (int i = 0; i < N; i++) {
    std::sort(g[i].begin(), g[i].end(), [&](const int &lhs, const int &rhs) {
      return edges[lhs].v < edges[rhs].v;
    });
  }

  std::vector<int> cnt(N);
  std::stack<int> ans;
  std::function<void(int)> dfs = [&](int u) {
    for (int &i = cnt[u]; i < g[u].size();) {
      if (!edges[g[u][i]].deleted) {
        edges[g[u][i]].del();
        edges[g[u][i] ^ 1].del();
        int v = edges[g[u][i]].v;
        i++;
        dfs(v);
      } else {
        i++;
      }
    }
    ans.push(u);
  };

  dfs(pivot);

  while (!ans.empty()) {
    std::cout << decode(ans.top());
    ans.pop();
  }
  std::cout << "\n";

  return 0;
}