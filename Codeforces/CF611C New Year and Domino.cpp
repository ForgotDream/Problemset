/**
 * @file    CF611C New Year and Domino.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-07
 */
#include <iostream>

#pragma region
struct FastIO {
static constexpr signed bufsize = 1 << 18;
char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
char outbuf[bufsize], *pp = outbuf;
~FastIO() { flush(); }
inline char gc() {
  if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
  return p1 == p2 ? EOF : *p1++;
}
template <typename T>
inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (c < '0' || c > '9') f = ( c == '-' ? -f : f), c = gc();
  while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = gc();
  x *= f;
}
inline void read(char *s) {
  char c = gc();
  while (c == ' ' || c == '\n' || c == '\r') c = gc();
  while (c != ' ' && c != '\n' && c != '\r') *s++ = c, c = gc();
}
inline void read(char &c) {
  c = gc();
  while (c == ' ' || c == '\n' || c == '\r') c = gc();
}
inline void read(std::string &s) {
  std::string().swap(s);
  char c = gc();
  while (c == ' ' || c == '\n' || c == '\r') c = gc();
  while (c != ' ' && c != '\n' && c != '\r') s += c, c = gc();
}
template <typename T = int>
inline T read() {
  T res;
  read(res);
  return res;
}
inline void pc(const char &c) {
  if (pp - outbuf == bufsize) fwrite(outbuf, 1, bufsize, stdout), pp = outbuf;
  *pp++ = c;
}
template <typename T>
inline void print(T x) {
  if (x < 0) x = -x, pc('-');
  static T sta[35];
  T top = 0;
  do sta[top++] = x % 10, x /= 10; while (x);
  while (top) pc(sta[--top] + '0');
}
inline void print(const char *s) { for (; *s; ++s) pc(*s); }
inline void print(char *s) { for (; *s; ++s) pc(*s); }
inline void print(const std::string &s) { for (const auto &c : s) pc(c); }
inline void print(const char &c) { pc(c); }
inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
template <typename T>
FastIO &operator>>(T &rhs) { return read(rhs), *this; }
FastIO &operator>>(char *rhs) { return read(rhs), *this; }
template <typename T>
FastIO &operator<<(const T &rhs) { return print(rhs), *this; }
} fin, fout;
#pragma endregion

using i64 = long long;

constexpr int N = 550;
int h, w, q;
char a[N][N];
int f[N][N], g[N][N];
void solve() {
  fin >> h >> w;
  for (int i = 1; i <= h; i++) fin >> (a[i] + 1);
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      f[i][j] = f[i - 1][j], g[i][j] = g[i][j - 1];
      if (a[i][j] == '#') continue;
      if (a[i - 1][j] == '.') f[i][j]++;
      if (a[i][j - 1] == '.') g[i][j]++;
    }
  }
  fin >> q;
  while (q--) {
    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    int ans = 0;
    for (int i = x1; i <= x2; i++) ans += g[i][y2] - g[i][y1];
    for (int i = y1; i <= y2; i++) ans += f[x2][i] - f[x1][i];
    fout << ans << "\n";
  }
}

signed main() {
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}