/**
 * @file    CF914F Substrings in a String.cpp
 * @author  ForgotDream
 * @brief   Bitmask + String
 * @date    2023-07-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q;
std::string s, y;
std::bitset<N> idx[26], ans;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> s;
  n = s.length();
  for (int i = 0; i < n; i++) idx[s[i] - 'a'].set(i);
  std::cin >> q;
  while (q--) {
    int opt;
    std::cin >> opt;
    if (opt & 1) {
      int i;
      char c;
      std::cin >> i >> c;
      i--;
      idx[s[i] - 'a'].reset(i);
      s[i] = c;
      idx[s[i] - 'a'].set(i);
    } else {
      int l, r;
      std::cin >> l >> r >> y;
      l--, r--;
      if (y.length() > r - l + 1) {
        std::cout << 0 << "\n";
        continue;
      }
      ans.set();
      for (int i = 0; i < y.length(); i++) ans &= (idx[y[i] - 'a'] >> i);
      std::cout << (ans >> l).count() - (ans >> (r - y.length() + 2)).count() << "\n";
    }
  }

  return 0;
}