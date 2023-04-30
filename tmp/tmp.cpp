/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-04-30
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
    Edge() : u(0), v(0), w(0) {}
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;
  std::vector<bool> vis, deleted;
  std::vector<int> match;
  std::vector<std::vector<bool>> reach;

  Graph(int _n) : n(_n) {
    e.resize(n);
    vis.resize(n), deleted.resize(n);
    match.resize(n);
    reach.resize(n, std::vector<bool>(n));
    return;
  }

  void add(int u, int v, int w = 0) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    reach[u][v] = true;
    return;
  }

  void floyd() {
    for (int k = 1; k < n; k++) {
      for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
          if (reach[i][k] && reach[k][j]) {
            reach[i][j] = true;
          }
        }
      }
    }

    return;
  }

  bool dfs(int u) {
    for (int v = 1; v < n; v++) {
      // int v = edges[i].v;
      if (!vis[v] && reach[u][v]) {
        // std::cerr << u << " " << v << "\n";
        if (deleted[v]) {
          continue;
        }
        vis[v] = true;
        if (!match[v] || dfs(match[v])) {
          match[v] = u;
          return true;
        }
      }
    }
    return false;
  }

  void resetDel() {
    std::fill(deleted.begin(), deleted.end(), false);
    return;
  }

  void del(int u) {
    deleted[u] = true;
    return;
  }

  int binaryMatching() {
    int res = 0;
    std::fill(match.begin(), match.end(), 0);

    for (int i = 1; i < n; i++) {
      if (deleted[i]) continue;
      std::fill(vis.begin(), vis.end(), false);
      if (dfs(i)) {
        res++;
      }
    }

    return res;
  }

  bool reachable(int i, int j) {
    return reach[i][j] || reach[j][i] || i == j;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  Graph g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    g.add(u, v);
  }

  g.floyd();

  int match  = n - g.binaryMatching();
  std::cout << match << "\n";

  std::vector<bool> onPath(n + 1);  
  for (int i = 1; i <= n; i++) {
    g.resetDel();
    int cnt = n;
    for (int j = 1; j <= n; j++) {
      if (g.reachable(i, j)) {
        g.del(j);
        cnt--;
      }
    }
    onPath[i] = (cnt - g.binaryMatching() == match - 1);
  }

  for (int delta = 0; delta < n; delta++) {
    int clk = 0;
    std::vector<int> col(n + 1);
    std::vector<bool> ans(n + 1, false);

    for (int i = 1; i <= n; i++) {
      if (onPath[(i + delta) % n] && !col[(i + delta) % n]) {
        ans[(i + delta) % n] = true;
        ++clk;
        for (int j = 1; j <= n; j++) {
          if (g.reachable((i + delta) % n, j)) {
            col[j] = clk;
          }
        }
      }
    }

    int ansCnt = 0;
    for (int i = 1; i <= n; i++) {
      if (ans[i]) {
        ansCnt++;
      }   
    }

    if (ansCnt == match) {
      for (int i = 1; i <= n; i++) {
        if (ans[i]) {
          std::cout << i << " ";
        }   
      } 
      std::cout << "\n";
      break;
    }
  }

  return 0;
}