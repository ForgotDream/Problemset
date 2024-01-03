/*
 * @file    P3554 [POI2013] LUK-Triumphal arch.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-01
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n;
std::vector<int> adj[N];

int son[N];
void pre(int u, int frm) {
  for (auto v : adj[u]) {
    if (v == frm) continue;
    pre(v, u), son[u]++;
  }
}

int f[N], k;
void dfs(int u, int frm) {
  f[u] = son[u] - k;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u), f[u] += std::max(f[v], 0);
  }
}
bool check(int u) {
  k = u, dfs(1, 0);
  return f[1] <= 0;
}

void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  pre(1, 0);

  int lo = son[1], hi = *std::max_element(son + 1, son + n + 1), ans = hi;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) hi = mid - 1, ans = mid;
    else lo = mid + 1;
  }

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
