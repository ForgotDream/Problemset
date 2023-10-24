#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::vector a(n + 2, std::vector<int>(m + 2));
  std::vector s(n + 1, std::vector<int>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
      s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    }
  }

  std::vector f(4, std::vector(n + 2, std::vector<int>(m + 2)));
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

    for (int i = sx; i != ex + dx; i += dx) {
      for (int j = sy; j != ey + dy; j += dy) {
        f[d][i][j] = (i == sx && j == sy) ? 0 : -1e9;
        if (j != sy) {
          f[d][i][j] = std::max(f[d][i][j], f[d][i][j - dy] + a[i][j - dy]);
        }
        if (i != sx) {
          f[d][i][j] = std::max(f[d][i][j], f[d][i - dx][j] + a[i - dx][j]);
        } 
      }
    }
  }

  std::vector p(n + 1, std::vector<int>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      p[i][j] = p[i - 1][j] + a[i][j];
    }
  }

  int ans = -1e9;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      int sum = f[2][i][1] + f[0][j][1];
      int pre = sum;
      for (int k = 1; k <= m; k++) {
        int tmp = p[i][k] - p[j - 1][k];
        if (sum < pre) {
          sum = f[2][i][k] + f[0][j][k];
          pre = sum;
        }
        sum += tmp;
        if (pre != f[2][i][k] + f[0][j][k]) {
          ans = std::max(ans, sum + f[3][i][k] + f[1][j][k]);
        }
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}