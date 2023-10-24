/**
 * @file    AT_code_festival_2017_qualb_f Largest Smallest Cyclic Shift.cpp
 * @author  ForgotDream
 * @brief   极为巧妙的贪心，神题！
 * @date    2023-06-06
 */
#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int x, y, z;
  std::cin >> x >> y >> z;

  std::multiset<std::string> s;
  for (int i = 0; i < x; i++) { s.insert("a"); }
  for (int i = 0; i < y; i++) { s.insert("b"); }
  for (int i = 0; i < z; i++) { s.insert("c"); }

  while (s.size() > 1) {
    auto l = s.begin(), r = std::prev(s.end());
    s.insert(*l + *r);
    s.erase(l), s.erase(r);
  }

  std::cout << *s.begin() << "\n";

  return 0;
}