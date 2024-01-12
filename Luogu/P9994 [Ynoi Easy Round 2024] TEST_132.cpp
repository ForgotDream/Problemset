/*
 * @file    P9994 [Ynoi Easy Round 2024] TEST_132.cpp
 * @author  ForgotDream
 * @brief   Sqrt
 * @date    2024-01-08
 */
#include <bits/stdc++.h>

#pragma region
namespace FastIO {
static constexpr signed bufsize = 1 << 20;
struct is {
  char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
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
  template <typename T>
  is &operator>>(T &rhs) { return read(rhs), *this; }
  is &operator>>(char *rhs) { return read(rhs), *this; }
};
struct os {
  char outbuf[bufsize], *pp = outbuf;
  ~os() { flush(); }
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
  os &operator<<(const T &rhs) { return print(rhs), *this; }
};
}  // namespace FastIO
FastIO::is fin;
FastIO::os fout;
#pragma endregion

// #define int unsigned

using i64 = long long;
using pii = std::tuple<int, int>;

constexpr int N = 1e6 + 50, mod = 1e9 + 7;

int n, m, x[N], y[N], v[N], vv[N];

int cnt[N], tag[N];
i64 ans[N];
std::vector<int> xp[N];
std::vector<pii> yp[N];

inline i64 fastPow(i64 base, i64 exp) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void solve() {
  fin >> n >> m;
  std::fill(tag + 1, tag + n + 1, 1);

  // int blk = 2 * std::sqrt(n);
  int blk = 3500;

  for (int i = 1; i <= n; i++) {
    fin >> x[i] >> y[i] >> v[i], vv[i] = v[i];
    cnt[x[i]]++, xp[x[i]].push_back(i);
    ans[y[i]] += v[i];
    if (ans[y[i]] >= mod) ans[y[i]] -= mod;
  }

  for (int i = 1; i <= n; i++) {
    if (cnt[i] <= blk) continue;
    for (auto j : xp[i]) yp[y[j]].emplace_back(i, j);
  }

  for (int opt, u; m; m--) {
    fin >> opt >> u;

    if (opt == 1) {
      if (cnt[u] <= blk) {
        for (auto i : xp[u]) {
          ans[y[i]] += mod - v[i];
          v[i] = 1ll * v[i] * v[i] % mod;
          ans[y[i]] += v[i];
        }
      } else {
        tag[u] *= 2;
        if (tag[u] >= mod - 1) tag[u] -= mod - 1;
      }
    } else {
      for (const auto &[i, j] : yp[u]) {
        ans[u] += mod - v[j];
        v[j] = fastPow(vv[j], tag[i]);
        ans[u] += v[j];
      }
      ans[u] = (ans[u] % mod + mod) % mod;
      fout << ans[u] << "\n";
    }
  }
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
