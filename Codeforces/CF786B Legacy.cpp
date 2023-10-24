/**
 * @file    CF786B Legacy.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-08-04
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50, M = 4e6 + 50, anc = 2e6;
int n, m, s;
std::vector<std::pair<int, int>> adj[M];
struct SegTree {
  int idx[N];
  void build(int s, int t, int u) {
    if (s == t) {
      idx[s] = u;
      adj[u].emplace_back(u + anc, 0);
      adj[u + anc].emplace_back(u, 0);
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(s, mid, lc), build(mid + 1, t, rc);
    adj[u].emplace_back(lc, 0);
    adj[u].emplace_back(rc, 0);
    adj[lc + anc].emplace_back(u + anc, 0);
    adj[rc + anc].emplace_back(u + anc, 0);
  }
  void connect(int l, int r, int s, int t, int u, std::tuple<int, int, int> v) {
    if (l <= s && t <= r) {
      auto [opt, idx, w] = v;
      if (opt) adj[u + anc].emplace_back(idx, w);
      else adj[idx + anc].emplace_back(u, w);
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (mid >= l) connect(l, r, s, mid, lc, v);
    if (mid <  r) connect(l, r, mid + 1, t, rc, v);
  }
} seg;
i64 dis[M];
bool vis[M];
void dijkstra(int s, i64 *dis) {
  std::memset(dis, 0x3f, sizeof(i64) * M);
  std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>,
                      std::greater<std::pair<i64, int>>>
      pq;
  pq.emplace(0, s), dis[s] = 0;
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) dis[v] = dis[u] + w, pq.emplace(dis[v], v);
    }
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> s;
  seg.build(1, n, 1);
  for (int i = 1; i <= m; i++) {
    int opt;
    std::cin >> opt;
    if (opt == 1) {
      int v, u, w;
      std::cin >> v >> u >> w;
      adj[seg.idx[v] + anc].emplace_back(seg.idx[u], w);
    } else {
      int v, l, r, w;
      std::cin >> v >> l >> r >> w;
      seg.connect(l, r, 1, n, 1, std::make_tuple(opt % 2, seg.idx[v], w));
    }
  }
  dijkstra(seg.idx[s] + anc, dis);
  for (int i = 1; i <= n; i++) {
    auto tmp = dis[seg.idx[i]];
    if (tmp != 0x3f3f3f3f3f3f3f3f) std::cout << tmp << " \n"[i == n];
    else std::cout << -1 << " \n"[i == n];
  }
  return 0;
}