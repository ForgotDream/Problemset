/**
 * @file    LOJ#10094 消息的传递.cpp
 * @author  ForgotDream
 * @brief   SCC + Topo
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
    Edge() : u(0), v(0), w(0) {}
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
  };
  int n;
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

  int tarjan(std::vector<int> &bln, std::vector<int> &siz) {
    bln.clear(), siz.clear();
    bln.resize(n), siz.resize(1);
    
    std::vector<int> dfn(n), low(n);
    std::stack<int> st;
    std::vector<bool> ins(n);
    int clk = 0, sccCnt = 0;

    std::function<void(int)> dfs = [&](int u) {
      dfn[u] = low[u] = ++clk;
      st.push(u), ins[u] = true;

      for (auto i : e[u]) {
        int v = edges[i].v;
        if (!dfn[v]) {
          dfs(v);
          low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (low[u] == dfn[u]) {
        siz.push_back(0);
        sccCnt++;

        int pivot = st.top();
        do {
          pivot = st.top();
          st.pop();
          bln[pivot] = sccCnt;
          ins[pivot] = false;
          siz[sccCnt]++;
        } while (u != pivot);
      }

      return;
    };

    for (int i = 1; i < n; i++) {
      if (!dfn[i]) {
        dfs(i);
      }
    }

    return sccCnt;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  Graph g(n + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int c;
      std::cin >> c;
      if (c) {
        g.add(i + 1, j + 1);
      }
    }
  }

  std::vector<int> bln, siz;
  int cnt = g.tarjan(bln, siz);

  std::vector<int> in(cnt + 1);
  for (auto i : g.edges) {
    int u = i.u, v = i.v;
    if (bln[u] != bln[v]) {
      in[bln[v]]++;
    }
  }

  int ans = 0;
  for (int i = 1; i <= cnt; i++) {
    if (!in[i]) {
      ans++;
    }
  }

  std::cout << ans << "\n";

  return 0;
}