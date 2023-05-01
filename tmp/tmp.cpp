/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-05-02
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
  std::cerr << s << "\n";
  return;
}
}

struct Graph {
  static constexpr int INF = 1e9;
  int n;
  struct Edge {
    int u, v, w;
    Edge(int _u, int _v, int _w = 0) : u(_u), v(_v), w(_w) {}
  };
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;

  Graph(int _n) : n(_n) {
    e.resize(n);
    return;
  }

  void add(int u, int v, int w = 0) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  return 0;
}