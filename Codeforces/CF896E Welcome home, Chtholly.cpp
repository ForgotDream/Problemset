/**
 * @file    CF896E Welcome home, Chtholly.cpp
 * @author  ForgotDream
 * @brief   分块 + 并查集
 * @date    2023-09-05
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

#pragma region
namespace FastIO {
char inbuf[1 << 20], *p1 = inbuf, *p2 = inbuf;
char outbuf[1 << 20], *pp = outbuf;
inline char gc() {
  if (p1 == p2) p1 = inbuf, p2 = inbuf + fread(inbuf, 1, 1 << 20, stdin);
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
  if (pp - outbuf == 1 << 20) fwrite(outbuf, 1, 1 << 20, stdout), pp = outbuf;
  *pp++ = c;
}
template <typename T>
inline void write(T x) {
  if (x < 0) x = -x, pc('-');  // 负数输出
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

constexpr int N = 1e5 + 50, M = 350;
int n, m, a[N];
namespace SQRT {
int fa[N], tag[N], max[N], w[N], rt[M][N], cnt[M][N];
inline int find(int u) {
  while (u != fa[u]) u = fa[u] = fa[fa[u]];
  return u;
}
int blk, bcnt, bln[N], lp[N], rp[N];
inline void merge(int u, int x, int y) {
  if (rt[u][y]) fa[rt[u][x]] = rt[u][y];
  else rt[u][y] = rt[u][x], w[rt[u][x]] = y;
  cnt[u][y] += cnt[u][x], cnt[u][x] = rt[u][x] = 0;
}
inline void pushdown(int u) {
  for (int i = lp[u]; i <= rp[u]; i++) {
    a[i] = w[find(i)], rt[u][a[i]] = cnt[u][a[i]] = 0, a[i] -= tag[u];
  }
  tag[u] = 0;
  for (int i = lp[u]; i <= rp[u]; i++) fa[i] = 0;
}
inline void tagging(int u, int val) {
  if (val <= max[u] - tag[u] - val) {
    for (int i = tag[u] + 1; i <= tag[u] + val; i++) {
      if (rt[u][i]) merge(u, i, i + val);
    }
    tag[u] += val;
  } else {
    for (int i = max[u]; i > tag[u] + val; i--) {
      if (rt[u][i]) merge(u, i, i - val);
    }
    max[u] = std::min(max[u], tag[u] + val);
  }
}
inline void rebuild(int u) {
  max[u] = 0;
  for (int i = lp[u]; i <= rp[u]; i++) {
    chkmax(max[u], a[i]);
    if (rt[u][a[i]]) fa[i] = rt[u][a[i]];
    else w[i] = a[i], rt[u][a[i]] = fa[i] = i;
    cnt[u][a[i]]++;
  }
}
inline void modify(int l, int r, int val) {
  int p = bln[l], q= bln[r];
  pushdown(p);
  if (p != q) pushdown(q);
  if (p == q) {
    for (int i = l; i <= r; i++) {
      if (a[i] > val) a[i] -= val;
    }
    rebuild(p);
  } else {
    for (int i = l; i <= rp[p]; i++) {
      if (a[i] > val) a[i] -= val;
    }
    for (int i = lp[q]; i <= r; i++) {
      if (a[i] > val) a[i] -= val;
    }
    for (int i = p + 1; i < q; i++) tagging(i, val);
    rebuild(p), rebuild(q);
  }
}
inline int query(int l, int r, int val) {
  int p = bln[l], q= bln[r], res = 0;
  if (p == q) {
    for (int i = l; i <= r; i++) {
      if (w[find(i)] - tag[p] == val) res++;
    }
  } else {
    for (int i = l; i <= rp[p]; i++) {
      if (w[find(i)] - tag[p] == val) res++;
    }
    for (int i = lp[q]; i <= r; i++) {
      if (w[find(i)] - tag[q] == val) res++;
    }
    for (int i = p + 1; i < q; i++) {
      if (val + tag[i] <= 1e5) res += cnt[i][val + tag[i]];
    }
  }
  return res;
}
void init() {
  blk = std::sqrt(n), bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;
  rp[bcnt] = n;
  for (int i = 1; i <= bcnt; i++) rebuild(i), tag[i] = 0;
}
}
void solve() {
  read(n, m);
  for (int i = 1; i <= n; i++) read(a[i]);
  SQRT::init();
  for (int i = 1; i <= m; i++) {
    int opt = read(), l = read(), r = read(), val = read();
    if (opt == 1) {
      SQRT::modify(l, r, val);
    } else {
      write(SQRT::query(l, r, val), '\n');  
    }
  }
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  flush();
  return 0;
}