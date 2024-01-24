/*
 * @file    P4382 [八省联考 2018] 劈配.cpp
 * @author  ForgotDream
 * @brief   Max Flow
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 500, inf = 0x3f3f3f3f;

struct Dinic {
  struct Edge {
    int u, v, cap, flow;
    Edge() = default;
    Edge(int _u, int _v, int _c) : u(_u), v(_v), cap(_c), flow(0) {}
  };
  std::vector<Edge> edges;
  int cnt, s, t;
  std::vector<int> adj[N];

  void add_edge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }

  int dis[N];
  u32 cur[N];
  bool vis[N];

  bool bfs() {
    std::queue<int> q;
    memset(dis, 0x3f, sizeof(dis));

    dis[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (dis[v] == inf && cap > flow) {
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }

    return dis[t] < inf;
  }

  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;

    int res = 0;
    for (u32 i = 0; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      int f;
      if (dis[v] == dis[u] + 1 && cap > flow &&
          (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        res += f, flow += f;
        lim -= f, edges[adj[u][i] ^ 1].flow -= f;
        if (!lim) break;
      }
    }

    return res;
  }
} G[N], eye, cur;

int n, m, expect[N], lim[N], s, t;
std::vector<int> lis[N][N];

void clear() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) lis[i][j].clear();
  }
  G[0] = eye;
}

bool check(int p, int u) {
  cur = G[p - 1], cur.add_edge(s, u, 1);
  for (int i = 1; i <= expect[u]; i++) {
    for (auto v : lis[u][i]) cur.add_edge(u, v + n, 1);
  }
  return cur.bfs();
}

void solve() {
  std::cin >> n >> m;
  clear();

  for (int i = 1; i <= m; i++) std::cin >> lim[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 1, u; j <= m; j++) {
      std::cin >> u;
      if (u) lis[i][u].push_back(j);
    }
  }
  for (int i = 1; i <= n; i++) std::cin >> expect[i];

  s = 0, t = n + m + 1;
  G[0].s = s, G[0].t = t;

  for (int i = 1; i <= m; i++) G[0].add_edge(i + n, t, lim[i]);
  for (int i = 1; i <= n; i++) {
    G[i] = G[i - 1], G[i].add_edge(s, i, 1);
    bool flg = false;
    for (int j = 1; j <= m; j++) {
      for (auto v : lis[i][j]) G[i].add_edge(i, v + n, 1);
      if (G[i].bfs()) {
        G[i].dfs(s, inf);
        flg = true, std::cout << j << " ";
        break;
      }
      for (auto v : lis[i][j]) {
        G[i].adj[i].pop_back(), G[i].adj[v + n].pop_back();
        G[i].edges.pop_back(), G[i].edges.pop_back();
      }
    }
    if (!flg) std::cout << m + 1 << " ";
  }
  std::cout << "\n";

  for (int i = 1; i <= n; i++) {
    int lo = 1, hi = i, ans = 0;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      if (check(mid, i)) lo = mid + 1, ans = mid;
      else hi = mid - 1;
    }
    std::cout << i - ans << " ";
  }
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t >> *new int;
  while (t--) solve();

  return 0;
}
