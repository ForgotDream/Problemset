/**
 * @file    UOJ#667. 【UNR #5】提问系统.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-07-26
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int K = 2550, mod = 998244353;
int k, lr, lb;
char opt[10];
int fa[K], dep[K], cur = 1, cnt = 1;
std::vector<int> adj[K];
i64 f[K][K][4];

void dfs(int u) {
  for (int b = 0; b <= std::min(lb, dep[u]); b++) {
    int r = dep[u] - b;
    if (r <= lr) f[u][b][0] = 1;
  }
  for (auto v : adj[u]) {
    dfs(v);
    for (int b = 0; b <= std::min(lb, dep[u]); b++) {
      i64 s0 = (f[v][b][0] + f[v][b + 1][0]) % mod;
      i64 s1 = (f[v][b][1] + f[v][b + 1][0] + f[v][b + 1][1]) % mod;
      i64 s2 = (f[v][b][2] + f[v][b + 1][0] + 2 * f[v][b + 1][1] + f[v][b + 1][2]) % mod;
      i64 s3 = (f[v][b][3] + f[v][b + 1][0] + 3 * f[v][b + 1][1] + 3 * f[v][b + 1][2] + f[v][b + 1][3]) % mod;
      f[u][b][3] = (f[u][b][0] * s3 + f[u][b][1] * s2 * 3 + f[u][b][2] * s1 * 3 + f[u][b][3] * s0) % mod;
      f[u][b][2] = (f[u][b][0] * s2 + f[u][b][1] * s1 * 2 + f[u][b][2] * s0) % mod;
      f[u][b][1] = (f[u][b][0] * s1 + f[u][b][1] * s0) % mod;
      f[u][b][0] = (f[u][b][0] * s0) % mod;
    }
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> k >> lr >> lb;
  for (int i = 1; i <= 2 * k; i++) {
    std::cin >> opt;
    if (opt[1] == 'u') {
      adj[cur].push_back(++cnt), fa[cnt] = cur, dep[cnt] = dep[cur] + 1;
      cur = cnt;
    } else cur = fa[cur];
  }

  dfs(1);
  std::cout << (k * f[1][0][2] - f[1][0][3] + mod) % mod << "\n";

  return 0;
}