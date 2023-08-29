/**
 * @file    CF1067B Multihedgehog.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-25
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k, deg[N];
std::vector<int> adj[N];
int dis[N], cnt[N];
bool used[N];
void solve() {
  std::cin >> n >> k;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  std::queue<int> q;
  std::memset(dis, -1, sizeof(dis));
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 1) {
      q.push(i);
      dis[i] = 0, cnt[i] = 1e9, used[i] = true;
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop(), used[u] = true;
    if (cnt[u] < 3) return void(std::cout << "No\n");
    for (auto v : adj[u]) {
      if (used[v]) continue;
      if (dis[v] == -1) dis[v] = dis[u] + 1, cnt[v]++;
      else if (dis[v] != dis[u] + 1) return void(std::cout << "No\n");
      else cnt[v]++;
      if (--deg[v] == 1) q.push(v);
    }
  }
  int max = *std::max_element(dis + 1, dis + n + 1);
  if (max == k) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}