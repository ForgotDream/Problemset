/**
 * @file    CF817F MEX Queries.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-10-26
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using ti3 = std::tuple<int, i64, i64>;

constexpr int N = 1e5 + 50;
int n;
std::vector<i64> b;
int find(i64 u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
struct SegTree {
  struct Node {
    int l, r, sum, tag = -1;
    bool rev = false;
  } tree[N << 4];
  int cnt;
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  void tagging(int u, int val) {
    tree[u].tag = val, tree[u].sum = (tree[u].r - tree[u].l + 1) * val;
    tree[u].rev = false;
  }
  void revtagging(int u) {
    if (tree[u].tag != -1) tree[u].tag ^= 1;
    else tree[u].rev ^= 1;
    tree[u].sum = (tree[u].r - tree[u].l + 1) - tree[u].sum;
  }
  void pushdown(int u) {
    if (tree[u].tag != -1) {
      tagging(lc(u), tree[u].tag), tagging(rc(u), tree[u].tag);
      tree[u].tag = -1;
    }
    if (tree[u].rev) {
      revtagging(lc(u)), revtagging(rc(u));
      tree[u].rev = false;
    }
  }
  void build(int s, int t, int u) {
    tree[u].l = s, tree[u].r = t;
    if (s == t) return;
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void assign(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) assign(l, r, s, mid, lc(u), val);
    if (mid < r) assign(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  void reverse(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return revtagging(u);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) reverse(l, r, s, mid, lc(u));
    if (mid < r) reverse(l, r, mid + 1, t, rc(u));
    pushup(u);
  }
  int query(int s, int t, int u) {
    if (s == t) return s;
    pushdown(u);
    int mid = (s + t) >> 1;
    // std::cerr << tree[lc(u)].sum << " " << mid - s + 1 << "\n";
    if (tree[lc(u)].sum >= mid - s + 1) return query(mid + 1, t, rc(u));
    else return query(s, mid, lc(u));
  }
} seg;
ti3 query[N];
void solve() { 
  std::cin >> n;
  b.push_back(1);
  for (int opt, i = 1; i <= n; i++) {
    i64 l, r;
    std::cin >> opt >> l >> r;
    query[i] = std::make_tuple(opt, l, r);
    b.push_back(l), b.push_back(r), b.push_back(r + 1);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int m = b.size();
  seg.build(1, m, 1);
  for (int i = 1; i <= n; i++) {
    auto [opt, l, r] = query[i];
    l = find(l), r = find(r);
    if (opt == 1) seg.assign(l, r, 1, m, 1, 1);
    else if (opt == 2) seg.assign(l, r, 1, m, 1, 0);
    else seg.reverse(l, r, 1, m, 1);
    std::cout << b[seg.query(1, m, 1) - 1] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
