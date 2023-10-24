/**
 * @file    P8078 [WC2022] 秃子酋长.cpp
 * @author  ForgotDream
 * @brief   回滚莫队
 * @date    2023-09-05
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

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
template <typename T, typename... args>
inline void read(T &x, args &...tmp) {
  read(x), read(tmp...);
}
inline void readString(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) *s++ = c, c = gc();
}
inline void readString(std::string &s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) s += c, c = gc();
}
inline void pc(const char &c) {
  if (pp - outbuf == 1 << 20) fwrite(outbuf, 1, 1 << 20, stdout), pp = outbuf;
  *pp++ = c;
}
template <typename T>
void write(T x) {
  if (x < 0) x = -x, pc('-');  // 负数输出
  static T sta[35];
  T top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) pc(sta[--top] + '0');
}
template <typename T>
void write(T x, char lastChar) {
  write(x), pc(lastChar);
}
inline void writeString(char *s) {
  for (; s; ++s) pc(*s);
}
inline void writeString(const std::string &s) {
  for (const auto &c : s) pc(c);
}
inline void flush() { fwrite(outbuf, 1, pp - outbuf, stdout), pp = outbuf; }
struct istream {};
template <typename T>
inline istream &operator>>(istream &is, T &rhs) {
  return read(rhs), is;
}
inline istream &operator>>(istream &is, char *rhs) {
  return readString(rhs), is;
}
inline istream &operator>>(istream &is, std::string &rhs) {
  return readString(rhs), is;
}
struct ostream {
  ~ostream() { flush(); }
};
inline ostream &operator<<(ostream &os, char *rhs) {
  return writeString(rhs), os;
}
inline ostream &operator<<(ostream &os, const char *rhs) {
  return writeString(rhs), os;
}
inline ostream &operator<<(ostream &os, std::string &rhs) {
  return writeString(rhs), os;
}
inline ostream &operator<<(ostream &os, const std::string &rhs) {
  return writeString(rhs), os;
}
template <typename T>
inline ostream &operator<<(ostream &os, const T &rhs) {
  return write(rhs), os;
}
}  // namespace FastIO
FastIO::istream in;
FastIO::ostream out;

using i64 = long long;

constexpr int N = 5e5 + 50;
int n, m, a[N], idx[N];
i64 ans[N];
struct LinkList {
  int pre[N], nxt[N];
  std::stack<int> s;
  void init() {
    for (int i = 1; i <= n; i++) pre[i] = i - 1, nxt[i] = i + 1;
  }
  inline int del(int u) {
    int p1 = pre[u], p2 = nxt[u], res = 0;
    if (p1 != 0 && p2 != n + 1) res += std::abs(idx[p1] - idx[p2]);
    if (p1 != 0) res -= std::abs(idx[p1] - idx[u]);
    if (p2 != n + 1) res -= std::abs(idx[p2] - idx[u]);
    pre[p2] = p1, nxt[p1] = p2, s.push(u);
    return res;
  }
  inline void rollback() {
    int u = s.top();
    s.pop(), nxt[pre[u]] = pre[nxt[u]] = u;
  }
} list;
namespace SQRT {
int bln[N], lp[N], rp[N];
struct Query {
  int l, r, id;
  inline bool operator<(const Query &rhs) const {
    if (bln[l] == bln[rhs.l]) return r > rhs.r;
    return bln[l] < bln[rhs.l];
  }
} qry[N];
void init() {
  list.init();
  int blk = std::max(m / std::sqrt(0.85 * n), 1.), cnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= cnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;
  rp[cnt] = n;
  std::sort(qry + 1, qry + m + 1);
}
inline void del(int u, i64 &val) { val += list.del(a[u]); }
inline void rollback(int u) { list.rollback(); }
void solve() {
  int s = 1, t = n;
  i64 cur = 0, st = 0;
  for (int i = 2; i <= n; i++) st += std::abs(idx[i] - idx[i - 1]);
  cur = st;
  int lst = 1;
  for (int i = 1; i <= m; i++) {
    auto [l, r, id] = qry[i];
    if (bln[l] != lst) {
      while (t < n) rollback(t++);
      while (s < lp[bln[l]]) del(s++, st);
      t = n, lst = bln[l], cur = st;
    }
    while (t > r) del(t--, cur);
    i64 tmp = cur, p = s;
    while (p < l) del(p++, tmp);
    while (p > s) rollback(p--);
    ans[id] = tmp;
  }
}
}
void solve() {
  in >> n >> m;
  for (int i = 1; i <= n; i++) in >> a[i], idx[a[i]] = i;
  for (int i = 1; i <= m; i++) {
    in >> SQRT::qry[i].l >> SQRT::qry[i].r;
    SQRT::qry[i].id = i;
  }
  SQRT::init(), SQRT::solve();
  for (int i = 1; i <= m; i++) out << ans[i] << "\n";
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  FastIO::flush();
  return 0;
}