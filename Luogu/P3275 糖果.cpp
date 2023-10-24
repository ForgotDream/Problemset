/**
 * @file    P3275 糖果.cpp
 * @author  ForgotDream
 * @brief   差分约束 + Tarjan
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

  void addIn(int u) {
    in[u]++;
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

  std::vector<int> topo() {
    std::vector<int> f(n);
    std::queue<int> q;

    for (int i = 1; i < n; i++) {
      if (!in[i]) {
        q.push(i), f[i] = 1;
      }
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        f[v] = std::max(f[v], f[u] + w);
        if (!--in[v]) {
          q.push(v);
        }
      }
    }

    return f;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  Graph g(n + 1);
  for (int i = 0; i < k; i++) {
    int opt, u, v;
    std::cin >> opt >> u >> v;
    
    if (opt == 1) {
      g.add(u, v, 0), g.add(v, u, 0);
    } else if (opt == 2) {
      g.add(u, v, 1);
    } else if (opt == 3) {
      g.add(v, u, 0);
    } else if (opt == 4) {
      g.add(v, u, 1);
    } else {
      g.add(u, v, 0);
    }
  }

  std::vector<int> bln, siz;
  int cnt = g.findScc(bln, siz);

  Graph dag(cnt + 1);
  for (auto i : g.edges) {
    int u = i.u, v = i.v, w = i.w;
    if (bln[u] != bln[v]) {
      dag.add(bln[u], bln[v], w);
      dag.addIn(bln[v]);
    } else if (w != 0) {
      std::cout << -1 << "\n";
      return 0;
    }
  }

  auto f = dag.topo();
  i64 ans = 0;
  for (int i = 1; i <= cnt; i++) {
    ans += f[i] * siz[i];
  }

  std::cout << ans << "\n";

  return 0;
}