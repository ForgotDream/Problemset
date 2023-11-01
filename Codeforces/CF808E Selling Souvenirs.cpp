/**
 * @file    CF808E Selling Souvenirs.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-31
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, m, w[N], c[N], siz[4];
i64 s[N], f[N], a[4][N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> w[i] >> c[i]; 
    a[w[i]][++siz[w[i]]] = c[i];
  }
  for (int i = 1; i <= 3; i++) {
    std::sort(a[i] + 1, a[i] + siz[i] + 1, std::greater<>());
  }
  f[1] = a[1][1];
  int pos[2][3] = {{0, 1, 1}, {0, 2, 1}};
  for (int i = 2; i <= m; i++) {
    int p = (i & 1);
    f[i] = f[i - 2];
    if (a[1][pos[p][1]] + a[1][pos[p][1] + 1] > a[2][pos[p][2]]) {
      f[i] += a[1][pos[p][1]] + a[1][pos[p][1] + 1];
      pos[p][1] += 2;
    } else {
      f[i] += a[2][pos[p][2]];
      pos[p][2]++;
    }
  }
  for (int i = 1; i <= std::max(siz[3], m / 3); i++) s[i] = s[i - 1] + a[3][i];
  i64 ans = 0;
  for (int i = 0; i <= m / 3; i++) ans = std::max(ans, s[i] + f[m - 3 * i]);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
