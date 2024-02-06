/*
 * @file    CF156D Clues.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-02-06
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using iter = std::vector<i64>::iterator;

constexpr int N = 1e5 + 50;

int n, m, p;
std::vector<int> adj[N];

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

int cnt, siz;
bool vis[N];

void dfs(int u) {
  vis[u] = true, siz++;
  for (auto v : adj[u]) {
    if (vis[v]) continue;
    dfs(v);
  }
}

void solve() {
  std::cin >> n >> m >> p;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  i64 ans = 1;
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    cnt++, siz = 0, dfs(i);
    ans = ans * siz % p;
  }

  if (cnt == 1) {
    std::cout << 1 % p << "\n";
    return;
  }

  ans = ans * fast_pow(n, cnt - 2, p) % p;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
