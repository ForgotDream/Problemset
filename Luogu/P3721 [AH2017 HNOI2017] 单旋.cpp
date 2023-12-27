/*
 * @file    P3721 [AH2017/HNOI2017] 单旋.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-21
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int m, opt[N], val[N];

struct SegTree {
  int dep[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  inline void pushdown(int u) {
    if (!dep[u]) return;
    dep[lc(u)] += dep[u], dep[rc(u)] += dep[u];
    dep[u] = 0;
  }
  void add(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return dep[u] += val, void();
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) add(l, r, s, mid, lc(u), val);
    if (mid < r) add(l, r, mid + 1, t, rc(u), val);
  }
  void modify(int tar, int s, int t, int u, int val) {
    if (s == t) return dep[u] = val, void();
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
  }
  int query(int tar, int s, int t, int u) {
    if (s == t) return dep[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= tar) return query(tar, s, mid, lc(u));
    else return query(tar, mid + 1, t, rc(u));
  }
} seg;

std::set<int> s;
int rt, fa[N], lc[N], rc[N];
inline int insert(int x) {
  auto it = s.insert(x).first;
  if (!rt) return rt = x, seg.modify(x, 1, m, 1, 1), 1;
  if (it != s.begin()) {
    if (!rc[*std::prev(it)]) rc[fa[x] = *std::prev(it)] = x;
  }
  if (!fa[x]) lc[fa[x] = *std::next(it)] = x;
  int res = seg.query(fa[x], 1, m, 1) + 1;
  seg.modify(x, 1, m, 1, res);
  return res;
}
inline int getMin() {
  int x = *s.begin(), res = seg.query(x, 1, m, 1);
  if (x == rt) return 1;
  if (x + 1 <= fa[x] - 1) seg.add(x + 1, fa[x] - 1, 1, m, 1, -1);
  seg.add(1, m, 1, m, 1, 1);
  lc[fa[x]] = rc[x], fa[rc[x]] = fa[x], rc[fa[rt] = x] = rt, rt = x;
  seg.modify(x, 1, m, 1, 1);
  return res;
}
inline int getMax() {
  int x = *s.rbegin(), res = seg.query(x, 1, m, 1);
  if (x == rt) return 1;
  if (fa[x] + 1 <= x - 1) seg.add(fa[x] + 1, x - 1, 1, m, 1, -1);
  seg.add(1, m, 1, m, 1, 1);
  rc[fa[x]] = lc[x], fa[lc[x]] = fa[x], lc[fa[rt] = x] = rt, rt = x;
  seg.modify(x, 1, m, 1, 1);
  return res;
}
inline int delMin() {
  int res = getMin();
  seg.add(1, m, 1, m, 1, -1);
  s.erase(rt), fa[rc[rt]] = 0, rt = rc[rt];
  return res;
}
inline int delMax() {
  int res = getMax();
  seg.add(1, m, 1, m, 1, -1);
  s.erase(rt), fa[lc[rt]] = 0, rt = lc[rt];
  return res;
}

std::vector<int> b;
void init() {
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
}
inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}

void solve() {
  std::cin >> m;
  for (int i = 1; i <= m; i++) {
    std::cin >> opt[i];
    if (opt[i] == 1) std::cin >> val[i], b.push_back(val[i]);
  }

  init();
  for (int i = 1; i <= m; i++) {
    if (opt[i] == 1) val[i] = find(val[i]);
  }

  for (int i = 1; i <= m; i++) {
    switch (opt[i]) {
      case 1: std::cout << insert(val[i]) << "\n"; break;
      case 2: std::cout << getMin() << "\n"; break;
      case 3: std::cout << getMax() << "\n"; break;
      case 4: std::cout << delMin() << "\n"; break;
      case 5: std::cout << delMax() << "\n"; break;
      default: break;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
