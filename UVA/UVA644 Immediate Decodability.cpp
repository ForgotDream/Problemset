/**
 * @file    UVA644 Immediate Decodability.cpp
 * @author  ForgotDream
 * @brief   Trie
 * @date    2023-02-27
 */
#include <bits/stdc++.h>

using i64 = long long;

template<int N, int SIGMA_SIZE>
struct Trie {
  std::vector<bool> vis, vis;
  std::vector<int> nxt[SIGMA_SIZE];
  int cnt;

  Trie() {
    vis.resize(N, 0);
    vis.resize(N, 0);
    for (int i = 0; i < SIGMA_SIZE; i++) {
      nxt[i].resize(N, 0);
    }
    cnt = 0;
    return;
  }

  bool insert(const std::string &s) {
    int len = s.length(), pivot = 0;
    bool flg = true;
    for (int i = 0; i < len; i++) {
      if (vis[pivot]) {
        flg = false;
      }
      if (!nxt[s[i] - '0'][pivot]) {
        nxt[s[i] - '0'][pivot] = ++cnt;
        vis[pivot] = true;
      }
      pivot = nxt[s[i] - '0'][pivot];
      // std::cerr << i << "\n";
    }
    vis[pivot] = true;
    if (vis[pivot]) {
      flg = false;
    }
    return flg;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::vector<std::string> v;
  int cnt = 0;
  while (std::cin >> s) {
    if (s == "9") {
      cnt++;
      Trie<1000, 2> trie;
      bool ans = true;
      for (const auto &str : v) {
        ans &= trie.insert(str);
        if (!ans) {
          std::cout << "Set " << cnt << " is not immediately decodable\n";
          break;
        }
      }
      if (ans) {
        std::cout << "Set " << cnt << " is immediately decodable\n";
      }
      v.clear();
    } else {
      v.push_back(s);
    }
  }

  return 0;
}