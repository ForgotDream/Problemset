#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  const std::vector<std::string> s = {"and", "not", "that", "the", "you"};

  int n;
  std::cin >> n;

  while (n--) {
    std::string cur;
    std::cin >> cur;
    for (auto i : s) {
      if (i == cur) {
        std::cout << "Yes" << '\n';
        return 0;
      }
    }
  }

  std::cout << "No" << '\n';

  return 0;
}