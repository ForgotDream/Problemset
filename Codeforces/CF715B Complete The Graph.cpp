/*
 * @file    CF715B Complete The Graph.cpp
 * @author  ForgotDream
 * @brief   SSSP + Greedy
 * @date    2024-02-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pli = std::pair<i64, int>;

constexpr int N = 20050;

int n, m, l, s, t;

struct Edge {
  int u, v, w, p;
  Edge() = default;
  Edge(int _u, int _v, int _w, int _p) : u(_u), v(_v), w(_w + _p), p(_p) {}
};
std::vector<Edge> edges;
std::vector<int> adj[N];

inline void add_edge(int u, int v, int w) {
  edges.emplace_back(u, v, w, !w);
  adj[u].push_back(edges.size() - 1);
}

i64 dis[2][N], d;
bool vis[N];

void dijkstra(int idx) {
  std::priority_queue<pli, std::vector<pli>, std::greater<>> pq;
  
  memset(vis, false, sizeof(vis));
  dis[idx][s] = 0, pq.emplace(0, s);

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto i : adj[u]) {
      auto &[_, v, w, p] = edges[i];
      if (idx == 1) {
        if (p && dis[1][u] + w < dis[0][v] + d) {
          w = edges[i ^ 1].w = dis[0][v] + d - dis[1][u];
        }
      }
      if (dis[idx][v] > dis[idx][u] + w) {
        dis[idx][v] = dis[idx][u] + w;
        pq.emplace(dis[idx][v], v);
      }
    }
  }
}

void solve() {
  std::cin >> n >> m >> l >> s >> t;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    add_edge(u, v, w), add_edge(v, u, w);
  }

  memset(dis, 0x3f, sizeof(dis));
  
  dijkstra(0);
  // std::cerr << dis[0][t] << "\n";
  if (dis[0][t] > l) {
    std::cout << "NO\n";
    return;
  }

  d = l - dis[0][t], dijkstra(1);
  // std::cerr << dis[1][t] << "\n";
  if (dis[1][t] != l) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n";
  for (u32 i = 0; i < edges.size(); i += 2) {
    std::cout << edges[i].u << " " << edges[i].v << " " << edges[i].w << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
