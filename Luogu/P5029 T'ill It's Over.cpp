/**
 * @file    P5029 T'ill It's Over.cpp
 * @author  ForgotDream
 * @brief   Maximum Flow
 * @date    2023-08-04
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50, inf = 0x3f3f3f3f, M = 1e6 + 50;
int n, m, k, cnt;
template<int N = 1000050, int M = 3000050>
struct Dinic {
  static const int inf = 0x3f3f3f3f;
  struct Edge {
    int u, v, cap, flow;
    Edge() = default;
    Edge(int _u, int _v, int _c) { u = _u, v = _v, cap = _c, flow = 0; }
  } edges[M];
  int cnt = 0;
  std::vector<int> adj[N];
  int s, t, dis[N], cur[N];
  void add(int u, int v, int cap) {
    edges[cnt++] = Edge(u, v, cap), edges[cnt++] = Edge(v, u, 0);
    adj[u].push_back(cnt - 2), adj[v].push_back(cnt - 1);
  }
  bool bfs() {
    std::memset(cur, 0, sizeof(cur));
    std::memset(dis, 0x3f, sizeof(dis));
    std::queue<int> q;
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (dis[v] == inf && cap > flow) dis[v] = dis[u] + 1, q.push(v);
      }
    }
    return dis[t] != inf;
  }
  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;
    int res = 0;
    for (int &i = cur[u], f; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      if (dis[v] == dis[u] + 1 && (f = dfs(v, std::min(lim, cap - flow)))) {
        res += f, lim -= f;
        flow += f, edges[adj[u][i] ^ 1].flow -= f;
        if (!lim) break;
      }
    }
    return res;
  }
  int maxFlow(int _s, int _t) {
    int res = 0;
    s = _s, t = _t;
    while (bfs()) res += dfs(s, inf);
    return res;
  }
};
Dinic solver;
int idx[M], rev[M];
void build(int s, int t, int u) {
  idx[u] = ++cnt, rev[u] = ++cnt;
  if (s == t) {
    solver.add(idx[u], rev[u], inf), solver.add(rev[u], idx[u], inf);
    return;
  }
  int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
  build(s, mid, lc), build(mid + 1, t, rc);
  solver.add(idx[u], idx[lc], inf), solver.add(idx[u], idx[rc], inf);
  solver.add(rev[lc], rev[u], inf), solver.add(rev[rc], rev[u], inf);
}
int st[N], top;
void find(int l, int r, int s, int t, int u) {
  if (l <= s && t <= r) {
    st[++top] = u;
    return;
  }
  int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
  if (mid >= l) find(l, r, s, mid, lc);
  if (mid <  r) find(l, r, mid + 1, t, rc);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> k;
  build(1, k, 1);
  for (int i = 1; i <= m; i++) {
    int opt, lim;
    std::cin >> opt >> lim;
    int ts = ++cnt, tt = ++cnt;
    solver.add(ts, tt, lim);
    if (opt == 1) {
      int a, b;
      std::cin >> a >> b;
      find(a, a, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b, b, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    } else if (opt == 2) {
      int a1, a2, b;
      std::cin >> a1 >> a2 >> b;
      find(a1, a2, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b, b, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    } else if (opt == 3) {
      int a, b1, b2;
      std::cin >> a >> b1 >> b2;
      find(a, a, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b1, b2, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    } else {
      int a1, a2, b1, b2;
      std::cin >> a1 >> a2 >> b1 >> b2;
      find(a1, a2, 1, k, 1);
      while (top) solver.add(rev[st[top--]], ts, inf);
      find(b1, b2, 1, k, 1);
      while (top) solver.add(tt, idx[st[top--]], inf);
    }
  }
  int s = ++cnt, t = ++cnt;
  find(1, 1, 1, k, 1);
  int p1 = st[top];
  top = 0;
  find(k, k, 1, k, 1);
  int pk = st[top];
  top = 0;
  solver.add(s, rev[p1], n), solver.add(idx[pk], t, n);
  std::cout << solver.maxFlow(s, t) << "\n";
  return 0;
}