/**
 * @file    P3792 由乃与大母神原型和偶像崇拜.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + Hash
 * @date    2023-12-04
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

using i64 = int64_t;
using u64 = uint64_t;
using ti3 = std::tuple<int, int, u64>;

constexpr int N = 5e5 + 50;
int n, m;
u64 a[N];
struct SegTree {
  int mn[N << 2], mx[N << 2];
  u64 ss[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) {
    mn[u] = std::min(mn[lc(u)], mn[rc(u)]);
    mx[u] = std::max(mx[lc(u)], mx[rc(u)]);
    ss[u] = ss[lc(u)] + ss[rc(u)];
  }
  void build(int s, int t, int u) {
    if (s == t) return mn[u] = mx[u] = a[s], ss[u] = 6 * a[s] * a[s], void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int tar, int s, int t, int u, u64 val) {
    if (s == t) return mn[u] = mx[u] = val, ss[u] = 6 * val * val, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  ti3 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return std::make_tuple(mn[u], mx[u], ss[u]);
    int mid = (s + t) >> 1;
    if (mid >= r) {
      return query(l, r, s, mid, lc(u));
    } else if (mid < l) {
      return query(l, r, mid + 1, t, rc(u));
    } else {
      auto [lmn, lmx, lss] = query(l, r, s, mid, lc(u));
      auto [rmn, rmx, rss] = query(l, r, mid + 1, t, rc(u));
      return std::make_tuple(std::min(lmn, rmn), std::max(lmx, rmx), lss + rss);
    }
  }
} seg;
u64 squareSum(u64 u) {
  return u * (u + 1) * (2 * u + 1);
}
void solve() {
  fin >> n >> m;
  for (int i = 1; i <= n; i++) fin >> a[i];
  seg.build(1, n, 1);
  for (int opt, x, y; m; m--) {
    fin >> opt >> x >> y;
    if (opt == 1) {
      seg.modify(x, 1, n, 1, y);
    } else {
      auto [mn, mx, ss] = seg.query(x, y, 1, n, 1);
      // std::cout << mn << " " << mx << " " << ss << " " << squareSum(mx) - squareSum(mn - 1) << "\n";
      if (mx - mn != y - x || squareSum(mx) - squareSum(mn - 1) != ss) {
        fout << "yuanxing\n";
      } else {
        fout << "damushen\n";
      }
    }
  }
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
