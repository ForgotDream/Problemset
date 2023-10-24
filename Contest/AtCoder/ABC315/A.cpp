#include <iostream>
#include <string>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  for (auto i : s) {
    if (i != 'a' && i != 'e' && i != 'i' && i != 'o' && i != 'u') {
      std::cout << i;
    }
  }

  return 0;
}