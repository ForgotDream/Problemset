/**
 * @file    P1260 工程规划.cpp
 * @author  ForgotDream
 * @brief   Difference Constraints
 * @date    2023-11-26
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 1050;
int n, m;
std::vector<pii> adj[N];
bool ins[N];
int dis[N], cnt[N];
bool spfa(int s) {
  memset(dis, 0x3f, sizeof(dis));
  std::queue<int> q;
  q.push(s), dis[s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop(), ins[u] = false;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w, cnt[v]++;
        if (cnt[v] >= n) return false;
        if (!ins[v]) ins[v] = true, q.push(v);
      }
    }
  }
  return true;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    adj[v].emplace_back(u, w);
  }
  for (int i = 1; i <= n; i++) adj[0].emplace_back(i, 0);
  if (spfa(0)) {
    auto mn = *std::min_element(dis + 1, dis + n + 1);
    for (int i = 1; i <= n; i++) std::cout << dis[i] - mn << "\n";
  } else {
    std::cout << "NO SOLUTION\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
