#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::string s;
  std::cin >> s;
  for (int i = 0; i < s.length(); i += 2) {
    std::swap(s[i], s[i + 1]);
  }

  std::cout << s << "\n";

  return 0;
}