/**
 * @file    CF321E Ciel and Gondolas.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
namespace FastIO {
char buf[1 << 23], *p1 = buf, *p2 = buf;
inline char gc() {
  if (p1 == p2) p1 = buf, p2 = buf + fread(buf, 1, 1 << 23, stdin);
  return p1 == p2 ? EOF : *p1++;
}
template <typename T> inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (!isdigit(c)) f = (c == '-' ? -f : f), c = gc();
  while (isdigit(c)) x = x * 10 + c - '0', c = gc();
  x *= f;
}
template <typename T, typename... args> inline void read(T &x, args &...tmp) {
  read(x), read(tmp...);
}
template <typename T> inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x / 10) print(x / 10);
  putchar(x % 10 + '0');
}
template <typename T> inline void print(T x, char c) { print(x), putchar(c); }
inline void readString(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) *s++ = c, c = gc();
}
} // namespace FastIO
using namespace FastIO;
using i64 = long long;
constexpr int N = 4050, K = 805;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
int n, k, a[N][N], s[N][N];
i64 f[K][N];
i64 sum(int l, int r) {
  return s[r][r] - s[l - 1][r] - s[r][l - 1] + s[l - 1][l - 1];
}
void solve(int l, int r, int s, int t, int k) {
  if (l > r) return;
  int mid = (l + r) >> 1, pivot = s;
  i64 ans = inf;
  for (int i = s; i <= std::min(mid, t); i++) {
    i64 tmp = f[k - 1][i - 1] + sum(i, mid) / 2;
    if (ans > tmp) ans = tmp, pivot = i;
  }
  f[k][mid] = ans;
  solve(l, mid - 1, s, pivot, k), solve(mid + 1, r, pivot, t, k);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  read(n, k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      read(a[i][j]);
      s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    }
  }
  std::memset(f, 0x3f, sizeof(f));
  f[0][0] = 0;
  for (int i = 1; i <= k; i++) solve(1, n, 1, n, i);
  print(f[k][n], '\n');
  return 0;
}