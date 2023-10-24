/**
 * @file    LOJ#2740 「JOISC 2016 Day 4」最差记者 2.cpp
 * @author  ForgotDream
 * @brief   SegTree + Hall Theorem
 * @date    2023-10-18
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;

constexpr int N = 4e5 + 50;
int n, m;
struct Node {
  int pos, val, idx;
  bool operator<(const Node &rhs) const {
    return val < rhs.val || (val == rhs.val && idx < rhs.idx);
  }
} a[N];
std::stack<int, std::vector<int>> st[N];
struct SegTree {
  int tree[N << 2], tag[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  inline void pushup(int u) { tree[u] = std::min(tree[lc(u)], tree[rc(u)]); }
  inline void tagging(int u, int val) { tree[u] += val, tag[u] += val; }
  inline void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    pushdown(u);
    int mid = (s + t) >> 1, res = 1e9;
    if (mid >= l) res = std::min(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::min(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
void solve() {
  std::cin >> n;
  for (int i = 1, pos, val; i <= n; i++) {
    std::cin >> pos >> val, a[i] = Node{pos, val, 0};
  }
  for (int i = 1, pos, val; i <= n; i++) {
    std::cin >> pos >> val, a[i + n] = Node{pos, val, 1};
  }
  m = n * 2;
  std::sort(a + 1, a + m + 1);
  int ans = n;
  for (int i = 1; i <= m; i++) {
    auto [pos, val, idx] = a[i];
    if (idx == 0) {
      seg.modify(i, m, 1, m, 1, 1);
      st[pos].push(i);
    } else {
      if (st[pos].empty()) {
        seg.modify(i, m, 1, m, 1, -1);
        continue;
      }
      int p = st[pos].top();
      seg.modify(p, m, 1, m, 1, -1);
      if (seg.query(1, i, 1, m, 1) < 0) {
        seg.modify(p, m, 1, m, 1, 1);
        seg.modify(i, m, 1, m, 1, -1);
      } else {
        ans--, st[pos].pop();
      }
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
