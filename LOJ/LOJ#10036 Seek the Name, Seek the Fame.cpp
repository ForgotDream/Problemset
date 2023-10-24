/**
 * @file    LOJ#10036 Seek the Name, Seek the Fame.cpp
 * @author  ForgotDream
 * @brief   字符串 Hash
 * @date    2023-04-02
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  static const int base = 233;
  std::vector<i64u> pow(4e5 + 50);

  pow[0] = 1;
  for (int i = 1; i <= 4e5; i++) {
    pow[i] = pow[i - 1] * base;
  }

  std::string s;
  while (std::cin >> s) {    
    i64u frontHash = 0, backHash = 0;
    for (int i = 1; i <= s.length(); i++) {
      frontHash = base * frontHash + s[i - 1] - 'a';
      backHash = backHash + pow[i - 1] * (s[s.length() - i] - 'a');
      if (frontHash == backHash) {
        std::cout << i << " ";
      }
    }
    std::cout << "\n";
  }

  return 0;
}