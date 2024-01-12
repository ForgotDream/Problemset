/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 505;

struct Dinic {
  struct Edge {
    int u, v, cap, flow;
    Edge() = default;
    Edge(int _u, int _v, int _c) : u(_u), v(_v), cap(_c), flow(0) {}
  };
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int s, t, dis[N], cur[N];
  bool vis[N];
  void addEdge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }
  bool bfs() {
    memset(vis, 0, sizeof(vis));
    std::queue<int> q;
    q.push(s), dis[s] = 0, vis[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (!vis[v] && flow < cap) {
          dis[v] = dis[u] + 1, vis[v] = true;
          q.push(v);
        }
      }
    }
    return vis[t];
  }
  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;
    int res = 0;
    for (int &i = cur[u]; i < adj[i].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      int f;
      if (!vis[v] && dis[v] == dis[u] + 1 && 
          (f = dfs(v, std::min(cap - flow, lim)))) {
        flow += f, res += f;
        edges[adj[u][i] ^ 1].flow -= f, lim -= f;
      }
    }
    return res;
  }
  int maxFlow(int s, int t) {
    this->s = s, this->t = t;
    int res = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(0));
      memset(vis, false, sizeof(vis));
      res += maxFlow(s, 1e9);
    }
    return res;
  }
} dinic;

std::vector<int> adj[N];

int n, m;

void build(int l, int r) {
  if (l >= r) return;
  int mid = (l + r) >> 1;
}

void solve() {
  std::cin >> n >> m;
  for (int i = 0, u, v, cap; i < m; i++) {
    std::cin >> u >> v >> cap;
    dinic.addEdge(u, v, cap);
  }

  build(0, m - 1);
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
