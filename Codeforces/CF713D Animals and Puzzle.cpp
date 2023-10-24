/**
 * @file    CF713D Animals and Puzzle.cpp
 * @author  ForgotDream
 * @brief   2D ST
 * @date    2023-07-31
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace FastIO {
char buf[1 << 23], *p1 = buf, *p2 = buf;
inline char gc() {
  if (p1 == p2) {
    p1 = buf, p2 = buf + fread(buf, 1, 1 << 23, stdin);
  }
  return p1 == p2 ? EOF : *p1++;
}
template <typename T> inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (!isdigit(c)) {
    f = (c == '-' ? -f : f), c = gc();
  }
  while (isdigit(c)) {
    x = x * 10 + c - '0', c = gc();
  }
  x *= f;
}
template <typename T, typename... args> inline void read(T &x, args &...tmp) {
  read(x), read(tmp...);
}
template <typename T> inline void print(T x) {
  if (x < 0) {
    putchar('-'), x = -x;
  }
  if (x / 10) {
    print(x / 10);
  }
  putchar(x % 10 + '0');
}
template <typename T> inline void print(T x, char c) { print(x), putchar(c); }
inline void readString(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) {
    c = gc();
  }
  while (isdigit(c) || isalpha(c)) {
    *s++ = c, c = gc();
  }
}
} // namespace FastIO

constexpr int N = 1001, LOG = 11;
int n, m, a[N][N], s[N][N], q;
int rt[N][N], dwn[N][N];
int f[LOG][LOG][N][N], lg[N];

void init() {
  for (int i = 2; i <= 1000; i++)
    lg[i] = lg[i >> 1] + 1;
  for (int k1 = 0; (1 << k1) <= n; k1++) {
    for (int k2 = 0; (1 << k2) <= m; k2++) {
      if (!k1 && !k2)
        continue;
      for (int i = 1; i + (1 << k1) - 1 <= n; i++) {
        for (int j = 1; j + (1 << k2) - 1 <= m; j++) {
          if (k1) {
            f[k1][k2][i][j] = std::max(f[k1 - 1][k2][i][j],
                                       f[k1 - 1][k2][i + (1 << (k1 - 1))][j]);
          } else {
            f[k1][k2][i][j] = std::max(f[k1][k2 - 1][i][j],
                                       f[k1][k2 - 1][i][j + (1 << (k2 - 1))]);
          }
        }
      }
    }
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  FastIO::read(n, m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      FastIO::read(a[i][j]);
    }
  }

  for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
      if (!a[i][j])
        continue;
      rt[i][j] = rt[i][j + 1] + 1;
      dwn[i][j] = dwn[i + 1][j] + 1;
      f[0][0][i][j] =
          std::min({f[0][0][i + 1][j + 1] + 1, rt[i][j], dwn[i][j]});
    }
  }

  init();

  FastIO::read(q);
  while (q--) {
    int x1, y1, x2, y2;
    FastIO::read(x1, y1, x2, y2);

    auto check = [&](int x1, int y1, int x2, int y2, int len) -> bool {
      int k1 = lg[x2 - x1 + 1], k2 = lg[y2 - y1 + 1];
      int tmp = std::max({
          f[k1][k2][x1][y1],
          f[k1][k2][x1][y2 - (1 << k2) + 1],
          f[k1][k2][x2 - (1 << k1) + 1][y1],
          f[k1][k2][x2 - (1 << k1) + 1][y2 - (1 << k2) + 1],
      });
      return tmp >= len;
    };

    int lo = 0, hi = std::min(x2 - x1 + 1, y2 - y1 + 1), ans = 0;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      if (check(x1, y1, x2 - mid + 1, y2 - mid + 1, mid))
        ans = mid, lo = mid + 1;
      else
        hi = mid - 1;
    }
    FastIO::print(ans, '\n');
  }

  return 0;
}