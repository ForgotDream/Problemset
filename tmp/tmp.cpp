/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-22
 */
#include <bits/stdc++.h>

using i64 = long long;

struct ODT {
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
    auto it = tree.lower_bound(Node(u - 1, 0, 0));
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
  i64 query(i64 l, i64 r) {
    
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  return 0;
}
