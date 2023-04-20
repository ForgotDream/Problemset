/**
 * @file    P1198 最大数.cpp
 * @author  ForgotDream
 * @brief   线段树 or 单调栈
 * @date    2023-02-28
 */
#include <bits/stdc++.h>

using i64 = long long;

static const int INF = 0x3f3f3f3f;
template<int N>
struct SegTree {
  std::vector<int> tree;
  int n;

  SegTree() {
    tree.resize(N << 2, 0);
    return;
  }

  void update(int target, int s, int t, int u, int val) {
    if (target == s && t == target) {
      tree[u] = val;
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (target <= mid) {
      update(target, s, mid, lc, val);
    } else {
      update(target, mid + 1, t, rc, val);
    }
    tree[u] = std::max(tree[lc], tree[rc]);
    return;
  }

  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      return tree[u];
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    int res = -INF;
    if (l <= mid) {
      res = std::max(res, query(l, r, s, mid, lc));
    }
    if (r > mid) {
      res = std::max(res, query(l, r, mid + 1, t, rc));
    }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int M, D;
  SegTree<200050> s;
  std::cin >> M >> D;
  
  int lst = 0, cnt = 0;
  for (int i = 1; i <= M; i++) {
    char opt;
    i64 optnum;
    std::cin >> opt >> optnum;
    // std::cerr << i << "\n";
    if (opt == 'A') {
      ++cnt;
      // std::cerr << (optnum + lst) % D << "\n";
      s.update(cnt, 1, 200000, 1, (optnum + lst) % D);
    } else {
      lst = s.query(cnt - optnum + 1, cnt, 1, 200000, 1);
      std::cout << lst << "\n";
    }
  }

  return 0;
}