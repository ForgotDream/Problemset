/**
 * @file    UVA10779 Collectors Problem.cpp
 * @author  ForgotDream
 * @brief   Maxmium Flow
 * @date    2023-06-07
 */
#include <bits/stdc++.h>

using i64 = long long;

static constexpr int inf = 1e9;
struct Dinic {
  int n, s, t;
  struct Edge {
    int from, to, cap, flow;
    Edge(int _f = 0, int _t = 0, int _c = 0, int _fl = 0) {
      from = _f, to = _t, cap = _c, flow = _fl;
    }
  };
  std::vector<Edge> edges;
  std::vector<std::vector<int>> adj;
  std::vector<int> dis, cur;
  Dinic(int _n) { n = _n, adj.resize(n), dis.resize(n), cur.resize(n); }
  void setST(int _s, int _t) { s = _s, t = _t; }
  void add(int u, int v, int cap) {
    edges.emplace_back(u, v, cap, 0);
    edges.emplace_back(v, u, 0, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }
  bool bfs() {
    // dis.assign(n, inf);
    // cur.assign(n, 0);
    std::fill(dis.begin(), dis.end(), inf);
    std::fill(cur.begin(), cur.end(), 0);
    std::queue<int> q;
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        int v = edges[i].to, cap = edges[i].cap, flow = edges[i].flow;
        if (cap > flow && dis[v] == inf) { dis[v] = dis[u] + 1, q.push(v); }
      }
    }
    return dis[t] != inf;
  }
  int dfs(int u, int curFlow) {
    if (u == t || curFlow == 0) { return curFlow; }
    int res = 0;
    for (int &i = cur[u]; i < adj[u].size(); i++) {
      int cap = edges[adj[u][i]].cap, flow = edges[adj[u][i]].flow;
      int v = edges[adj[u][i]].to, d = cap - flow, f;
      if (dis[v] == dis[u] + 1 && (f = dfs(v, std::min(curFlow, d))) > 0) {
        edges[adj[u][i]].flow += f, edges[adj[u][i] ^ 1].flow -= f;
        res += f, curFlow -= f;
      }
    }
    return res;
  }
  int maxFlow(int s, int t) {
    setST(s, t);
    int res = 0;
    while (bfs()) { res += dfs(s, inf); }
    return res;
  }
};

void solve(int id) {
  int n, m;
  std::cin >> n >> m;

  Dinic solver(n + m + 2);
  int s = 0, t = n + m + 1;
  for (int i = 0; i < n; i++) {
    int k;
    std::cin >> k;
    std::vector<int> cnt(m);
    while (k--) {
      int u;
      std::cin >> u;
      cnt[--u]++;
    }
    for (int j = 0; j < m; j++) {
      if (i == 0) {
        solver.add(s, j + n, cnt[j]);
      } else {
        if (cnt[j] > 1) { solver.add(i, j + n, cnt[j] - 1); }
        if (!cnt[j]) { solver.add(j + n, i, 1); }
      }
    }
  }
  for (int i = 0; i < m; i++) { solver.add(i + n, t, 1); }

  std::cout << "Case #" << id + 1 << ": " << solver.maxFlow(s, t) << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  for (int i = 0; i < t; i++) {
    solve(i);
  }

  return 0;
}