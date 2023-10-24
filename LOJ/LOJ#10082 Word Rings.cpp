/**
 * @file    LOJ#10082 Word Rings.cpp
 * @author  ForgotDream
 * @brief   SPFA Check Circle
 * @date    2023-04-28
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
}

struct Graph {
  static constexpr int INF = 1e9;
  struct Edge {
    int u, v;
    f80 w;
    Edge(int _u = 0, int _v = 0, f80 _w = 0) : u(_u), v(_v), w(_w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;

  Graph(int _n) : n(_n) {
    e.resize(n);
    return;
  }

  void add(const int &u, const int &v, const f80 &w) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }

  std::vector<f80> dis;
  std::vector<bool> vis;

  bool spfa(int u, const f80 &delta) {
    vis[u] = true;

    for (int i : e[u]) {
      int v = edges[i].v;
      f80 w = edges[i].w;
      if (dis[v] < dis[u] + w - delta) {
        dis[v] = dis[u] + w - delta;
        if (vis[v]) {
          return true;
        } else if (spfa(v, delta)) {
          return true;
        }
      }
    }

    vis[u] = false;
    return false;
  }

  void clear() {
    dis.clear(), vis.clear();
    dis.resize(n, 0), vis.resize(n, false);
    return;
  }

  bool findCircle(const f80 &delta) {
    clear();
    for (int i = 0; i < 26 * 26; i++) {
      if (spfa(i, delta)) {
        return true;
      }
    }
    return false;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(2);

  constexpr f80 EPS = 1e-8;
  auto convert = [](const char &a, const char &b) {
    return (a - 'a') * 26 + (b - 'a');
  };

  int n;
  while (std::cin >> n && n) {
    Graph g(26 * 26);

    for (int i = 0; i < n; i++) {
      std::string s;
      std::cin >> s;
      int len = s.length();
      g.add(convert(s[0], s[1]), convert(s[len - 2], s[len - 1]), len);
    }

    f80 l = 0, r = 1e5;
    while (r - l > EPS) {
      f80 mid = (l + r) / 2;
      if (g.findCircle(mid)) {
        l = mid;
      } else {
        r = mid;
      }
    }

    if (std::fabs(l) <= EPS) {
      std::cout << "No solution\n";
    } else {
      std::cout << l << "\n";
    }
  }

  return 0;
}