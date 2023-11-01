/**
 * @file    CF797F Mice and Holes.cpp
 * @author  ForgotDream
 * @brief   DP + Monotone Queue
 * @date    2023-11-01
 */
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 5050;
int n, m, a[N], s[N];
pii b[N];
i64 f[N][N], sum[N];
int q[N], l, r;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i].first >> b[i].second;
  std::sort(a + 1, a + n + 1), std::sort(b + 1, b + m + 1);
  for (int i = 1; i <= m; i++) s[i] = s[i - 1] + b[i].second;
  if (s[m] < n) {
    std::cout << -1 << "\n";
    return;
  }
  std::memset(f, 0x3f, sizeof(f)), f[0][0] = 0;
  for (int i = 1; i <= m; i++) {
    f[i][0] = l = r = 0, q[++r] = 0;
    for (int j = 1; j <= std::min(s[i], n); j++) {
      f[i][j] = f[i - 1][j], sum[j] = sum[j - 1] + std::abs(a[j] - b[i].first);
      while (j - q[l] > b[i].second ||
             (l <= r && f[i - 1][q[l]] - sum[q[l]] > f[i - 1][j] - sum[j])) l++;
      f[i][j] = std::min(f[i][j], f[i - 1][q[l]] - sum[q[l]] + sum[j]);
      q[++r] = j;
    }
  }
  std::cout << f[m][n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
