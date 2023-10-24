/**
 * @file    P4137 Rmq Problem / mex.cpp
 * @author  ForgotDream
 * @brief   回滚莫队
 * @date    2023-09-05
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
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
template <typename T>
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

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, a[N], c[N];
std::vector<int> b;
i64 ans[N];
namespace SQRT {
int bln[N], lp[N], rp[N];
struct Query {
  int l, r, id;
  bool operator<(const Query &rhs) const {
    if (bln[l] == bln[rhs.l]) return r > rhs.r;
    return bln[l] < bln[rhs.l];
  }
} qry[N];
void init() {
  int blk = std::max(m / std::sqrt(0.75 * n), 1.), cnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= cnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;
  rp[cnt] = n;
  std::sort(qry + 1, qry + m + 1);
}
int cnt[N];
void del(int u, int &val) {
  cnt[a[u]]--;
  if (!cnt[a[u]]) val = std::min(val, a[u]);
}
void rollback(int u) { cnt[a[u]]++; }
void solve() {
  int s = 1, t = n;
  std::set<int> S;
  for (int i = 0; i <= 2e5 + 1; i++) S.insert(i);
  for (int i = 1; i <= n; i++) S.erase(a[i]), cnt[a[i]]++;
  int cur = *S.begin(), st = cur, lst = 0;
  for (int i = 1; i <= m; i++) {
    auto [l, r, id] = qry[i];
    if (bln[l] != lst) {
      while (t < n) rollback(++t);
      while (s < lp[bln[l]]) del(s++, st);
      lst = bln[l], cur = st;
    }
    while (t > r) del(t--, cur);
    int tmp = cur, p = s;
    while (p < l) del(p++, tmp);
    while (p > s) rollback(--p);
    ans[id] = tmp;
  }
}
}
void solve() {
  read(n, m);
  for (int i = 1; i <= n; i++) read(a[i]);
  for (int i = 1; i <= m; i++) {
    read(SQRT::qry[i].l, SQRT::qry[i].r);
    SQRT::qry[i].id = i;
  }
  SQRT::init(), SQRT::solve();
  for (int i = 1; i <= m; i++) write(ans[i], '\n');
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