/**
 * @file    P1491 集合位置.cpp
 * @author  ForgotDream
 * @brief   SSSP
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
using f80 = long double;
using pif = std::pair<int, f80>;
using pfi = std::pair<f80, int>;
constexpr int N = 250;
constexpr f80 eps = 1e-8, inf = 1e18;
int n, m, x[N], y[N];
std::vector<pif> adj[N];
f80 dis[N];
int nxt[N];
bool vis[N];
bool eq(f80 lhs, f80 rhs) { return std::fabs(lhs - rhs) <= eps; }
bool gt(f80 lhs, f80 rhs) { return lhs > rhs + eps; }
bool ge(f80 lhs, f80 rhs) { return gt(lhs, rhs) || eq(lhs, rhs); }
int pu, pv;
void dijkstra(int s, f80 *dis, bool flg = false, int siz = N) {
  std::priority_queue<pfi, std::vector<pfi>, std::greater<pfi>> pq;
  for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = false;
  dis[s] = 0, pq.emplace(0, s);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : adj[u]) {
      if (u == pu && v == pv) continue;
      if (u == pv && v == pu) continue;
      if (gt(dis[v], dis[u] + w)) {
        dis[v] = dis[u] + w, pq.emplace(dis[v], v);
        if (flg) nxt[v] = u;
      }
    }
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(2);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    f80 dis = std::hypot(x[u] - x[v], y[u] - y[v]);
    adj[u].emplace_back(v, dis);
    adj[v].emplace_back(u, dis);
  }
  dijkstra(1, dis, true);
  f80 ans = inf;
  for (int p = n; nxt[p]; p = nxt[p]) {
    pu = p, pv = nxt[p];
    dijkstra(1, dis);
    ans = std::min(ans, dis[n]);
  }
  if (ans != inf) std::cout << ans << "\n";
  else std::cout << -1 << "\n";
  return 0;
}