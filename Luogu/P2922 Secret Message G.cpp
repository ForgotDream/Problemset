/**
 * @file    P2922 Secret Message G.cpp
 * @author  ForgotDream
 * @brief   Trie
 * @date    2023-02-27
 */
#include <bits/stdc++.h>

using i64 = long long;

template<int N, int SIGMA_SIZE>
class Trie {
  private:
    std::vector<int> end, vis;
    std::vector<int> nxt[SIGMA_SIZE], size;
    int cnt;

    int convert(char c) {
      return c - '0';
    };

  public:
    Trie() {
      end.resize(N, 0);
      vis.resize(N, 0);
      size.resize(N, 0);
      for (int i = 0; i < SIGMA_SIZE; i++) {
        nxt[i].resize(N, 0);
      }
      cnt = 0;
      return;
    }

    void insert(const std::string &s) {
      int len = s.length(), pivot = 0;
      for (int i = 0; i < len; i++) {
        if (!nxt[convert(s[i])][pivot]) {
          nxt[convert(s[i])][pivot] = ++cnt;
        }
        pivot = nxt[convert(s[i])][pivot];
        vis[pivot]++;
      }
      end[pivot]++;
      return;
    }

    int find(const std::string &s) {
      int res = 0, pivot = 0, len = s.length();
      bool flg = true;
      for (int i = 0; i < len; i++) {
        if (!nxt[convert(s[i])][pivot]) {
          flg = false;
          break;
        }
        pivot = nxt[convert(s[i])][pivot];
        res += end[pivot];
      }
      if (flg) {
        res = res + vis[pivot] - end[pivot];
      }
      return res;
    }

};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Trie<500050, 2> trie;
  std::vector<std::string> vec;

  int m, n;
  std::cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    int len;
    std::string s = "";
    std::cin >> len;
    for (int j = 1; j <= len; j++) {
      char c;
      std::cin >> c;
      s += c;
    }
    trie.insert(s);
  }

  for (int i = 1; i <= n; i++) {
    int len;
    std::string s = "";
    std::cin >> len;
    for (int j = 1; j <= len; j++) {
      char c;
      std::cin >> c;
      s += c;
    }
    std::cout << trie.find(s) << "\n";
  }

  return 0;
}