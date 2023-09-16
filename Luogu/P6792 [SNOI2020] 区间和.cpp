/**
 * @file    P6792 [SNOI2020] 区间和.cpp
 * @author  ForgotDream
 * @brief   KTT
 * @date    2023-09-04
 */
#include <iostream>

using i64 = long long;

void chkmin(i64 &a, const i64 &b) { a = a > b ? b : a; }
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
}

constexpr int N = 1e5 + 50;
constexpr i64 inf = 1e18;
int n, q;
i64 a[N];
struct Line {
  i64 k, b;
  Line(i64 _k = 0, i64 _b = 0) { k = _k, b = _b; }
  Line operator+(const Line &rhs) const { return Line(k + rhs.k, b + rhs.b); }
};
std::pair<Line, i64> findmax(Line lhs, Line rhs) {
  if (lhs.k < rhs.k || (lhs.k == rhs.k && lhs.b < rhs.b)) std::swap(lhs, rhs);
  if (lhs.b >= rhs.b) return std::make_pair(lhs, inf);
  else return std::make_pair(rhs, (rhs.b - lhs.b)/ (lhs.k - rhs.k));
}
struct SegTree {
  struct Node {
    Line sum, lmax, rmax, max;
    i64 nxt = inf;
    friend Node operator+(const Node &lhs, const Node &rhs) {
      Node res;
      res.nxt = std::min(lhs.nxt, rhs.nxt);
      // Update sum
      res.sum = lhs.sum + rhs.sum;
      // Update lmax
      auto tmp = findmax(lhs.lmax, lhs.sum + rhs.lmax);
      res.lmax = tmp.first, chkmin(res.nxt, tmp.second);
      // Update rmax
      tmp = findmax(lhs.rmax + rhs.sum, rhs.rmax);
      res.rmax = tmp.first, chkmin(res.nxt, tmp.second);
      // Update max
      tmp = findmax(lhs.max, rhs.max), chkmin(res.nxt, tmp.second);
      tmp = findmax(tmp.first, lhs.rmax + rhs.lmax);
      res.max = tmp.first, chkmin(res.nxt, tmp.second);
      return res;
    }
  } tree[N << 2];
  i64 min[N << 2], semi[N << 2], tag[N << 2];
  inline int lc(const int &u) { return u << 1; }
  inline int rc(const int &u) { return u << 1 | 1; }
  void pushup(int u) {
    int lc = SegTree::lc(u), rc = SegTree::rc(u);
    if (min[lc] == min[rc]) {
      min[u] = min[lc];
      semi[u] = std::min(semi[lc], semi[rc]);
      tree[u] = tree[lc] + tree[rc];
    } else if (min[lc] > min[rc]) {
      min[u] = min[rc];
      semi[u] = std::min(min[lc], semi[rc]);
      auto tmp = std::move(tree[lc]);
      tmp.sum.k = tmp.lmax.k = tmp.rmax.k = tmp.max.k = 0;
      tree[u] = tmp + tree[rc];
    } else {
      min[u] = min[lc];
      semi[u] = std::min(min[rc], semi[lc]);
      auto tmp = std::move(tree[rc]);
      tmp.sum.k = tmp.lmax.k = tmp.rmax.k = tmp.max.k = 0;
      tree[u] = tree[lc] + tmp;
    }
  }
  void tagging(int u, i64 val) {
    if (val <= min[u]) return;
    i64 d = val - min[u];
    min[u] = val, tag[u] = std::max(tag[u], val);
    tree[u].nxt -= d;
    tree[u].sum.b += tree[u].sum.k * d;
    tree[u].lmax.b += tree[u].lmax.k * d;
    tree[u].rmax.b += tree[u].rmax.k * d;
    tree[u].max.b += tree[u].max.k * d;
  }
  void pushdown(int u) {
    if (tag[u] == -inf) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = -inf;
  }
  void build(int s, int t, int u) {
    tag[u] = -inf;
    if (s == t) {
      Line tmp(1, a[s]);
      tree[u].sum = tree[u].lmax = tree[u].rmax = tree[u].max = tmp;
      tree[u].nxt = inf, min[u] = a[s], semi[u] = inf;
      return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void defeat(int s, int t, int u, i64 val) {
    tag[u] = std::max(val, tag[u]);
    if (val - min[u] <= tree[u].nxt) return tagging(u, val);
    int mid = (s + t) >> 1;
    defeat(s, mid, lc(u), val), defeat(mid + 1, t, rc(u), val);
    pushup(u);
  }
  void modify(int l, int r, int s, int t, int u, i64 val) {
    if (min[u] >= val) return;
    if (l <= s && t <= r && val < semi[u]) return defeat(s, t, u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  Node query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid < l) return query(l, r, mid + 1, t, rc(u));
    if (mid >= r) return query(l, r, s, mid, lc(u));
    return query(l, r, s, mid, lc(u)) + query(l, r, mid + 1, t, rc(u));
  }
} seg;
void solve() {
  FastIO::read(n, q);
  for (int i = 1; i <= n; i++) FastIO::read(a[i]);
  seg.build(1, n, 1);
  for (int i = 1; i <= q; i++) {
    int opt, l, r;
    FastIO::read(opt, l, r);
    if (opt == 0) {
      i64 val;
      FastIO::read(val);
      seg.modify(l, r, 1, n, 1, val);
    } else {
      FastIO::write(std::max(seg.query(l, r, 1, n, 1).max.b, 0ll), '\n');
    }
  }
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
// 势能为最小值的个数，感觉非常趣味啊！！！！