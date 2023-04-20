/**
 * @file    LOJ#10050 The XOR Largest Pair.cpp
 * @author  ForgotDream
 * @brief   Trie
 * @date    2023-04-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

struct Trie {
  int cnt;
  std::vector<std::vector<int>> tree;

  Trie() {
    cnt = 0;
    tree.emplace_back(std::vector<int> {0, 0});
    return;
  }

  void insert(int num) {
    int pivot = 0;

    for (int i = 30; i >= 0; i--) {
      if (tree[pivot][static_cast<bool>(num & (1 << i))] == 0) {
        tree[pivot][static_cast<bool>(num & (1 << i))] = ++cnt;
        tree.emplace_back(std::vector<int> {0, 0});
      }
      pivot = tree[pivot][static_cast<bool>(num & (1 << i))];
    }

    return;
  }

  int getMax(int num) {
    int res = 0, pivot = 0;

    for (int i = 30; i >= 0; i--) {
      if (tree[pivot][static_cast<bool>(!(num & (1 << i)))]) {
        res += (1 << i);
        pivot = tree[pivot][static_cast<bool>(!(num & (1 << i)))];
      } else {
        pivot = tree[pivot][static_cast<bool>(num & (1 << i))];  
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

  int n;
  std::cin >> n;

  Trie trie;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    // std::cerr << "OK\n";
    int num;
    std::cin >> num;
    trie.insert(num);
    ans = std::max(ans, trie.getMax(num));
  }

  std::cout << ans << "\n";

  return 0;
}