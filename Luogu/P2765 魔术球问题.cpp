/**
 * @file    P2765 魔术球问题.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-08-19
 */
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pll = std::pair<i64, i64>;

constexpr int N = 1e5 + 50;
int n, head[N], nxt[N];
bool vis[N];

#pragma region
template<int N = 100050>
struct Dinic {
  struct Edge {
    int u, v;
    i64 cap, flow;
    Edge(int _u = 0, int _v = 0, i64 _c = 0) {
      u = _u, v = _v, cap = _c, flow = 0;
    }
  };
  int s, t;
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int dis[N], cur[N];
  Dinic() = default;
  void addEdge(int u, int v, i64 cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }
  bool bfs() {
    std::memset(dis, 0, sizeof(dis));
    std::memset(cur, 0, sizeof(cur));
    std::queue<int> q;
    q.push(s), dis[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (!dis[v] && cap > flow) dis[v] = dis[u] + 1, q.push(v);
      }
    }
    return dis[t];
  }
  i64 dfs(int u, i64 lim) {
    if (u == t || !lim) return lim;
    i64 res = 0;
    for (int &i = cur[u]; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      i64 f;
      if (dis[v] == dis[u] + 1 && (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        flow += f, edges[adj[u][i] ^ 1].flow -= f;
        res += f, lim -= f;
        nxt[u / 2] = v / 2;
        if (!lim) break;
      }
    }
    return res;
  }
  i64 maxFlow(int s, int t) {
    this->s = s, this->t = t;
    i64 res = 0;
    while (bfs()) res += dfs(s, 1e9);
    return res;
  }
};
Dinic solver;
#pragma endregion

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  int S = 0, T = 100050 - 1;

  int cur = 0, cnt = 0;
  while (cnt <= n) {
    cur++;
    solver.addEdge(S, 2 * cur, 1);
    solver.addEdge(2 * cur + 1, T, 1);
    for (int i = 1; i < cur; i++) {
      if (int s = std::sqrt(i + cur); s * s == i + cur) {
        solver.addEdge(2 * i, 2 * cur + 1, 1);
      }
    }
    int flow = solver.maxFlow(S, T);
    if (!flow) head[++cnt] = cur;
  }

  std::cout << cur - 1 << "\n";
  for (int i = 1; i <= n; i++) {
    if (vis[head[i]]) continue;
    for (int p = head[i]; p && p != T / 2; p = nxt[p]) {
      vis[p] = true;
      std::cout << p << " ";
    }
    std::cout << "\n";
  }

  return 0;
}