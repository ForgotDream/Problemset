#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;

  int c1 = 0, c2 = 0;
  for (int i = 0 ;i < s.length(); i++) {
    if (s[i] == 'A') {
      c1++;
    } else {
      c2++;
    }
    if (c1 >= (s.length() + 1) / 2) {
      std::cout << "A\n";
      return 0;
    }
    if (c2 >= (s.length() + 1) / 2) {
      std::cout << "T\n";
      return 0;
    }
  }

  return 0;
}