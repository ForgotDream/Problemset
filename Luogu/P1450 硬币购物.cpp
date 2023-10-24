/**
 * @file    P1450 硬币购物.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int d = 1e5;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::array<int, 4> c;
  for (int i = 0; i < 4; i++) { std::cin >> c[i]; }

  std::vector<i64> f(d + 1);
  f[0] = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = c[i]; j <= d; j++) { f[j] += f[j - c[i]]; }
  }

  int n;
  std::cin >> n;

  while (n--) {
    std::array<int, 4> d;
    for (int i = 0; i < 4; i++) { std::cin >> d[i]; }
    int s;
    std::cin >> s;
    i64 ans = f[s];
    for (int st = 1; st < 16; st++) {
      int mark = 0;
      i64 cur = s;
      for (int i = 0; i < 4; i++) {
        if (!(st & (1 << i))) { continue; }
        mark ^= 1, cur -= 1ll * (d[i] + 1) * c[i];
      }
      // std::cerr << cur << "\n";
      if (cur >= 0) {
        if (mark) {
          ans -= f[cur];
        } else {
          ans += f[cur];
        }
      }
    }
    std::cout << ans << "\n";
  }

  return 0;
}