/**
 * @file    P3066 [USACO12DEC] Running Away From the Barn G.cpp
 * @author  ForgotDream
 * @brief   Binary Lifting
 * @date    2023-11-28
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2e5 + 50;
int n;
i64 t, p[20][N], w[20][N], v[N], dep[N];
void solve() {
  std::cin >> n >> t;
  for (int i = 2; i <= n; i++) std::cin >> p[0][i] >> w[0][i], dep[i] = dep[p[0][i]] + w[0][i];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 19; j++) p[j][i] = p[j - 1][p[j - 1][i]];
    i64 cur = t;
    v[i]++;
    int u = i;
    for (int j = 19; j >= 0; j--) {
      if (dep[u] - dep[p[j][u]] <= cur) cur -= dep[u] - dep[p[j][u]], u = p[j][u];
    }
    v[p[0][u]]--;
  }
  for (int i = n; i; i--) v[p[0][i]] += v[i];
  for (int i = 1; i <= n; i++) std::cout << v[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
