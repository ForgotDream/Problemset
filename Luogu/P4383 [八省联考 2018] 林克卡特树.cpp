/*
 * @file    P4383 [八省联考 2018] 林克卡特树.cpp
 * @author  ForgotDream
 * @brief   WQS Binary Search + DP
 * @date    2024-02-26
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pll = std::pair<i64, i64>;

constexpr int N = 3e5 + 50;

int n, k;
std::vector<pll> adj[N];

pll f[N][3], cur;

inline pll operator+(const pll &a, const pll &b) {
  return {a.first + b.first, a.second + b.second};
}

void dfs(int u, int frm) {
  f[u][0] = f[u][1] = f[u][2] = {0, 0}, f[u][2] = std::max(f[u][2], cur);
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    f[u][2] = std::max({f[u][2], f[u][2] + f[v][0], f[u][1] + f[v][1] + std::pair(w, 0) + cur});
    f[u][1] = std::max({f[u][1], f[u][1] + f[v][0], f[u][0] + f[v][1] + std::pair(w, 0)});
    f[u][0] = std::max({f[u][0], f[u][0] + f[v][0]});
  }
  f[u][0] = std::max({f[u][0], f[u][1] + cur, f[u][2]});
}

bool check(i64 u) {
  cur = {-u, 1}, dfs(1, 0);
  return f[1][0].second >= k;
}

void solve() {
  std::cin >> n >> k, k++;
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }

  i64 lo = -1e12, hi = 1e12, ans = 0;
  while (lo <= hi) {
    i64 mid = (lo + hi) >> 1;
    if (check(mid)) ans = f[1][0].first + mid * k, lo = mid + 1;
    else hi = mid - 1;
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
