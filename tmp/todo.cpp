/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 305;

int n;

struct MCMF {
  struct Edge {
    int from, to, cap, cost;
    Edge(int u, int v, int cap, int cost) 
      : from(u), to(v), cap(cap), cost(cost) {}
  };
  static const int INF = 0x3f3f3f3f;
  int n, s, t;
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int dis[N];
  u32 cur[N];
  bool vis[N];

  bool spfa() {
    memset(dis, 0x3f, sizeof(dis)), memset(vis, false, sizeof(vis));
    std::queue<int> q;
    q.push(s), dis[s] = 0, vis[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), vis[u] = false;
      for (int i : adj[u]) {
        auto [_, v, cap, w] = edges[i];
        if (cap && dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (!vis[v]) vis[v] = true, q.push(v);
        }
      }
    }
    return dis[t] != INF;
  }

  int dfs(int u, int lim, int &cost) {
    if (u == t || lim == 0) return lim;
    int res = 0;
    vis[u] = true;
    for (u32 &i = cur[u]; i < adj[u].size(); i++) {
      auto &[_, v, cap, w] = edges[adj[u][i]];
      int f;
      if (!vis[v] && dis[v] == dis[u] + w && 
          (f = dfs(v, std::min(cap, lim), cost)) > 0) {
        cost += f * w;
        cap -= f, lim -= f;
        edges[adj[u][i] ^ 1].cap += f, res += f;
        if (!lim) break;
      }
    }
    vis[u] = false;
    return res;
  }

  void add(int u, int v, int cap, int cost) {
    edges.emplace_back(u, v, cap, cost);
    edges.emplace_back(v, u, 0, -cost);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }

  std::pair<int, int> solve(int _s, int _t) {
    int flow = 0, cost = 0;
    s = _s, t = _t;
    while (spfa()) {
      memset(cur, 0, sizeof(cur));
      flow += dfs(_s, INF, cost);
    }
    return std::make_pair(flow, cost);
  }
};

void solve() {
  std::cin >> n;
  for (int i = 1, ct; i <= n; i++) {
    std::cin >> ct;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
