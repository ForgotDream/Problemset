/**
 * @file    P3119 Grass Cownoisseur G.cpp
 * @author  ForgotDream
 * @brief   Tarjan + SSSP
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

  int findScc(std::vector<int> &bln, std::vector<int> &siz) {
    bln.clear(), siz.clear();
    bln.resize(n), siz.resize(1);
    
    std::vector<int> dfn(n), low(n);
    std::stack<int> st;
    std::vector<bool> ins(n);
    int clk = 0, sccCnt = 0;

    std::function<void(int)> tarjan = [&](int u) {
      dfn[u] = low[u] = ++clk;
      st.push(u), ins[u] = true;

      for (auto i : e[u]) {
        int v = edges[i].v;
        if (!dfn[v]) {
          tarjan(v);
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
        tarjan(i);
      }
    }

    return sccCnt;
  }

  std::vector<int> spfa(int s) {
    std::vector<int> dis(n, -INF);
    std::vector<bool> vis(n, false);
    std::queue<int> q;

    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), vis[u] = false;
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] < dis[u] + w) {
          dis[v] = dis[u] + w;
          if (!vis[v]) {
            vis[v] = true, q.push(v);
          }
        }
      }
    }

    return dis;
  }
  
};

void solve() {
  std::vector<int> t(24);
  for (int i = 0; i < 24; i++) {
    std::cin >> t[i];
  }

  return;
}

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

  std::vector<int> bln, siz;
  int cnt = g.findScc(bln, siz);

  Graph aft(2 * cnt + 1);
  for (auto i : g.edges) {
    int u = i.u, v = i.v;
    if (bln[u] != bln[v]) {
      aft.add(bln[u], bln[v], siz[bln[u]]);
      aft.add(bln[u] + cnt, bln[v] + cnt, siz[bln[u]]);
      aft.add(bln[v], bln[u] + cnt, siz[bln[v]]);
    }
  }

  auto dis = aft.spfa(bln[1]);

  std::cout << dis[bln[1] + cnt] << "\n";

  return 0;
}