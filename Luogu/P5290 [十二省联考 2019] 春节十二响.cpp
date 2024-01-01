/*
 * @file    P5290 [十二省联考 2019] 春节十二响.cpp
 * @author  ForgotDream
 * @brief   DSU on Tree
 * @date    2023-12-30
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N];
std::vector<int> adj[N];

std::priority_queue<int> pq[N];
void merge(int u, int v) {
  if (pq[u].size() < pq[v].size()) std::swap(pq[u], pq[v]);
  std::vector<int> cur;
  while (!pq[v].empty()) {
    cur.push_back(std::max(pq[u].top(), pq[v].top()));
    pq[u].pop(), pq[v].pop();
  }
  for (auto i : cur) pq[u].push(i);
}
void dfs(int u) {
  for (auto v : adj[u]) dfs(v), merge(u, v);
  pq[u].push(a[u]);
}

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 2, f; i <= n; i++) std::cin >> f, adj[f].push_back(i);

  dfs(1);

  i64 ans = 0;
  while (!pq[1].empty()) ans += pq[1].top(), pq[1].pop();
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
