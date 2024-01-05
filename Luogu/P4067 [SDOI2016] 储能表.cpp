/*
 * @file    P4067 [SDOI2016] 储能表.cpp
 * @author  ForgotDream
 * @brief   Digital DP
 * @date    2024-01-05
 */
#include <bits/stdc++.h>

using i64 = long long;

// 考虑一个显然的分讨！
// 把点分为 > k 的与 <= k 的
// 于是只需要求出前者的和

constexpr int N = 70;
i64 n, m, k, p;
i64 f[N][2][2][2], g[N][2][2][2];

void solve() {
  std::cin >> n >> m >> k >> p;

  memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
  g[62][1][1][1] = 1;  // 全部都是 0，当然相等

  for (int i = 61; i; i--) {
    int x = !!(n & (1ll << (i - 1))), y = !!(m & (1ll << (i - 1))), 
        z = !!(k & (1ll << (i - 1)));
    for (int a = 0; a < 2; a++) {
      for (int b = 0; b < 2; b++) {
        for (int c = 0; c < 2; c++) {
          if (!f[i + 1][a][b][c] && !g[i + 1][a][b][c]) continue;

          for (int xx = 0; xx < 2; xx++) {
            for (int yy = 0; yy < 2; yy++) {
              int zz = xx ^ yy;
              if ((a && x < xx) || (b && y < yy) || (c && z > zz)) continue;

              int aa = (a && x == xx), bb = (b && y == yy), cc = (c && z == zz);
              // 其实相当于同时判断三个数有没有顶到上界？不是很懂

              g[i][aa][bb][cc] += g[i + 1][a][b][c];
              g[i][aa][bb][cc] %= p;

              f[i][aa][bb][cc] += f[i + 1][a][b][c] + 
                  (zz - z + p) % p * ((1ll << (i - 1)) % p) % p * 
                  g[i + 1][a][b][c] % p;
              f[i][aa][bb][cc] %= p;
            }
          }
        }
      }
    }
  }

  std::cout << f[1][0][0][0] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
