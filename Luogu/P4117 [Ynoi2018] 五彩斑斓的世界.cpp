/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-09-07
 */
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

#pragma region
namespace FastIO {
constexpr signed bufsize = 1 << 24;
char inbuf[bufsize], *p1 = inbuf, *p2 = inbuf;
char outbuf[bufsize], *pp = outbuf;
inline char gc() {
  if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, bufsize, stdin);
  return p1 == p2 ? EOF : *p1++;
}
template <typename T>
inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (!isdigit(c)) f = ( c == '-' ? -f : f), c = gc();
  while (isdigit(c)) x = x * 10 + c - '0', c = gc();
  x *= f;
}
template <typename T = int>
inline T read() {
  T res;
  read(res);
  return res;
}
template <typename T, typename... args>
inline void read(T &x, args &...tmp) { read(x), read(tmp...); }
inline void read(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) *s++ = c, c = gc();
}
inline void read(std::string &s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) s += c, c = gc();
}
inline void pc(const char &c) {
  if (pp - outbuf == bufsize) fwrite(outbuf, 1, bufsize, stdout), pp = outbuf;
  *pp++ = c;
}
template <typename T>
inline void write(T x) {
  if (x < 0) x = -x, pc('-');
  static T sta[35];
  T top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) pc(sta[--top] + '0');
}
template <typename T> inline void write(T x, char c) { write(x), pc(c); }
inline void write(char *s) {
  for (; s; ++s) pc(*s);
}
inline void write(const std::string &s) {
  for (const auto &c : s) pc(c);
}
inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
}  // namespace FastIO
using namespace FastIO;
#pragma endregion

using i64 = long long;

template <typename T>
bool chkmax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T>
bool chkmin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T>
T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
T min(const T &a, const T &b) { return a < b ? a : b; }

constexpr int N = 1e6 + 50, M = 1e5 + 50, K = N / 2;
int n, m, a[N];
struct Query {
  int opt, l, r, val;
} qry[K];
int ans[K];
int fa[N], tag, ma, w[N], rt[M], cnt[M];
int bl, br;
inline int find(int u) {
  while (u ^ fa[u]) u = fa[u] = fa[fa[u]];
  return u;
}
int blk, bcnt;
inline void merge(const int &x, const int &y) {
  if (rt[y]) fa[rt[x]] = rt[y];
  else rt[y] = rt[x], w[rt[x]] = y;
  cnt[y] += cnt[x], cnt[x] = rt[x] = 0;
}
inline void pushdown() {
  for (int i = bl; i <= br; i++) {
    a[i] = w[find(i)], rt[a[i]] = cnt[a[i]] = 0, a[i] -= tag;
  }
  tag = 0;
  for (int i = bl; i <= br; i++) w[i] = 0;
}
inline void tagging(const int &val) {
  if (val <= ma - tag - val) {
    for (int i = tag + 1; i <= tag + val; i++) {
      if (rt[i]) merge(i, i + val);
    }
    tag += val;
  } else {
    for (int i = ma; i > tag + val; i--) {
      if (rt[i]) merge(i, i - val);
    }
    ma = std::min(ma, tag + val);
  }
}
inline void rebuild() {
  ma = 0;
  for (int i = bl; i <= br; i++) {
    chkmax(ma, a[i]);
    if (rt[a[i]]) fa[i] = rt[a[i]];
    else w[i] = a[i], rt[a[i]] = fa[i] = i;
    cnt[a[i]]++;
  }
}
int l, r, val;
inline void modify() {
  if (l <= bl && br <= r) {
    tagging(val);
  } else {
    pushdown();
    int s = std::max(l, bl), t = std::min(r, br);
    for (int i = s; i <= t; i++) {
      if (a[i] > val) a[i] -= val;
    }
    rebuild();
  }
}
inline int query() {
  if (val + tag > 1e5 + 1) return 0;
  if (l <= bl && br <= r) {
    return cnt[val + tag];
  } else {
    int res = 0, s = std::max(l, bl), t = std::min(r, br);
    for (int i = s; i <= t; i++) {
      if (!(w[find(i)] ^ val + tag)) res++;
    }
    return res;
  }
}
inline void solve() {
  read(n, m);
  blk = __builtin_sqrt(n) * 1.3, bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) read(a[i]);
  for (int i = 1; i <= m; i++) read(qry[i].opt, qry[i].l, qry[i].r, qry[i].val);
  for (int u = 1; u <= bcnt; u++) {
    if (u != 1) {
      // __builtin_memset(rt, 0, sizeof(rt));
      __builtin_memset(cnt, 0, sizeof(cnt));
    }
    bl = (u - 1) * blk + 1, br = u * blk;
    if (u == bcnt) br = n;
    tag = 0, rebuild();
    for (int i = 1; i <= m; i++) {
      l = qry[i].l, r = qry[i].r, val = qry[i].val;
      if (bl > r || br < l) continue;
      if (qry[i].opt ^ 1) {
        ans[i] += query();
      } else {
        modify();
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (!(qry[i].opt ^ 2)) write(ans[i], '\n');
  }
}

signed main() {
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  flush();
  return 0;
}
