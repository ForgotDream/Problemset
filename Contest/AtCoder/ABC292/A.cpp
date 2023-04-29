#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;
  for (auto c : s) {
    std::cout << (char) toupper(c);
  }
  std::cout << "\n";

  return 0;
}