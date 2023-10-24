/**
 * @file    AT_abc236_d [ABC236D] Dance.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-08-26
 */
#include <iostream>

using i64 = long long;

constexpr int N = 20;
int n, a[N][N];
i64 ans;
bool used[N];
void dfs(int u, i64 cur) {
  if (u == 2 * n) {
    ans = std::max(ans, cur);
    return;
  }
  if (used[u]) return dfs(u + 1, cur);
  for (int i = u + 1; i <= 2 * n; i++) {
    if (used[i]) continue;
    used[i] = true;
    dfs(u + 1, cur ^ a[u][i]);
    used[i] = false;
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= 2 * n; i++) {
    for (int j = i + 1; j <= 2 * n; j++) {
      std::cin >> a[i][j];
      a[j][i] = a[i][j];
    }
  }
  dfs(1, 0);
  std::cout << ans << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}