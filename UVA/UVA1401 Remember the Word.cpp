/**
 * @file    UVA1401 Remember the Word.cpp
 * @author  ForgotDream
 * @brief   DP + Trie
 * @date    2023-06-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 20071027;
template<size_t SIZ = int(1e5)>
struct Trie {
  std::vector<std::vector<int>> next;
  std::vector<int> f, end;
  Trie() { next.reserve(SIZ), next.emplace_back(26), end.push_back(0); }
  void insert(const std::string &s) {
    int p = 0;
    for (int i = 0; i < s.length(); i++) {
      int d = s[i] - 'a';
      if (!next[p][d]) { 
        next.emplace_back(26), end.push_back(0);
        next[p][d] = next.size() - 1;
      }
      p = next[p][d];
    }
    end[p] = s.length();
  }
  void find(const std::string &s, int st) {
    int p = 0;
    for (int i = st; i < s.length(); i++) {
      int d = s[i] - 'a';
      if (!next[p][d]) { return; }
      p = next[p][d];
      if (end[p]) { (f[st] += f[st + end[p]]) %= mod; }
    }
  }
  int solve(const std::string &s) {
    f.clear(), f.resize(s.length() + 1), f[s.length()] = 1;
    for (int i = s.length() - 1; ~i; i--) { find(s, i); }
    return f[0];
  }
};

void solve(int id, const std::string &s) {
  int n;
  std::cin >> n;
  Trie<> trie;
  for (int i = 0; i < n; i++) {
    std::string t;
    std::cin >> t;
    trie.insert(t);
  }
  std::cout << "Case " << id << ": " << trie.solve(s) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  int cnt = 0;
  while (std::cin >> s) { solve(++cnt, s); }

  return 0;
}