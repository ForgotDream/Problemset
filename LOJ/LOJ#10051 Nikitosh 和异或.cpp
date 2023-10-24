/**
 * @file    LOJ#10051 Nikitosh 和异或.cpp
 * @author  ForgotDream
 * @brief   Trie
 * @date    2023-04-15
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

struct Trie {
  // std::vector<std::vector<int>> tree;
  int cnt, tree[static_cast<int>(6e6 + 50)][2];

  Trie() {
    cnt = 0;
    // tree.resize(6e6 + 50, std::vector<int>(2, 0));
    // tree.emplace_back(2, 0);
    return;
  }

  void clear() {
    // tree.clear();
    cnt = 0;
    // tree.resize(6e6 + 50, std::vector<int>(2, 0));
    // tree.emplace_back(2, 0);
    return;
  }

  void insert(int num) {
    int pivot = 0;

    for (int i = 30; i >= 0; i--) {
      int d = !!(num & (1 << i));
      if (tree[pivot][d] == 0) {
        tree[pivot][d] = ++cnt;
        // tree.emplace_back(2, 0);
      }
      pivot = tree[pivot][d];
    }

    return;
  }

  int findMax(int num) {
    int pivot = 0, res = 0;

    for (int i = 30; i >= 0; i--) {
      int d = !!(num & (1 << i));
      if (tree[pivot][!d]) {
        res += 1 << i;
        pivot = tree[pivot][!d];
      } else {
        pivot = tree[pivot][d];
      }
    }

    return res;
  }

};

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, xorSum = 0;
  std::cin >> n;

  std::vector<int> l(n), r(n);

  std::vector<int> a(n);
  Trie trie1;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    xorSum ^= a[i];
    trie1.insert(xorSum);
    l[i] = std::max((i == 0) ? 0 : l[i - 1], trie1.findMax(xorSum));
  }

  Trie trie2;
  xorSum = 0;

  for (int i = n - 1; i >= 0; i--) {
    xorSum ^= a[i];
    trie2.insert(xorSum);
    r[i] = std::max((i == n - 1) ? 0 : r[i + 1], trie2.findMax(xorSum));
  }

  int ans = 0;
  for (int i = 1; i < n - 1; i++) {
    ans = std::max(ans, l[i] + r[i + 1]);
  }
  ans = std::max(ans, std::max(l[0], r[n - 1]));

  std::cout << ans << "\n";

  return 0;
}