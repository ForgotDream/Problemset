/**
 * @file    P4097 【模板】李超线段树 / [HEOI2013] Segment.cpp
 * @author  ForgotDream
 * @brief   Lichao SegTree
 * @date    2023-10-26
 */
#include <algorithm>
#include <iostream>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e5 + 50, mod1 = 39989, mod2 = 1e9;
constexpr f80 eps = 1e-12;
int n;
struct Line {
  f80 k, b;
  inline f80 operator()(const f80 &val) { return k * val + b; }
};
int cmp(f80 lhs, f80 rhs) {
  if (lhs - rhs > eps) return 1;
  else if (rhs - lhs > eps) return -1;
  else return 0;
}
struct SegTree {
  struct Node {
    f80 val;
    int idx;
    bool operator<(const Node &rhs) const {
      if (cmp(val, rhs.val) == 1) return false;
      else if (cmp(val, rhs.val) == -1) return true;
      else return idx < rhs.idx ? false : true;
    }
  };
  int tree[N << 2], cnt;
  Line line[N];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void add(int x1, int x2, int y1, int y2) {
    cnt++;
    if (x1 == x2) {
      line[cnt].k = 0, line[cnt].b = std::max(y2, y1);
    } else {
      line[cnt].k = 1. * (y2 - y1) / (x2 - x1);
      line[cnt].b = y1 - line[cnt].k * x1;
    }
  }
  void modify(int s, int t, int u, int val) {
    int mid = (s + t) >> 1, &cur = tree[u];
    int d = cmp(line[val](mid), line[cur](mid));
    if (d == 1 || (!d && val < cur)) std::swap(val, cur);
    int dl = cmp(line[val](s), line[cur](s));
    int dr = cmp(line[val](t), line[cur](t));
    if (dl == 1 || (!dl && val < cur)) modify(s, mid, lc(u), val);
    if (dr == 1 || (!dr && val < cur)) modify(mid + 1, t, rc(u), val);
  }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return modify(s, t, u, val);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
  }
  Node query(int s, int t, int u, int val) {
    if (t < val || val < s) return {0, 0};
    Node cur = {line[tree[u]](val), tree[u]};
    if (s == t) return cur;
    int mid = (s + t) >> 1;
    return std::max(
        {cur, query(s, mid, lc(u), val), query(mid + 1, t, rc(u), val)});
  }
  void insert(int x1, int y1, int x2, int y2) {
    if (x1 > x2) std::swap(x1, x2), std::swap(y1, y2);
    add(x1, x2, y1, y2), modify(x1, x2, 1, mod1, 1, cnt);
  }
} seg;
void solve() {
  std::cin >> n;
  int lst = 0;
  for (int opt; n; n--) {
    std::cin >> opt;
    if (opt == 1) {
      int x1, y1, x2, y2;
      std::cin >> x1 >> y1 >> x2 >> y2;
      x1 = (x1 + lst - 1 + mod1) % mod1 + 1;
      y1 = (y1 + lst - 1 + mod2) % mod2 + 1;
      x2 = (x2 + lst - 1 + mod1) % mod1 + 1;
      y2 = (y2 + lst - 1 + mod2) % mod2 + 1;
      // std::cerr << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
      seg.insert(x1, y1, x2, y2);
    } else {
      int val;
      std::cin >> val;
      val = (val + lst - 1 + mod1) % mod1 + 1;
      std::cout << (lst = seg.query(1, mod1, 1, val).idx) << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
