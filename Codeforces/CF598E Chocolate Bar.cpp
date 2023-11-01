/**
 * @file    CF598E Chocolate Bar.cpp
 * @author  ForgotDream
 * @brief   DP + DFS
 * @date    2023-11-01
 */
#include <iostream>

using i64 = long long;

constexpr int N = 55;
int n, m, k, a[N], f[N][N][N];
int dfs(int n, int m, int k) {
  if (!k || n * m == k) return 0;
  if (n > m) std::swap(n, m);
  if (f[n][m][k]) return f[n][m][k];
  int &res = f[n][m][k];
  res = 1e9;
  for (int i = 1; i <= n / 2; i++) {
    for (int j = 0; j <= k; j++) {
      res = std::min(res, m * m + dfs(i, m, j) + dfs(n - i, m, k - j));
    }
  }
  for (int i = 1; i <= m / 2; i++) {
    for (int j = 0; j <= k; j++) {
      res = std::min(res, n * n + dfs(n, i, j) + dfs(n, m - i, k - j));
    }
  }
  return res;
}
void solve() {
  std::cin >> n >> m >> k;
  std::cout << dfs(n, m, k) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
