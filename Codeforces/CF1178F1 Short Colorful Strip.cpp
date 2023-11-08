/**
 * @file    CF1178F1 Short Colorful Strip.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-05
 */
#include <algorithm>
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

constexpr int N = 1050, M = 1e6 + 50, mod = 998244353;
int n, m, a[M], lp[N], rp[N];
i64 f[N][N];
void solve() {
  fin >> n >> m;
  for (int i = 1; i <= m; i++) fin >> a[i];
  m = std::unique(a + 1, a + m + 1) - a - 1;
  if (m > 2 * n) return fout << 0 << "\n", void();
  for (int i = 1; i <= n; i++) lp[i] = m + 1;
  for (int i = 1; i <= m; i++) {
    lp[a[i]] = std::min(lp[a[i]], i), rp[a[i]] = std::max(rp[a[i]], i);
  }
  for (int i = 1; i <= m; i++) {
    if (lp[a[i]] == i && rp[a[i]] == i) f[i][i] = 1;
  }
  for (int i = 0; i <= m; i++) f[i + 1][i] = 1;
  for (int len = 2; len <= m; len++) {
    for (int l = 1; l <= m - len + 1; l++) {
      int r = l + len - 1;
      int mn = std::min_element(a + l, a + r + 1) - a;
      int s = lp[a[mn]], t = rp[a[mn]];
      if (s < l || t > r) continue;
      i64 s1 = 0, s2 = 0, pre = 0;
      for (int k = l; k <= s; k++) (s1 += f[l][k - 1] * f[k][s - 1] % mod) %= mod;
      for (int k = t; k <= r; k++) (s2 += f[t + 1][k] * f[k + 1][r] % mod) %= mod;
      f[l][r] = s1 * s2 % mod;
      for (int k = l; k <= r; k++) {
        if (a[k] != a[mn]) continue;
        if (pre) f[l][r] = f[l][r] * f[pre + 1][k - 1] % mod;
        pre = k;
      }
    }
  }
  fout << f[1][m] << "\n";
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
