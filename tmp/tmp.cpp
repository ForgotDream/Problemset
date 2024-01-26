/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using f64 = double;

constexpr int N = 550, inf = 0x3f3f3f3f;

struct Dinic {
  struct Edge {
    int u, v, cap;
  };
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int cnt, s, t;

  int dis[N];
  u32 cur[N];

  bool bfs() {
    std::queue<int> q;
    memset(dis, 0x3f, sizeof(dis));

    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap] = edges[i];
        if (dis[v] == inf && cap) {
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }

    return dis[t] != inf;
  }

  int dfs(int u, int lim) {

  }
};

void solve() {
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t >> *new int;
  while (t--) solve();

  return 0;
}
