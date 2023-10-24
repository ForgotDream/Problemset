/**
 * @file    P8436 边双连通分量.cpp
 * @author  ForgotDream
 * @brief   e-DCC
 * @date    2023-05-01
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

  int findDCC(std::vector<int> &bln, std::vector<int> &siz) {
    bln.clear(), siz.clear();
    bln.resize(n), siz.push_back(0);
    
    std::vector<int> dfn(n), low(n);
    std::stack<int> st;
    int clk = 0, dccCnt = 0;

    std::function<void(int, int)> tarjan = [&](int u, int inEdge) {
      dfn[u] = low[u] = ++clk;
      st.push(u);

      for (auto i : e[u]) {
        int v = edges[i].v;
        if (!dfn[v]) {
          tarjan(v, i);
          low[u] = std::min(low[u], low[v]);
        } else if (i != (inEdge ^ 1)) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (low[u] == dfn[u]) {
        int pivot;
        ++dccCnt;
        siz.push_back(0);
        do {
          pivot = st.top();
          st.pop();
          bln[pivot] = dccCnt;
          siz[dccCnt]++;
        } while (pivot != u);
      }
    };

    for (int i = 1; i < n; i++) {
      if (!dfn[i]) {
        tarjan(i, 0);
      }
    }

    return dccCnt;
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
    if (u == v) {
      continue;
    }
    g.add(u, v), g.add(v ,u);
  }

  std::vector<int> bln, siz;
  int cnt = g.findDCC(bln, siz);

  std::cout << cnt << "\n";

  std::vector ans(cnt + 1, std::vector<int>());
  for (int i = 1; i <= n; i++) {
    ans[bln[i]].push_back(i);
  }

  for (int i = 1; i <= cnt; i++) {
    std::cout << ans[i].size() << " ";
    for (int j = 0; j < ans[i].size(); j++) {
      std::cout << ans[i][j] << " \n"[j == ans[i].size() - 1];
    }
  }

  return 0;
}