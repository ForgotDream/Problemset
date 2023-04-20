/**
 * @file    LOJ#10001 种树.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-17
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Query {
  int l, r, t;
  bool operator< (const Query &oth) const {
    if (r != oth.r) {
      return r < oth.r;
    }
    return l < oth.l;
  }
};

struct BIT {
  int n;
  std::vector<int> tree;

  BIT(int n) {
    this->n = n;
    tree.resize(n, 0);
    return;
  }

  static int lowbit(int x) {
    return x & -x;
  }

  void add(int x, int val) {
    for (int i = x; i <= n; i += lowbit(i)) {
      tree[i] += val;
    }
    return;
  }

  int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
      res += tree[i];
    }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, h;
  std::cin >> n >> h;

  std::vector<Query> a(h);
  for (auto &i : a) {
    std::cin >> i.l >> i.r >> i.t;
    i.l++;
    i.r++;
  }

  std::sort(a.begin(), a.end());
  
  BIT bit(n + 100);
  std::vector<bool> bucket(n + 100);
  int ans = 0;
  for (auto i : a) {
    int cur = bit.sum(i.r) - bit.sum(i.l - 1);
    
    if (i.t <= cur) {
      continue;
    }

    int rst = i.t - cur;
    ans += rst;
    for (int j = i.r; j >= i.l && rst; j--) {
      if (!bucket[j]) {
        bit.add(j, 1);
        rst--;
        bucket[j] = true;
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}