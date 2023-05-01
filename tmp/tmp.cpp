/**
 * @file    
 * @author  ForgotDream
 * @brief   
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

  int findDCC(std::vector<std::vector<int>> &ans, std::vector<int> &siz) {
    ans.clear(), siz.clear();
    ans.resize(1), siz.resize(1);
    
    std::vector<int> dfn(n), low(n);
    std::stack<int> st;
    int clk = 0, dccCnt = 0;

    std::function<void(int, int)> tarjan = [&](int u, int rt) {
      dfn[u] = low[u] = ++clk;
      st.push(u);
      
      if (u == rt && e[u].size() == 0) {
        dccCnt++;
        ans.emplace_back(1, u);
        siz.push_back(1);
      }

      for (auto i : e[u]) {
        int v = edges[i].v;
        if (!dfn[v]) {
          tarjan(v, rt);
          low[u] = std::min(low[u], low[v]);
          
          if (low[v] >= dfn[u]) {
            int pivot;
            dccCnt++;
            siz.push_back(0);
            ans.emplace_back(0);

            do {
              pivot = st.top();
              st.pop();
              ans[dccCnt].push_back(pivot);
              siz[dccCnt]++;
            } while (pivot != v);

            ans[dccCnt].push_back(u);
            siz[dccCnt]++;
          }
        } else {
          low[u] = std::min(low[u], dfn[v]);
        }
      }
      
      return;
    };

    for (int i = 1; i < n; i++) {
      if (!dfn[i]) {
        tarjan(i, i);
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
  std::vector ans(0, std::vector<int>());

  int cnt = g.findDCC(ans, siz);

  std::cout << cnt << "\n";

  for (int i = 1; i <= cnt; i++) {
    std::cout << ans[i].size() << " ";
    for (int j = 0; j < ans[i].size(); j++) {
      std::cout << ans[i][j] << " \n"[j == ans[i].size() - 1];
    }
  }

  return 0;
}