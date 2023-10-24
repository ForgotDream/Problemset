/**
 * @file    P2762 太空飞行计划问题.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-08-19
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

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

constexpr int N = 55;
int n, m, c[N];

struct Reader {
  std::string s;
  int p = 0;
  bool block = false;
  int operator()() {
    if (block) return block = false, -1;
    if (p == s.length()) std::getline(std::cin, s), p = 0, s += '\n';
    int res = -1;
    bool flg = false;
    while (p < s.length()) {
      if (std::isdigit(s[p])) {
        if (res == -1) res = s[p] - '0';
        else res = res * 10 + s[p] - '0';
        flg = true;
      } else if (flg) {
        if (s[p] == '\n') block = true;
        p++;
        return res;
      }
      p++;
    }
    return res;
  }
} read;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int S = 0, T = 100050 - 1;

  std::cin >> m >> n;
  int sum = 0;
  for (int i = 1; i <= m; i++) {
    int p, u;
    std::cin >> p;
    sum += p;
    solver.addEdge(S, i, p);
    while ((u = read()) != -1) {
      solver.addEdge(i, u + m, 1e9);
    }
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> c[i];
    solver.addEdge(i + m, T, c[i]);
  }

  auto flow = solver.maxFlow(S, T);
  for (int i = 1; i <= m; i++) {
    if (solver.dis[i]) std::cout << i << " ";
  }
  std::cout << "\n";
  for (int i = 1; i <= n; i++) {
    if (solver.dis[i + m]) std::cout << i << " ";
  }
  std::cout << "\n";
  std::cout << sum - flow << "\n";

  return 0;
}