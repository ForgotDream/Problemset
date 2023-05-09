/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-05-08
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 INF = 1e18;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

<<<<<<< Updated upstream
=======
  int n, m;
  std::cin >> n >> m;

  std::vector a(n + 1, std::vector<i64>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
    }
  }

  std::vector f(4, std::vector(n + 2, std::vector<i64>(m + 2, -INF)));
  for (int d = 0; d < 4; d++) {
    int dx, dy;
    int sx, sy;
    int ex, ey;

    if (d >= 2) {
      dx = -1, sx = n, ex = 1;
    } else {
      dx = 1, sx = 1, ex = n;
    }

    if (d & 1) {
      dy = -1, sy = m, ey = 1;
    } else {
      dy = 1, sy = 1, ey = m;
    }

    f[d][sx][sy] = a[sx][sy];
    for (int i = sx; i != ex + dx; i += dx) {
      for (int j = sy; j != ey + dy; j += dy) {
        if (i != sx || j != sy) {
          f[d][i][j] = std::max(f[d][i - dx][j], f[d][i][j - dy]) + a[i][j];
        }
      }
    }
  }

  std::vector p(n + 1, std::vector<i64>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      p[i][j] = (i == 1 ? 0 : p[i - 1][j]) + a[i][j];
    }
  }

  std::vector<i64> l(m + 1), r(m + 1), s(m + 1);
  i64 ans = -INF;
  for (int x1 = 1; x1 <= n; x1++) {
    for (int x2 = x1 + 1; x2 <= n; x2++) {
      for (int i = 1; i <= m; i++) {
        s[i] = s[i - 1] + p[x2][i] - p[x1 - 1][i];
      }
      for (int i = 1; i <= m; i++) {
        l[i] = -s[i - 1] + f[0][x1][i] + f[2][x2][i] - a[x1][i] - a[x2][i];
        r[i] = s[i] + f[1][x1][i] + f[3][x2][i] - a[x1][i] - a[x2][i];
      }
      i64 cur = -INF;
      for (int i = 1; i <= m; i++) {
        std::cerr << cur << " " << ans << "\n";
        if (i != 1) {
          ans = std::max(ans, cur + r[i]);
        }
        cur = std::max(cur, l[i]);
      }
    }
  }

  std::cout << ans << "\n";

>>>>>>> Stashed changes
  return 0;
}