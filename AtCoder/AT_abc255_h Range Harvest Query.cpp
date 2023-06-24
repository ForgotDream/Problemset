/**
 * @file    AT_abc255_h Range Harvest Query.cpp
 * @author  ForgotDream
 * @brief   ODT
 * @date    2023-06-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

struct ODT {
  static constexpr i64 mod = 998244353, inv = 499122177;
  struct Node {
    i64 l, r;
    mutable i64 val;
    Node(i64 _l, i64 _r, i64 _v) : l(_l), r(_r), val(_v) {};
    bool operator<(const Node &rhs) const {
      return l < rhs.l;
    }
  };
  std::set<Node> tree;
  auto split(i64 u) {
    auto it = tree.lower_bound(Node(u, 0, 0));
    if (it != tree.end() && it->l == u) {
      return it;
    }
    --it;
    i64 l = it->l, r = it->r, val = it->val;
    tree.erase(it);
    tree.emplace(l, u - 1, val);
    return tree.emplace(u, r, val).first;
  }
  void assign(i64 l, i64 r, i64 val) {
    auto end = split(r + 1), begin = split(l);
    tree.erase(begin, end);
    tree.emplace(l, r, val);
  }
  i64 query(i64 l, i64 r, i64 d) {
    auto end = split(r + 1), begin = split(l);
    i128 res = 0;
    for (auto it = begin; it != end; it++) {
      i64 l = it->l, r = it->r, val = it->val;
      (res += i128(d - val) % mod * 
              (l + r) % mod * 
              (r - l + 1) % mod * 
              inv % mod) %= mod;
    }
    return res % mod;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  i64 n;
  int q;
  std::cin >> n >> q;

  ODT odt;
  odt.tree.emplace(1, n, 0);
  while (q--) {
    i64 l, r, d;
    std::cin >> d >> l >> r;
    std::cout << odt.query(l, r, d) << "\n";
    odt.assign(l, r, d);
  }

  return 0;
}
