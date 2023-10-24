/**
 * @file    CF343B Alternating Current.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-21
 */
#include <iostream>
#include <stack>
#include <string>

using i64 = long long;

std::string s;
std::stack<char> st;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> s;
  for (int i = 0; i < s.length(); i++) {
    if (!st.empty() && s[i] == st.top()) st.pop();
    else st.push(s[i]);
  }

  if (st.empty()) std::cout << "Yes\n";
  else std::cout << "No\n";

  return 0;
}