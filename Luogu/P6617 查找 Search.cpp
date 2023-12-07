/**
 * @file    P6617 查找 Search.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-06
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 5e5 + 50;
int n, m, w, a[N];
std::set<int> s[N];
struct SegTree {
  int mx[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { mx[u] = std::max(mx[lc(u)], mx[rc(u)]); }
  void build(int s, int t, int u) {
    if (s == t) return mx[u] = a[s], void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int tar, int s, int t, int u, int val) {
    if (s == t) return mx[u] = val, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return mx[u];
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
inline int pre(int u) {
  auto it1 = s[a[u]].lower_bound(u), it2 = s[w - a[u]].lower_bound(u);
  if (it2 == s[w - a[u]].begin()) return 0;
  else if (it1 == s[a[u]].begin()) return *std::prev(it2);
  else if (*std::prev(it1) > *std::prev(it2)) return 0;
  else return *std::prev(it2);
}
void solve() {
  std::cin >> n >> m >> w;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) seg.modify(i, 1, n, 1, pre(i)), s[a[i]].insert(i);
  int cnt = 0;
  for (int opt, x, y; m; m--) {
    std::cin >> opt >> x >> y;
    if (opt == 1) {
      std::vector<int> rst;
      auto it = s[a[x]].upper_bound(x);
      if (it != s[a[x]].end()) rst.emplace_back(*it);
      it = s[w - a[x]].upper_bound(x);
      if (it != s[w - a[x]].end()) rst.emplace_back(*it);
      s[a[x]].erase(x), a[x] = y, s[a[x]].insert(x);
      rst.emplace_back(x);
      it = s[a[x]].upper_bound(x);
      if (it != s[a[x]].end()) rst.emplace_back(*it);
      it = s[w - a[x]].upper_bound(x);
      if (it != s[w - a[x]].end()) rst.emplace_back(*it);
      for (auto u : rst) seg.modify(u, 1, n, 1, pre(u));
    } else {
      x ^= cnt, y ^= cnt;
      if (seg.query(x, y, 1, n, 1) >= x) cnt++, std::cout << "Yes\n";
      else std::cout << "No\n";
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
