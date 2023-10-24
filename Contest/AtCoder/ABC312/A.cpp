#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  if (s == "ACE" || s == "BDF" || s == "CEG" || s == "DFA" || s == "EGB" || s == "FAC" || s == "GBD") {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }

  return 0;
}