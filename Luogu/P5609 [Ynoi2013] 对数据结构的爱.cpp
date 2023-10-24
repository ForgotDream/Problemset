/**
 * @file    P5609 [Ynoi2013] 对数据结构的爱.cpp
 * @author  ForgotDream
 * @brief   线段树
 * @date    2023-09-10
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <ranges>

using i64 = long long;

constexpr int N = 1e6 + 50;
constexpr i64 inf = 1e18;
int n, m, p, a[N];
struct SegTree {
  struct Node {
    int l, r;
    i64 sum;
    std::vector<i64> f;
  } tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) {
    int l = tree[u].l, r = tree[u].r, mid = (l + r) >> 1;
    tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum;
    for (int i = 0, j = 0; i <= mid - l + 1; i++) {
      if (j == r - mid + 1) j = r - mid;
      for (; j <= r - mid; j++) {
        i64 cur = tree[lc(u)].f[i + 1] - 1 - 1ll * i * p + tree[lc(u)].sum;
        if (tree[rc(u)].f[j] > cur) {
          j--;
          break;
        }
        tree[u].f[i + j] = std::min(
            tree[u].f[i + j],
            std::max(tree[lc(u)].f[i],
                     tree[rc(u)].f[j] + 1ll * i * p - tree[lc(u)].sum));
      }
    }
  }
  void build(int s, int t, int u) {
    tree[u].l = s, tree[u].r = t;
    tree[u].f.resize(t - s + 5, inf);
    tree[u].f[0] = -inf;
    if (s == t) return tree[u].sum = a[s], tree[u].f[1] = p - a[s], void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int u, i64 val) {
    if (l == s && t == r) {
      auto it = std::ranges::upper_bound(tree[u].f, val);
      return val + tree[u].sum - 1ll * (std::prev(it) - tree[u].f.begin()) * p;
    }
    int mid = (s + t) >> 1;
    if (mid < l) {
      return query(l, r, mid + 1, t, rc(u), val);
    } else if (mid >= r) {
      return query(l, r, s, mid, lc(u), val);
    } else {
      return query(mid + 1, r, mid + 1, t, rc(u),
                   query(l, mid, s, mid, lc(u), val));
    }
  }
} seg;
void solve() {
  std::cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  seg.build(1, n, 1);
  while (m--) {
    int l, r;
    std::cin >> l >> r;
    std::cout << seg.query(l, r, 1, n, 1, 0) << "\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}