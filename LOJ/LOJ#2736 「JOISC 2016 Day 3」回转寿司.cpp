/**
 * @file    LOJ#2736 「JOISC 2016 Day 3」回转寿司.cpp
 * @author  ForgotDream
 * @brief   Sqrt Data Structure
 * @date    2023-10-29
 */
#include <cmath>
#include <iostream>
#include <queue>

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

constexpr int N = 4e5 + 50;
int n, q, a[N];
int blk, bcnt, l[N], r[N], bln[N];
std::priority_queue<int> max[N];
std::priority_queue<int, std::vector<int>, std::greater<>> tag[N];
void rebuild(int u) {
  if (tag[u].empty()) return;
  for (int i = l[u]; i <= r[u]; i++) {
    if (a[i] > tag[u].top()) {
      int pre = a[i];
      a[i] = tag[u].top(), tag[u].pop();
      tag[u].push(pre);
    }
  }
  while (!tag[u].empty()) tag[u].pop();
}
int modify(int u, int l, int r, int val) {
  rebuild(u);
  for (int i = l; i <= r; i++) {
    if (a[i] > val) std::swap(a[i], val);
  }
  while (!max[u].empty()) max[u].pop();
  for (int i = ::l[u]; i <= ::r[u]; i++) max[u].push(a[i]);
  return val;
}
int query(int l, int r, int val) {
  if (bln[l] == bln[r]) {
    return modify(bln[l], l, r, val);
  } else {
    val = modify(bln[l], l, ::r[bln[l]], val);
    for (int i = bln[l] + 1; i < bln[r]; i++) {
      if (max[i].top() > val) {
        int cur = max[i].top();
        max[i].pop(), max[i].push(val);
        tag[i].push(val), val = cur;
      }
    }
    return modify(bln[r], ::l[bln[r]], r, val);
  }
}
void init() {
  blk = std::sqrt(n * 1.25), bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) l[i] = (i - 1) * blk + 1, r[i] = i * blk;
  r[bcnt] = n;
}
void solve() {
  fin >> n >> q;
  init();
  for (int i = 1; i <= n; i++) fin >> a[i], max[bln[i]].push(a[i]);
  for (int i = 1, l, r, val; i <= q; i++) {
    fin >> l >> r >> val;
    if (l <= r) fout << query(l, r, val) << "\n";
    else fout << query(1, r, query(l, n, val)) << "\n";
  }
}

int main() {
  // std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
