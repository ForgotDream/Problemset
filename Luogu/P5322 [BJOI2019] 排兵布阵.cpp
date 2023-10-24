/**
 * @file    P5322 [BJOI2019] 排兵布阵.cpp
 * @author  ForgotDream
 * @brief   Knapsack
 * @date    2023-10-18
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 105, M = 2e4 + 50;
int s, n, m;
namespace S1 {
int a[N];
i64 f[N][M];
void solve() {
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      f[i][j] = f[i - 1][j];
      if (j >= 2 * a[i] + 1) {
        f[i][j] = std::max(f[i][j], f[i - 1][j - 2 * a[i] - 1] + i);
      }
    }
  }
  std::cout << f[n][m] << "\n";
}
}  // namespace S1
namespace S2 {
std::vector<int> a[N];
i64 f[N][M];
void solve() {
  for (int i = 1; i <= n; i++) a[i].push_back(0);
  for (int i = 1; i <= s; i++) {
    for (int j = 1, u; j <= n; j++) std::cin >> u, a[j].push_back(u);
  }
  for (int i = 1; i <= n; i++) std::sort(a[i].begin(), a[i].end());
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      f[i][j] = f[i - 1][j];
      for (int k = 0; k <= s; k++) {
        if (j < 2 * a[i][k] + 1) break;
        f[i][j] = std::max(f[i][j], f[i - 1][j - 2 * a[i][k] - 1] + k * i);
      }
    }
  }
  std::cout << f[n][m] << "\n";
}
}  // namespace S2
void solve() {
  std::cin >> s >> n >> m;
  if (s == 1) S1::solve();
  else S2::solve();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
