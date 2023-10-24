/**
 * @file    LOJ#10052 Immediate Decodability.cpp
 * @author  ForgotDream
 * @brief   Trie
 * @date    2023-04-15
 */
#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

struct Trie {
  std::vector<std::vector<int>> tree;
  std::vector<bool> vis, end;

  Trie() {
    tree.emplace_back(2, 0);
    vis.push_back(false);
    end.push_back(false);
    return;
  }

  void clear() {
    tree.clear(), vis.clear(), end.clear();
    tree.emplace_back(2, 0);
    vis.push_back(false);
    end.push_back(false);
    return;
  }

  bool insert(std::string s) {
    int pivot = 0;
    bool res = false, changeable = true;

    for (int i = 0; i < s.length(); i++) {
      int d = s[i] - '0';
      if (!tree[pivot][d]) {
        tree[pivot][d] = tree.size();
        tree.emplace_back(2, 0);
        vis.push_back(false);
        end.push_back(false);
      }
      pivot = tree[pivot][d];
      if (!vis[pivot] && changeable) {
        res = true;
      }
      if (end[pivot]) {
        res = false;
        changeable = false;
      }
      vis[pivot] = true;
    }
    end[pivot] = true;

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

  int cnt = 0;
  std::string num;
  Trie trie;
  bool flg = true;
  while (std::cin >> num) {
    if (num == "9") {
      trie.clear();
      if (flg) {
        std::cout << "Set " << ++cnt << " is immediately decodable\n";
      } else {
        flg = true;
      }
    } else {
      if (flg && !trie.insert(num)) {
        if (cnt == 0) {
          std::cout << num << "\n";
        }
        flg = false;
        std::cout << "Set " << ++cnt << " is not immediately decodable\n";
      }
    }
  }

  return 0;
}