/**
 * @file    CF915D Almost Acyclic Graph.cpp
 * @author  ForgotDream
 * @brief   Topo Sort
 * @date    2023-08-27
 */
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 550;
int n, m;
std::vector<int> adj[N];
int deg[N], tmp[N];
bool topo(int s) {
  std::copy(deg + 1, deg + n + 1, tmp + 1), tmp[s]--;
  std::queue<int> q;
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!tmp[i]) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop(), cnt++;
    for (auto v : adj[u]) {
      if (!--tmp[v]) q.push(v);
    }
  }
  return cnt == n;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), deg[v]++;
  }
  for (int i = 1; i <= n; i++) {
    if (topo(i)) {
      std::cout << "YES\n";
      return;
    }
  }
  std::cout << "NO\n";
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}