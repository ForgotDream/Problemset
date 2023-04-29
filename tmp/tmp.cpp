/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-04-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace Helper {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}

void debug(const std::string &s) {
  std::clog << s << "\n";
  return;
}
}

struct Graph {
  static constexpr int INF = 1e9;
  struct Edge {
    int u, v, w;
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;
  std::vector<int> in;

  Graph(int _n) : n(_n) {
    e.resize(n);
    in.resize(n);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int a, b;
  std::cin >> a >> b;
  std::cout << a + b << "\n";

  // int n, m;
  // std::cin >> n >> m;

  // Graph g(n + 1);
  // for (int i = 0; i < m; i++) {
  //   int u, v, w;
  //   std::cin >> u >> v >> w;
  //   g.add(u, v, w);
  // }

  return 0;
}