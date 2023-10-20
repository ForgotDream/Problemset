/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-19
 */
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n, a[N], k, q[N];
struct SegTree {
  struct Node {
    std::vector<int> v;
    i64 p, q;
    friend Node operator+(const Node &lhs, const Node &rhs) {
      Node res;
      res.p = lhs.p + rhs.p, res.q = lhs.q + rhs.q;
      auto lit = lhs.v.begin(), rit = rhs.v.begin();
      while (lit != lhs.v.end() && rit != rhs.v.end()) {
        if (*lit < *rit) {
          res.v.push_back(*lit), res.q += std::distance(rit, rhs.v.end());
          lit++;
        } else if (*lit == *rit) {
          res.v.push_back(*lit), res.v.push_back(*rit);
          lit++, rit++;
        } else {
          res.v.push_back(*rit), res.p += std::distance(lhs.v.begin(), std::next(lit));
          rit++;
        }
      }
      while (lit != lhs.v.end()) res.v.push_back(*lit), lit++;
      while (rit != rhs.v.end()) res.v.push_back(*rit), rit++;
      return res;
    }
  } tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void build(int s, int t, int u) {
    if (s == t) return tree[u].v.push_back(a[s]), void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
} seg;
void solve() {
  std::cin >> n;
  int m = 1 << n;
  for (int i = 1; i <= m; i++) std::cin >> a[i];
  seg.build(1, m, 1);
  std::cout << seg.tree[1].p << " " << seg.tree[1].q << "\n";
  std::cin >> k;
  for (int i = 1; i <= k; i++) std::cin >> q[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
