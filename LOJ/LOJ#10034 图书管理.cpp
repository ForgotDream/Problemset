/**
 * @file    LOJ#10034 图书管理.cpp
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

  int n;
  std::cin >> n;

  std::unordered_set<std::string> st;
  while (n--) {
    std::string opt, s;
    std::cin >> opt;
    std::getline(std::cin, s);

    if (opt == "add") {
      st.insert(s);
    } else {
      if (st.count(s)) {
        std::cout << "yes" << "\n";
      } else {
        std::cout << "no" << "\n";
      }
    }
  }

  return 0;
}